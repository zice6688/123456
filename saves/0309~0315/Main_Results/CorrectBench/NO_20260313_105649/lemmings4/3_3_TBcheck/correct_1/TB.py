class GoldenDUT:
    def __init__(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter = 0
        self.reset = False

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.reset_state()
        else:
            self.update_state(bump_left, bump_right, ground, dig)

    def check(self, signal_vector):
        expected = {
            'walk_left': self.walk_left_reg,
            'walk_right': self.walk_right_reg,
            'aaah': self.aaah_reg,
            'digging': self.digging_reg
        }

        observed = {
            'walk_left': signal_vector['walk_left'],
            'walk_right': signal_vector['walk_right'],
            'aaah': signal_vector['aaah'],
            'digging': signal_vector['digging']
        }

        if expected != observed:
            print(f"Scenario: {signal_vector['scenario']}, expected: {expected}, observed: {observed}")
            return False
        return True

    def reset_state(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter = 0
        self.reset = True

    def update_state(self, bump_left, bump_right, ground, dig):
        if self.aaah_reg and ground == 1:
            if self.fall_counter > 20:
                self.splatter()
                return
            self.fall_counter = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            if self.walk_left_reg:
                self.walk_left_reg = 1
                self.walk_right_reg = 0
            else:
                self.walk_left_reg = 0
                self.walk_right_reg = 1
        elif ground == 0:
            self.aaah_reg = 1
            self.fall_counter += 1
            self.digging_reg = 0
        elif dig == 1 and not (self.aaah_reg or self.digging_reg) and ground == 1:
            self.digging_reg = 1
            self.walk_left_reg = 0
            self.walk_right_reg = 0
        elif self.digging_reg and ground == 0:
            self.digging_reg = 0
            self.aaah_reg = 1
            self.fall_counter += 1
        elif bump_left == 1 or bump_right == 1:
            if bump_left == 1 and bump_right == 0:
                self.walk_left_reg = 0
                self.walk_right_reg = 1
            elif bump_left == 0 and bump_right == 1:
                self.walk_left_reg = 1
                self.walk_right_reg = 0
            else:
                self.walk_left_reg, self.walk_right_reg = self.walk_right_reg, self.walk_left_reg
        else:
            # No change in direction
            pass

    def splatter(self):
        self.walk_left_reg = 0
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter = 0
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
