class GoldenDUT:
    def __init__(self):
        self.WALK_LEFT = 0b0001
        self.WALK_RIGHT = 0b0010
        self.FALLING = 0b0100
        self.DIGGING = 0b1000
        self.SPLATTERED = 0b10000

        self.current_state_reg = self.WALK_LEFT
        self.previous_state_reg = self.WALK_LEFT  # New register to store the previous state
        self.walk_left_reg = 0
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.current_state_reg = self.WALK_LEFT
            self.previous_state_reg = self.WALK_LEFT
            self.fall_counter_reg = 0
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            return

        if self.current_state_reg == self.WALK_LEFT:
            if bump_left or (bump_left and bump_right):
                self.current_state_reg = self.WALK_RIGHT
            elif bump_right:
                pass  # Stay in WALK_LEFT
            elif not ground:
                self.previous_state_reg = self.current_state_reg  # Store the current state before falling
                self.current_state_reg = self.FALLING
                self.aaah_reg = 1
            elif dig and ground:
                self.current_state_reg = self.DIGGING
                self.digging_reg = 1
            else:
                self.walk_left_reg = 1
                self.walk_right_reg = 0
                self.aaah_reg = 0
                self.digging_reg = 0

        elif self.current_state_reg == self.WALK_RIGHT:
            if bump_right or (bump_left and bump_right):
                self.current_state_reg = self.WALK_LEFT
            elif bump_left:
                pass  # Stay in WALK_RIGHT
            elif not ground:
                self.previous_state_reg = self.current_state_reg  # Store the current state before falling
                self.current_state_reg = self.FALLING
                self.aaah_reg = 1
            elif dig and ground:
                self.current_state_reg = self.DIGGING
                self.digging_reg = 1
            else:
                self.walk_left_reg = 0
                self.walk_right_reg = 1
                self.aaah_reg = 0
                self.digging_reg = 0

        elif self.current_state_reg == self.FALLING:
            if ground:
                if self.fall_counter_reg > 20:
                    self.current_state_reg = self.SPLATTERED
                    self.walk_left_reg = 0
                    self.walk_right_reg = 0
                    self.aaah_reg = 0
                    self.digging_reg = 0
                else:
                    self.current_state_reg = self.previous_state_reg  # Transition back to the previous state
                    if self.previous_state_reg == self.WALK_LEFT:
                        self.walk_left_reg = 1
                        self.walk_right_reg = 0
                    elif self.previous_state_reg == self.WALK_RIGHT:
                        self.walk_left_reg = 0
                        self.walk_right_reg = 1
                    elif self.previous_state_reg == self.DIGGING:
                        self.digging_reg = 1
                    self.aaah_reg = 0
                self.fall_counter_reg = 0
            else:
                self.aaah_reg = 1
                self.fall_counter_reg += 1

        elif self.current_state_reg == self.DIGGING:
            if not ground:
                self.previous_state_reg = self.current_state_reg  # Store the current state before falling
                self.current_state_reg = self.FALLING
                self.aaah_reg = 1
                self.digging_reg = 0
            else:
                self.digging_reg = 1
                self.aaah_reg = 0

        elif self.current_state_reg == self.SPLATTERED:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0

    def check(self, signal_vector):
        expected_walk_left = self.walk_left_reg
        expected_walk_right = self.walk_right_reg
        expected_aaah = self.aaah_reg
        expected_digging = self.digging_reg

        observed_walk_left = signal_vector['walk_left']
        observed_walk_right = signal_vector['walk_right']
        observed_aaah = signal_vector['aaah']
        observed_digging = signal_vector['digging']

        if (expected_walk_left != observed_walk_left or
            expected_walk_right != observed_walk_right or
            expected_aaah != observed_aaah or
            expected_digging != observed_digging):
            print(f"Scenario: {signal_vector['scenario']}, "
                  f"expected: walk_left={expected_walk_left}, walk_right={expected_walk_right}, aaah={expected_aaah}, digging={expected_digging}, "
                  f"observed: walk_left={observed_walk_left}, walk_right={observed_walk_right}, aaah={observed_aaah}, digging={observed_digging}")
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
