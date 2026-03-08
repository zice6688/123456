class GoldenDUT:
    def __init__(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0
        self.splattered_reg = 0
        self.prev_walk_left_reg = 0
        self.prev_walk_right_reg = 0

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.reset()
        else:
            self.update_state(bump_left, bump_right, ground, dig)

    def check(self, signal_vector):
        expected_outputs = self.get_expected_outputs(signal_vector)
        observed_outputs = {
            'walk_left': signal_vector['walk_left'],
            'walk_right': signal_vector['walk_right'],
            'aaah': signal_vector['aaah'],
            'digging': signal_vector['digging']
        }

        if expected_outputs != observed_outputs:
            print(f"Scenario: {signal_vector['scenario']}, expected: {expected_outputs}, observed: {observed_outputs}")
            return False
        return True

    def reset(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0
        self.splattered_reg = 0
        self.prev_walk_left_reg = 0
        self.prev_walk_right_reg = 0

    def update_state(self, bump_left, bump_right, ground, dig):
        if self.splattered_reg:
            return

        if ground == 0:
            if self.fall_counter_reg >= 20:
                self.splattered_reg = 1
                self.walk_left_reg = 0
                self.walk_right_reg = 0
                self.aaah_reg = 0
                self.digging_reg = 0
            else:
                self.aaah_reg = 1
                self.fall_counter_reg += 1
                self.walk_left_reg = 0
                self.walk_right_reg = 0
                self.digging_reg = 0
        else:
            if self.aaah_reg:
                # Restore the previous walking direction
                self.walk_left_reg = self.prev_walk_left_reg
                self.walk_right_reg = self.prev_walk_right_reg
                self.aaah_reg = 0
                self.fall_counter_reg = 0
            else:
                if dig == 1 and not self.aaah_reg:
                    self.digging_reg = 1
                    self.walk_left_reg = 0
                    self.walk_right_reg = 0
                elif self.digging_reg == 1 and ground == 0:
                    self.aaah_reg = 1
                    self.digging_reg = 0
                    self.walk_left_reg = 0
                    self.walk_right_reg = 0
                else:
                    if bump_left == 1 or bump_right == 1:
                        if bump_left == 1:
                            self.walk_left_reg = 0
                            self.walk_right_reg = 1
                        elif bump_right == 1:
                            self.walk_left_reg = 1
                            self.walk_right_reg = 0
                    else:
                        self.walk_left_reg = self.walk_left_reg
                        self.walk_right_reg = self.walk_right_reg
                    self.aaah_reg = 0
                    self.digging_reg = 0

            # Store the current walking direction before falling
            self.prev_walk_left_reg = self.walk_left_reg
            self.prev_walk_right_reg = self.walk_right_reg

    def get_expected_outputs(self, signal_vector):
        return {
            'walk_left': self.walk_left_reg,
            'walk_right': self.walk_right_reg,
            'aaah': self.aaah_reg,
            'digging': self.digging_reg
        }
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
