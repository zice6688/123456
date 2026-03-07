import numpy as np

class GoldenDUT:
    def __init__(self):
        self.state_reg = 0b0001  # Initial state: Walking Left (WL)
        self.walk_left_reg = 0
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0
        self.areset_reg = 0

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.state_reg = 0b0001  # Reset to WL
            self.fall_counter_reg = 0
        else:
            self.state_reg, self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg = self.get_next_state_and_outputs(self.state_reg, bump_left, bump_right, ground, dig, self.fall_counter_reg)

        if self.state_reg == 0b0100:  # FALL
            self.fall_counter_reg += 1
        else:
            self.fall_counter_reg = 0

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
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_left={expected_walk_left}, walk_right={expected_walk_right}, aaah={expected_aaah}, digging={expected_digging}")
            print(f"Scenario: {signal_vector['scenario']}, observed: walk_left={observed_walk_left}, walk_right={observed_walk_right}, aaah={observed_aaah}, digging={observed_digging}")
            return False
        return True

    def get_next_state_and_outputs(self, current_state, bump_left, bump_right, ground, dig, fall_counter):
        next_state = current_state
        walk_left = 0
        walk_right = 0
        aaah = 0
        digging = 0

        if current_state == 0b0001:  # WL
            if bump_left:
                next_state = 0b0010  # WR
            elif not ground:
                next_state = 0b0100  # FALL
            elif dig and ground:
                next_state = 0b1000  # DIG
            else:
                walk_left = 1
        elif current_state == 0b0010:  # WR
            if bump_right:
                next_state = 0b0001  # WL
            elif not ground:
                next_state = 0b0100  # FALL
            elif dig and ground:
                next_state = 0b1000  # DIG
            else:
                walk_right = 1
        elif current_state == 0b0100:  # FALL
            if ground:
                if fall_counter > 20:
                    next_state = 0b10000  # SPLATTER
                else:
                    if current_state == 0b0001:  # WL
                        next_state = 0b0001  # WL
                    elif current_state == 0b0010:  # WR
                        next_state = 0b0010  # WR
            else:
                aaah = 1
        elif current_state == 0b1000:  # DIG
            if not ground:
                next_state = 0b0100  # FALL
            else:
                digging = 1
        elif current_state == 0b10000:  # SPLATTER
            pass  # Stay in SPLATTER state

        return next_state, walk_left, walk_right, aaah, digging

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
