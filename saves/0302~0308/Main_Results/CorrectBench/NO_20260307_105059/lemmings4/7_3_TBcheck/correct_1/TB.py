import numpy as np

class GoldenDUT:
    def __init__(self):
        self.WALK_LEFT = 0b0001
        self.WALK_RIGHT = 0b0010
        self.FALLING = 0b0100
        self.DIGGING = 0b1000
        self.SPLATTERED = 0b10000
        self.current_state_reg = self.WALK_LEFT
        self.fall_counter_reg = 0
        self.walk_left_reg = 0
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.current_state_reg = self.WALK_LEFT
            self.fall_counter_reg = 0
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        else:
            self.update_state(bump_left, bump_right, ground, dig)
            self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg = self.get_outputs()

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

    def update_state(self, bump_left, bump_right, ground, dig):
        if self.current_state_reg == self.FALLING:
            self.fall_counter_reg += 1
            if self.fall_counter_reg > 20:
                self.current_state_reg = self.SPLATTERED
        else:
            self.fall_counter_reg = 0

        if ground == 0:
            if self.current_state_reg in [self.WALK_LEFT, self.WALK_RIGHT, self.DIGGING]:
                self.current_state_reg = self.FALLING
            elif self.current_state_reg == self.FALLING:
                if self.fall_counter_reg > 20:
                    self.current_state_reg = self.SPLATTERED
        elif ground == 1:
            if self.current_state_reg == self.FALLING:
                if self.fall_counter_reg > 20:
                    self.current_state_reg = self.SPLATTERED
                else:
                    self.current_state_reg = self.WALK_LEFT if (self.current_state_reg == self.WALK_LEFT or self.current_state_reg == self.DIGGING) else self.WALK_RIGHT
            elif self.current_state_reg == self.DIGGING:
                self.current_state_reg = self.WALK_LEFT if (self.current_state_reg == self.WALK_LEFT) else self.WALK_RIGHT
            elif dig == 1 and self.current_state_reg in [self.WALK_LEFT, self.WALK_RIGHT]:
                self.current_state_reg = self.DIGGING
            elif bump_left == 1 and bump_right == 1:
                self.current_state_reg = self.WALK_RIGHT if self.current_state_reg == self.WALK_LEFT else self.WALK_LEFT
            elif bump_left == 1:
                self.current_state_reg = self.WALK_RIGHT
            elif bump_right == 1:
                self.current_state_reg = self.WALK_LEFT

    def get_outputs(self):
        walk_left = 1 if self.current_state_reg == self.WALK_LEFT else 0
        walk_right = 1 if self.current_state_reg == self.WALK_RIGHT else 0
        aaah = 1 if self.current_state_reg == self.FALLING else 0
        digging = 1 if self.current_state_reg == self.DIGGING else 0
        return walk_left, walk_right, aaah, digging
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
