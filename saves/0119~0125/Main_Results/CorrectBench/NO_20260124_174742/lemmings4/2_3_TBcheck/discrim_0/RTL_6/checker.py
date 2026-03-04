class GoldenDUT:
    def __init__(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0
        self.ground_reg = 1

    def load(self, signal_vector):
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']
        areset = signal_vector['areset']

        if areset:
            self.__init__()
        else:
            (self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg), self.fall_counter_reg = self.lemming_rules(
                bump_left, bump_right, ground, dig, 
                (self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg), 
                self.fall_counter_reg
            )
            self.ground_reg = ground

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

    def lemming_rules(self, bump_left, bump_right, ground, dig, current_state, fall_counter):
        walk_left, walk_right, aaah, digging = current_state

        new_walk_left = walk_left
        new_walk_right = walk_right
        new_aaah = aaah
        new_digging = digging
        new_fall_counter = fall_counter

        if ground == 0 and not digging:
            new_aaah = 1
            new_walk_left = 0
            new_walk_right = 0
            new_digging = 0
            new_fall_counter += 1
        else:
            new_aaah = 0
            new_fall_counter = 0

        if ground == 1 and new_fall_counter > 20:
            new_walk_left = 0
            new_walk_right = 0
            new_aaah = 0
            new_digging = 0
            new_fall_counter = 0

        if ground == 1 and dig == 1 and not aaah:
            new_digging = 1
            new_walk_left = 0
            new_walk_right = 0
            new_aaah = 0
        elif ground == 0 and new_digging:
            new_digging = 0
            new_aaah = 1
            new_walk_left = 0
            new_walk_right = 0
        elif ground == 1 and not dig and new_digging:
            new_digging = 0
            new_walk_left = walk_left
            new_walk_right = walk_right
            new_aaah = 0

        if bump_left == 1 and bump_right == 0 and not (new_aaah or new_digging):
            new_walk_left = 0
            new_walk_right = 1
        elif bump_right == 1 and bump_left == 0 and not (new_aaah or new_digging):
            new_walk_left = 1
            new_walk_right = 0
        elif bump_left == 1 and bump_right == 1 and not (new_aaah or new_digging):
            if walk_left == 1:
                new_walk_left = 0
                new_walk_right = 1
            else:
                new_walk_left = 1
                new_walk_right = 0

        if ground == 1 and new_aaah:
            new_aaah = 0
            new_walk_left = walk_left
            new_walk_right = walk_right
            new_digging = 0

        return (new_walk_left, new_walk_right, new_aaah, new_digging), new_fall_counter

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
