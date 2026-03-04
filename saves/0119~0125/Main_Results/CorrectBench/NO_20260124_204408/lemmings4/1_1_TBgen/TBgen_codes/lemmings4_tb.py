class GoldenDUT:
    def __init__(self):
        # Internal state registers (suffix "_reg")
        self.walk_left_reg = 1      # initial state: walk left after reset
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.splattered_reg = False
        self.fall_counter_reg = 0   # 6-bit counter, saturates at 63
        self.pre_fall_walk_left_reg = 1  # stores direction before fall starts
        self.pre_fall_walk_right_reg = 0

    def _update_pre_fall_direction(self, walk_left, walk_right):
        # Update pre-fall direction only when currently walking (not falling/digging/splattered)
        if (walk_left or walk_right) and not self.aaah_reg and not self.digging_reg and not self.splattered_reg:
            self.pre_fall_walk_left_reg = walk_left
            self.pre_fall_walk_right_reg = walk_right

    def load(self, signal_vector):
        # Extract inputs
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        # Asynchronous reset has highest priority
        if areset:
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.splattered_reg = False
            self.fall_counter_reg = 0
            self.pre_fall_walk_left_reg = 1
            self.pre_fall_walk_right_reg = 0
            return

        # Determine current state flags from *current* register values (state entering this cycle)
        was_walking = (self.walk_left_reg or self.walk_right_reg) and not self.aaah_reg and not self.digging_reg and not self.splattered_reg
        was_falling = self.aaah_reg and not self.digging_reg and not self.splattered_reg
        was_digging = self.digging_reg and not self.aaah_reg and not self.splattered_reg

        # Precedence: FALL > DIG > BUMP

        # FALL condition: ground == 0
        if ground == 0:
            # Falling: aaah=1, all others off; increment fall counter (6-bit saturated)
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 1
            self.digging_reg = 0
            # fall_counter_reg increments, saturate at 63 (6 bits)
            self.fall_counter_reg = min(63, self.fall_counter_reg + 1)
            # pre_fall direction remains unchanged during fall
            return

        # GROUND == 1: landing or normal operation
        if was_falling:
            # Landing: check splatter condition
            if self.fall_counter_reg >= 21:  # fell for >20 cycles → splatter
                self.walk_left_reg = 0
                self.walk_right_reg = 0
                self.aaah_reg = 0
                self.digging_reg = 0
                self.splattered_reg = True
                self.fall_counter_reg = 0
                self.pre_fall_walk_left_reg = 0
                self.pre_fall_walk_right_reg = 0
            else:
                # Safe landing: resume pre-fall direction
                self.walk_left_reg = self.pre_fall_walk_left_reg
                self.walk_right_reg = self.pre_fall_walk_right_reg
                self.aaah_reg = 0
                self.digging_reg = 0
                self.splattered_reg = False
                self.fall_counter_reg = 0
                # pre_fall direction preserved for next potential fall
            return

        # Not falling, ground==1: check splattered state
        if self.splattered_reg:
            # Splattered: all outputs remain 0 forever
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg = 0
            self.pre_fall_walk_left_reg = 0
            self.pre_fall_walk_right_reg = 0
            return

        # Not splattered, ground==1, not falling → could be walking or digging
        if was_digging:
            # Continue digging while ground==1
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 1
            self.fall_counter_reg = 0
            # pre_fall direction unchanged during digging
            return

        # Now: must be walking (was_walking is True), ground==1, not splattered, not falling, not digging
        # Check DIG condition: start digging if dig==1 and ground==1
        if dig == 1:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 1
            self.fall_counter_reg = 0
            # Save current walking direction as pre-fall direction (in case dig leads to fall later)
            self._update_pre_fall_direction(self.walk_left_reg, self.walk_right_reg)
            return

        # No dig: evaluate bumps for direction change
        if bump_left == 1 and bump_right == 0:
            # Bump left → walk right
            self.walk_left_reg = 0
            self.walk_right_reg = 1
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg = 0
            self._update_pre_fall_direction(self.walk_left_reg, self.walk_right_reg)
        elif bump_right == 1 and bump_left == 0:
            # Bump right → walk left
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg = 0
            self._update_pre_fall_direction(self.walk_left_reg, self.walk_right_reg)
        elif bump_left == 1 and bump_right == 1:
            # Toggle direction
            if self.walk_left_reg == 1:
                self.walk_left_reg = 0
                self.walk_right_reg = 1
            else:
                self.walk_left_reg = 1
                self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg = 0
            self._update_pre_fall_direction(self.walk_left_reg, self.walk_right_reg)
        else:
            # No bump: maintain current direction
            # All output regs remain unchanged
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg = 0
            self._update_pre_fall_direction(self.walk_left_reg, self.walk_right_reg)

    def check(self, signal_vector):
        # Expected outputs are current register values
        expected_walk_left = self.walk_left_reg
        expected_walk_right = self.walk_right_reg
        expected_aaah = self.aaah_reg
        expected_digging = self.digging_reg

        # Observed outputs from DUT (from signal vector)
        observed_walk_left = signal_vector.get('walk_left', 0)
        observed_walk_right = signal_vector.get('walk_right', 0)
        observed_aaah = signal_vector.get('aaah', 0)
        observed_digging = signal_vector.get('digging', 0)

        # Compare each output
        if expected_walk_left != observed_walk_left:
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_left={expected_walk_left}, observed walk_left={observed_walk_left}")
            return False
        if expected_walk_right != observed_walk_right:
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_right={expected_walk_right}, observed walk_right={observed_walk_right}")
            return False
        if expected_aaah != observed_aaah:
            print(f"Scenario: {signal_vector['scenario']}, expected: aaah={expected_aaah}, observed aaah={observed_aaah}")
            return False
        if expected_digging != observed_digging:
            print(f"Scenario: {signal_vector['scenario']}, expected: digging={expected_digging}, observed digging={observed_digging}")
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
