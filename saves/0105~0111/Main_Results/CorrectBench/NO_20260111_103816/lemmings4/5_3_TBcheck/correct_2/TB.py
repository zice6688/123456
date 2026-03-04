import numpy as np

# Define the states
WALK_LEFT = 0b0001
WALK_RIGHT = 0b0010
FALL = 0b0100
DIG = 0b1000
SPLATTER = 0b10000

# Define the outputs
WALK_LEFT_OUT = 0b0001
WALK_RIGHT_OUT = 0b0010
AAAH = 0b0100
DIGGING = 0b1000

class GoldenDUT:
    def __init__(self):
        self.state_reg = WALK_LEFT
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
            self.state_reg = WALK_LEFT
            self.fall_counter_reg = 0
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        else:
            self.update_state(bump_left, bump_right, ground, dig)

    def update_state(self, bump_left, bump_right, ground, dig):
        if self.state_reg == SPLATTER:
            return

        if ground == 0 and (self.state_reg & (WALK_LEFT | WALK_RIGHT | DIG)):
            self.state_reg = FALL
            self.fall_counter_reg += 1
        elif self.state_reg == FALL:
            if ground == 1:
                if self.fall_counter_reg > 20:
                    self.state_reg = SPLATTER
                else:
                    self.state_reg = WALK_LEFT if (self.state_reg & WALK_LEFT) else WALK_RIGHT
                self.fall_counter_reg = 0
            else:
                self.fall_counter_reg += 1
        elif self.state_reg == WALK_LEFT:
            if bump_right == 1:
                self.state_reg = WALK_RIGHT
            elif dig == 1 and ground == 1:
                self.state_reg = DIG
        elif self.state_reg == WALK_RIGHT:
            if bump_left == 1:
                self.state_reg = WALK_LEFT
            elif dig == 1 and ground == 1:
                self.state_reg = DIG
        elif self.state_reg == DIG:
            if ground == 0:
                self.state_reg = FALL
                self.fall_counter_reg = 1

        self.update_outputs()

    def update_outputs(self):
        if self.state_reg == SPLATTER:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        elif self.state_reg == FALL:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 1
            self.digging_reg = 0
        elif self.state_reg == WALK_LEFT:
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        elif self.state_reg == WALK_RIGHT:
            self.walk_left_reg = 0
            self.walk_right_reg = 1
            self.aaah_reg = 0
            self.digging_reg = 0
        elif self.state_reg == DIG:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 1

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
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_left={expected_walk_left}, observed walk_left={observed_walk_left}")
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_right={expected_walk_right}, observed walk_right={observed_walk_right}")
            print(f"Scenario: {signal_vector['scenario']}, expected: aaah={expected_aaah}, observed aaah={observed_aaah}")
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
