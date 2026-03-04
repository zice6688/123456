class GoldenDUT:
    def __init__(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.current_state = 'walk_left'
        self.fall_count = 0
        self.splattered = False
        self.ground_reg = 1

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
        walk_left_observed = signal_vector['walk_left']
        walk_right_observed = signal_vector['walk_right']
        aaah_observed = signal_vector['aaah']
        digging_observed = signal_vector['digging']

        if (self.walk_left_reg != walk_left_observed or
            self.walk_right_reg != walk_right_observed or
            self.aaah_reg != aaah_observed or
            self.digging_reg != digging_observed):
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_left={self.walk_left_reg}, observed walk_left={walk_left_observed}")
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_right={self.walk_right_reg}, observed walk_right={walk_right_observed}")
            print(f"Scenario: {signal_vector['scenario']}, expected: aaah={self.aaah_reg}, observed aaah={aaah_observed}")
            print(f"Scenario: {signal_vector['scenario']}, expected: digging={self.digging_reg}, observed digging={digging_observed}")
            return False
        return True

    def reset(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.current_state = 'walk_left'
        self.fall_count = 0
        self.splattered = False
        self.ground_reg = 1

    def update_state(self, bump_left, bump_right, ground, dig):
        if self.splattered:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            return

        if not ground:
            self.fall_count += 1
            if self.fall_count > 20:
                self.splattered = True
                self.walk_left_reg = 0
                self.walk_right_reg = 0
                self.aaah_reg = 0
                self.digging_reg = 0
                return
            self.aaah_reg = 1
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.digging_reg = 0
            return

        if self.fall_count > 0:
            self.fall_count = 0
            if self.current_state == 'walk_left':
                self.walk_left_reg = 1
                self.walk_right_reg = 0
                self.aaah_reg = 0
                self.digging_reg = 0
            elif self.current_state == 'walk_right':
                self.walk_left_reg = 0
                self.walk_right_reg = 1
                self.aaah_reg = 0
                self.digging_reg = 0
            return

        if bump_left and not bump_right:
            self.current_state = 'walk_right'
            self.walk_left_reg = 0
            self.walk_right_reg = 1
            self.aaah_reg = 0
            self.digging_reg = 0
        elif bump_right and not bump_left:
            self.current_state = 'walk_left'
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        elif bump_left and bump_right:
            if self.current_state == 'walk_left':
                self.current_state = 'walk_right'
                self.walk_left_reg = 0
                self.walk_right_reg = 1
                self.aaah_reg = 0
                self.digging_reg = 0
            elif self.current_state == 'walk_right':
                self.current_state = 'walk_left'
                self.walk_left_reg = 1
                self.walk_right_reg = 0
                self.aaah_reg = 0
                self.digging_reg = 0

        if dig and ground and (self.current_state == 'walk_left' or self.current_state == 'walk_right'):
            self.current_state = 'digging'
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 1
        elif self.current_state == 'digging' and not ground:
            self.current_state = 'falling'
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 1
            self.digging_reg = 0
        elif self.current_state == 'digging' and ground:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 1

        if self.current_state == 'walk_left':
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        elif self.current_state == 'walk_right':
            self.walk_left_reg = 0
            self.walk_right_reg = 1
            self.aaah_reg = 0
            self.digging_reg = 0
        elif self.current_state == 'digging':
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 1
        else:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0

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
