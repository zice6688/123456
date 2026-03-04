class GoldenDUT:
    def __init__(self):
        # Internal state registers (as per FSM specification)
        self.intended_walk_left_reg = 1   # after reset: walk left
        self.intended_walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.splattered_reg = False
        self.fall_counter_reg = 0

    def _update_state(self, bump_left, bump_right, ground, dig):
        # --- STEP 0: Determine if currently walking (i.e., stably walking on ground: ground==1 AND not falling, not digging, not splattered)
        # CRITICAL FIX: is_walking now requires ground == 1 explicitly — per spec, walking only occurs when ground is present.
        is_walking = (ground == 1) and (self.aaah_reg == 0) and (self.digging_reg == 0) and (not self.splattered_reg)

        # --- STEP 1: FALL LOGIC (highest precedence)
        will_fall = (ground == 0)
        landed = (self.aaah_reg == 1) and (ground == 1)
        will_splatter = landed and (self.fall_counter_reg >= 21)

        # --- STEP 2: Compute next_fall_counter
        if will_splatter or (landed and not will_splatter):
            next_fall_counter = 0
        elif will_fall:
            next_fall_counter = self.fall_counter_reg + 1
        else:
            next_fall_counter = 0

        # --- STEP 3: Determine next_splattered
        next_splattered = self.splattered_reg or will_splatter

        # --- STEP 4: DIGGING LOGIC (medium precedence)
        will_start_digging = (
            (ground == 1) and
            (self.aaah_reg == 0) and
            (not self.splattered_reg) and
            (self.digging_reg == 0) and
            (dig == 1)
        )
        will_continue_digging = (
            (self.digging_reg == 1) and
            (ground == 1)
        )
        is_digging_now = will_start_digging or will_continue_digging

        # --- STEP 5: DIRECTION SWITCH LOGIC (lowest precedence) — ONLY if stably walking AND not digging this cycle
        # Note: is_walking already implies ground==1, !aaah, !digging, !splattered.
        # And we explicitly exclude digging *now*, because dig has higher precedence than direction switch.
        new_intended_walk_left = self.intended_walk_left_reg
        new_intended_walk_right = self.intended_walk_right_reg

        if is_walking and not is_digging_now:
            if bump_left and not bump_right:
                new_intended_walk_left = 0
                new_intended_walk_right = 1
            elif bump_right and not bump_left:
                new_intended_walk_left = 1
                new_intended_walk_right = 0
            elif bump_left and bump_right:
                # Toggle direction: if was walking left → walk right; if was walking right → walk left
                if self.intended_walk_left_reg:
                    new_intended_walk_left = 0
                    new_intended_walk_right = 1
                else:
                    new_intended_walk_left = 1
                    new_intended_walk_right = 0

        # --- STEP 6: Assign outputs based on current effective state
        if next_splattered:
            walk_left = 0
            walk_right = 0
            aaah = 0
            digging = 0
        elif will_fall:
            walk_left = 0
            walk_right = 0
            aaah = 1
            digging = 0
        elif is_digging_now:
            walk_left = 0
            walk_right = 0
            aaah = 0
            digging = 1
        else:
            walk_left = new_intended_walk_left
            walk_right = new_intended_walk_right
            aaah = 0
            digging = 0

        # Update internal registers
        # CRITICAL: Only update intended direction registers if NOT splattered — once splattered, they must remain frozen until reset.
        # The spec says "cease walking, falling, or digging forever (or until reset)", so intended direction should not change after splatter.
        if not next_splattered:
            self.intended_walk_left_reg = new_intended_walk_left
            self.intended_walk_right_reg = new_intended_walk_right
        # aaah_reg, digging_reg, splattered_reg, and fall_counter_reg are always updated (they drive behavior even when splattered, but outputs are zeroed)
        self.aaah_reg = aaah
        self.digging_reg = digging
        self.splattered_reg = next_splattered
        self.fall_counter_reg = next_fall_counter

    def load(self, signal_vector):
        # Extract inputs
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']
        areset = signal_vector['areset']

        # Handle asynchronous reset (active-high, level-sensitive modeling as per testbench: areset=1 means reset asserted *this cycle*)
        if areset:
            self.intended_walk_left_reg = 1
            self.intended_walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.splattered_reg = False
            self.fall_counter_reg = 0
        else:
            # Update state based on inputs
            self._update_state(bump_left, bump_right, ground, dig)

    def check(self, signal_vector):
        # Expected outputs are derived from current internal state (Moore outputs)
        # After splatter: all outputs are 0.
        # While falling (aaah=1): walk_left=0, walk_right=0, aaah=1, digging=0.
        # While digging: walk_left=0, walk_right=0, aaah=0, digging=1.
        # While walking (ground=1, !aaah, !digging, !splattered): outputs reflect intended direction.
        if self.splattered_reg:
            expected_walk_left = 0
            expected_walk_right = 0
            expected_aaah = 0
            expected_digging = 0
        elif self.aaah_reg == 1:
            expected_walk_left = 0
            expected_walk_right = 0
            expected_aaah = 1
            expected_digging = 0
        elif self.digging_reg == 1:
            expected_walk_left = 0
            expected_walk_right = 0
            expected_aaah = 0
            expected_digging = 1
        else:
            # Walking state: output intended directions
            expected_walk_left = self.intended_walk_left_reg
            expected_walk_right = self.intended_walk_right_reg
            expected_aaah = 0
            expected_digging = 0

        # Observed outputs from DUT (in signal_vector)
        observed_walk_left = signal_vector['walk_left']
        observed_walk_right = signal_vector['walk_right']
        observed_aaah = signal_vector['aaah']
        observed_digging = signal_vector['digging']

        # Compare
        if (expected_walk_left != observed_walk_left or
            expected_walk_right != observed_walk_right or
            expected_aaah != observed_aaah or
            expected_digging != observed_digging):
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_left={expected_walk_left}, walk_right={expected_walk_right}, aaah={expected_aaah}, digging={expected_digging}, observed: walk_left={observed_walk_left}, walk_right={observed_walk_right}, aaah={observed_aaah}, digging={observed_digging}")
            return False
        return True
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
