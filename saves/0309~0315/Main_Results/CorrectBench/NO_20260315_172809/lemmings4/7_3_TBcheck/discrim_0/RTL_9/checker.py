import numpy as np

class GoldenDUT:
    WL = 0b0001  # Walking Left
    WR = 0b0010  # Walking Right
    F = 0b0100   # Falling
    D = 0b1000   # Digging
    S = 0b10000  # Splattered

    WALK_LEFT = 0b0001
    WALK_RIGHT = 0b0010
    AAAH = 0b0100
    DIGGING = 0b1000

    def __init__(self):
        self.state_reg = self.WL
        self.walk_left_reg = 0
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_duration_reg = 0

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.__init__()
        else:
            self.update_state(bump_left, bump_right, ground, dig)

    def update_state(self, bump_left, bump_right, ground, dig):
        current_state = self.state_reg
        fall_duration = self.fall_duration_reg

        if current_state == self.F and ground:
            if fall_duration > 20:
                self.state_reg = self.S
                self.fall_duration_reg = 0
            else:
                self.state_reg = self.WL if (current_state & self.WL) else self.WR
                self.fall_duration_reg = 0
        elif current_state == self.D and not ground:
            self.state_reg = self.F
            self.fall_duration_reg += 1
        elif current_state == self.D and ground and not dig:
            self.state_reg = self.WL if (current_state & self.WL) else self.WR
        elif current_state == self.WL:
            if bump_left:
                self.state_reg = self.WR
            elif not ground:
                self.state_reg = self.F
                self.fall_duration_reg += 1
            elif dig and ground:
                self.state_reg = self.D
            else:
                pass  # Stay in WL
        elif current_state == self.WR:
            if bump_right:
                self.state_reg = self.WL
            elif not ground:
                self.state_reg = self.F
                self.fall_duration_reg += 1
            elif dig and ground:
                self.state_reg = self.D
            else:
                pass  # Stay in WR
        elif current_state == self.F:
            self.fall_duration_reg += 1
        elif current_state == self.S:
            pass  # Stay in S

        self.update_outputs()

    def update_outputs(self):
        current_state = self.state_reg
        if current_state == self.WL:
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        elif current_state == self.WR:
            self.walk_left_reg = 0
            self.walk_right_reg = 1
            self.aaah_reg = 0
            self.digging_reg = 0
        elif current_state == self.F:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 1
            self.digging_reg = 0
        elif current_state == self.D:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 1
        elif current_state == self.S:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0

    def check(self, signal_vector):
        walk_left_observed = signal_vector['walk_left']
        walk_right_observed = signal_vector['walk_right']
        aaah_observed = signal_vector['aaah']
        digging_observed = signal_vector['digging']

        if (self.walk_left_reg != walk_left_observed or
            self.walk_right_reg != walk_right_observed or
            self.aaah_reg != aaah_observed or
            self.digging_reg != digging_observed):
            print(f"Scenario: {signal_vector['scenario']}, "
                  f"expected: walk_left={self.walk_left_reg}, walk_right={self.walk_right_reg}, aaah={self.aaah_reg}, digging={self.digging_reg}, "
                  f"observed: walk_left={walk_left_observed}, walk_right={walk_right_observed}, aaah={aaah_observed}, digging={digging_observed}")
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
