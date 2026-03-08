import numpy as np

class GoldenDUT:
    WL = 0b0001  # Walking Left
    WR = 0b0010  # Walking Right
    F = 0b0100   # Falling
    D = 0b1000   # Digging
    S = 0b10000  # Splattered

    def __init__(self):
        self.state_reg = self.WL
        self.walk_left_reg = 0
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0
        self.previous_state_reg = self.WL  # Track the previous state before falling

    def next_state_and_outputs(self, bump_left, bump_right, ground, dig):
        next_state = self.state_reg
        walk_left = 0
        walk_right = 0
        aaah = 0
        digging = 0

        if self.state_reg == self.WL:
            if bump_left:
                next_state = self.WR
            elif not ground:
                next_state = self.F
                aaah = 1
            elif dig:
                next_state = self.D
                digging = 1
            else:
                walk_left = 1
        elif self.state_reg == self.WR:
            if bump_right:
                next_state = self.WL
            elif not ground:
                next_state = self.F
                aaah = 1
            elif dig:
                next_state = self.D
                digging = 1
            else:
                walk_right = 1
        elif self.state_reg == self.F:
            if ground:
                if self.fall_counter_reg > 20:
                    next_state = self.S
                else:
                    next_state = self.previous_state_reg  # Transition back to the previous state
                aaah = 0
            else:
                aaah = 1
        elif self.state_reg == self.D:
            if not ground:
                next_state = self.F
                aaah = 1
            else:
                digging = 1
        elif self.state_reg == self.S:
            pass  # Stay in the splattered state

        return next_state, walk_left, walk_right, aaah, digging

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.state_reg = self.WL
            self.fall_counter_reg = 0
            self.previous_state_reg = self.WL
        else:
            if self.state_reg == self.F:
                self.fall_counter_reg += 1
                if self.fall_counter_reg > 20 and ground:
                    self.state_reg = self.S
                    self.fall_counter_reg = 0
            else:
                self.fall_counter_reg = 0

            if (self.state_reg == self.WL or self.state_reg == self.WR) and not ground:
                self.previous_state_reg = self.state_reg  # Update the previous state before falling

        self.state_reg, self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg = self.next_state_and_outputs(bump_left, bump_right, ground, dig)

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
