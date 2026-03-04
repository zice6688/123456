class GoldenDUT:
    def __init__(self):
        # Internal state registers (suffix "_reg")
        self.walk_left_reg = 1      # initial: walk left after reset
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0  # counts consecutive ground=0 cycles while aaah=1
        self.splattered_reg = False
        self.base_dir_reg = 0      # 0 = walk left, 1 = walk right (persistent base direction)
        self.ground_prev_reg = 1   # previous ground value; initial = 1 (ground present at reset)

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        # Store current ground as previous for next cycle — do this *first*, before any state update
        # because all edge detections (e.g., ground rising) depend on *old* ground vs *new* ground
        ground_prev = self.ground_prev_reg
        self.ground_prev_reg = ground

        # Asynchronous reset takes immediate effect (highest priority)
        if areset:
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg = 0
            self.splattered_reg = False
            self.base_dir_reg = 0
            return

        # If already splattered, all outputs remain 0 forever until reset
        # AND no internal state (base_dir, fall_counter, etc.) may be modified further
        if self.splattered_reg:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            # DO NOT modify base_dir_reg, fall_counter_reg, or any other register
            # All state is frozen — only ground_prev_reg was already updated above
            return

        # FALL PRECEDENCE: ground == 0
        if ground == 0:
            # aaah = 1, others = 0
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 1
            self.digging_reg = 0
            # Fall counter increments only if was *already falling* in previous cycle (i.e., aaah was 1 last cycle)
            # Since aaah_reg hasn't been updated yet, it holds the *previous* cycle's aaah value
            if self.aaah_reg == 1:  # was falling before this cycle
                self.fall_counter_reg += 1
            else:
                self.fall_counter_reg = 1
            return

        # Now ground == 1 → not falling this cycle
        # Check for SPLATTER TRIGGER: ground rising edge AND fall_counter >= 21
        ground_rising = (ground_prev == 0) and (ground == 1)
        if ground_rising and (self.fall_counter_reg >= 21):
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg = 0
            self.splattered_reg = True
            # base_dir_reg remains unchanged (frozen), but outputs are zeroed — no need to preserve it for logic
            return

        # Only if NO splatter occurred on this ground-rising edge: reset fall counter
        self.fall_counter_reg = 0

        # DIG PRECEDENCE: enabled only if not falling (aaah was 0), not digging (digging was 0),
        # and was walking (i.e., walk_left or walk_right was 1 *before* this cycle) and dig==1
        # Note: 'was walking' means outputs were active *before* any updates this cycle.
        # Since we haven't updated walk_*_reg yet, current values reflect prior state.
        was_walking = (self.walk_left_reg == 1) or (self.walk_right_reg == 1)
        can_dig = (not self.aaah_reg) and (not self.digging_reg) and was_walking and (dig == 1)
        if can_dig:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 1
            return

        # BUMP or HOLD: only eligible if not falling and not digging
        # Again: use *current* (i.e., pre-update) values of aaah_reg/digging_reg to check eligibility
        if (not self.aaah_reg) and (not self.digging_reg):
            # Bump logic: flip base_dir on bumps
            if bump_left and bump_right:
                self.base_dir_reg = 1 - self.base_dir_reg
            elif bump_left:
                self.base_dir_reg = 1
            elif bump_right:
                self.base_dir_reg = 0
            # else: hold base_dir

            # Set walk outputs based on updated base_dir
            if self.base_dir_reg == 0:
                self.walk_left_reg = 1
                self.walk_right_reg = 0
            else:
                self.walk_left_reg = 0
                self.walk_right_reg = 1
            self.aaah_reg = 0
            self.digging_reg = 0
        else:
            # Not eligible for bump: resume base direction (e.g., after dig or fall)
            # But note: if we just exited dig or fall, base_dir_reg is still valid
            if self.base_dir_reg == 0:
                self.walk_left_reg = 1
                self.walk_right_reg = 0
            else:
                self.walk_left_reg = 0
                self.walk_right_reg = 1
            self.aaah_reg = 0
            self.digging_reg = 0

    def check(self, signal_vector):
        # Expected outputs are the current register values
        expected_walk_left = self.walk_left_reg
        expected_walk_right = self.walk_right_reg
        expected_aaah = self.aaah_reg
        expected_digging = self.digging_reg

        # Observed outputs from DUT (from signal vector)
        observed_walk_left = signal_vector.get('walk_left', 0)
        observed_walk_right = signal_vector.get('walk_right', 0)
        observed_aaah = signal_vector.get('aaah', 0)
        observed_digging = signal_vector.get('digging', 0)

        # Compare all four outputs
        ok = True
        if expected_walk_left != observed_walk_left:
            print(f"Scenario: {signal_vector['scenario']}, expected walk_left={expected_walk_left}, observed walk_left={observed_walk_left}")
            ok = False
        if expected_walk_right != observed_walk_right:
            print(f"Scenario: {signal_vector['scenario']}, expected walk_right={expected_walk_right}, observed walk_right={observed_walk_right}")
            ok = False
        if expected_aaah != observed_aaah:
            print(f"Scenario: {signal_vector['scenario']}, expected aaah={expected_aaah}, observed aaah={observed_aaah}")
            ok = False
        if expected_digging != observed_digging:
            print(f"Scenario: {signal_vector['scenario']}, expected digging={expected_digging}, observed digging={observed_digging}")
            ok = False

        return ok
def check_dut(vectors_in):
    golden_dut = GoldenDUT()
    failed_scenarios = []
    for vector in vectors_in:
        if vector["check_en"]:
            check_pass = golden_dut.check(vector)
            if check_pass:
                print(f"Passed; vector: {vector}")
            else:
                print(f"Failed; vector: {vector}")
                failed_scenarios.append(vector["scenario"])
        golden_dut.load(vector)
    return failed_scenarios

def SignalTxt_to_dictlist(txt:str):
    signals = []
    lines = txt.strip().split("\n")
    for line in lines:
        signal = {}
        if line.startswith("[check]"):
            signal["check_en"] = True
            line = line[7:]
        elif line.startswith("scenario"):
            signal["check_en"] = False
        else:
            continue
        line = line.strip().split(", ")
        for item in line:
            if "scenario" in item:
                item = item.split(": ")
                signal["scenario"] = item[1].replace(" ", "")
            else:
                item = item.split(" = ")
                key = item[0]
                value = item[1]
                if ("x" not in value) and ("X" not in value) and ("z" not in value):
                    signal[key] = int(value)
                else:
                    if ("x" in value) or ("X" in value):
                        signal[key] = 0 # used to be "x"
                    else:
                        signal[key] = 0 # used to be "z"
        signals.append(signal)
    return signals
with open("TBout.txt", "r") as f:
    txt = f.read()
vectors_in = SignalTxt_to_dictlist(txt)
tb_pass = check_dut(vectors_in)
print(tb_pass)
