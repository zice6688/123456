import numpy as np

class GoldenDUT:
    def __init__(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.direction_reg = 'left'
        self.falling_reg = False
        self.splattered_reg = False
        self.fall_counter_reg = 0
        self.direction_before_fall_reg = 'left'  # New state variable to store the direction before falling

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.reset()
            return

        if self.splattered_reg:
            return

        # Handle direction change due to bumps
        if not self.falling_reg and not self.digging_reg:
            if bump_left == 1 or bump_right == 1:
                if bump_left == 1:
                    self.direction_reg = 'right'
                elif bump_right == 1:
                    self.direction_reg = 'left'

        # Handle falling and splattering
        if ground == 0 and not self.digging_reg:
            if not self.falling_reg:
                self.direction_before_fall_reg = self.direction_reg  # Store the direction before falling
            self.falling_reg = True
            self.aaah_reg = 1
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg += 1
        elif ground == 1 and self.falling_reg:
            if self.fall_counter_reg > 20:
                self.splattered_reg = True
                self.walk_left_reg = 0
                self.walk_right_reg = 0
                self.aaah_reg = 0
                self.digging_reg = 0
            else:
                self.falling_reg = False
                self.aaah_reg = 0
                self.direction_reg = self.direction_before_fall_reg  # Restore the direction before falling
                if self.direction_reg == 'left':
                    self.walk_left_reg = 1
                    self.walk_right_reg = 0
                else:
                    self.walk_left_reg = 0
                    self.walk_right_reg = 1
            self.fall_counter_reg = 0

        # Handle digging
        if ground == 1 and dig == 1 and not self.falling_reg:
            self.digging_reg = 1
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
        elif ground == 0 and self.digging_reg:
            self.digging_reg = 0
            self.falling_reg = True
            self.aaah_reg = 1
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.fall_counter_reg += 1

        # Set walking direction if not falling or digging
        if not self.falling_reg and not self.digging_reg:
            if self.direction_reg == 'left':
                self.walk_left_reg = 1
                self.walk_right_reg = 0
            else:
                self.walk_left_reg = 0
                self.walk_right_reg = 1

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

    def reset(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.direction_reg = 'left'
        self.falling_reg = False
        self.splattered_reg = False
        self.fall_counter_reg = 0
        self.direction_before_fall_reg = 'left'  # Reset the direction before falling

# Example usage
if __name__ == "__main__":
    golden_dut = GoldenDUT()
    signal_vector = {
        'areset': 0,
        'bump_left': 0,
        'bump_right': 0,
        'ground': 1,
        'dig': 0,
        'walk_left': 1,
        'walk_right': 0,
        'aaah': 0,
        'digging': 0,
        'scenario': 1
    }
    golden_dut.load(signal_vector)
    result = golden_dut.check(signal_vector)
    print("Check result:", result)
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
