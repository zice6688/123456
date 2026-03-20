class GoldenDUT:
    def __init__(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0

    def reset(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.reset()
        else:
            new_state, new_fall_counter = self.lemming_rules(bump_left, bump_right, ground, dig)
            self.walk_left_reg = new_state['walk_left']
            self.walk_right_reg = new_state['walk_right']
            self.aaah_reg = new_state['aaah']
            self.digging_reg = new_state['digging']
            self.fall_counter_reg = new_fall_counter

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

    def lemming_rules(self, bump_left, bump_right, ground, dig):
        new_state = {
            'walk_left': self.walk_left_reg,
            'walk_right': self.walk_right_reg,
            'aaah': self.aaah_reg,
            'digging': self.digging_reg
        }
        new_fall_counter = self.fall_counter_reg

        # Handle falling
        if ground == 0:
            new_state['aaah'] = 1
            new_state['walk_left'] = 0
            new_state['walk_right'] = 0
            new_state['digging'] = 0
            new_fall_counter += 1
            if new_fall_counter > 20:
                new_state['aaah'] = 0
                new_state['walk_left'] = 0
                new_state['walk_right'] = 0
                new_state['digging'] = 0
                return new_state, new_fall_counter
            return new_state, new_fall_counter

        # Reset fall counter when on ground
        if ground == 1:
            new_fall_counter = 0

        # Handle splattering after falling for more than 20 cycles
        if new_fall_counter > 20 and ground == 1:
            new_state['aaah'] = 0
            new_state['walk_left'] = 0
            new_state['walk_right'] = 0
            new_state['digging'] = 0
            new_fall_counter = 0
            return new_state, new_fall_counter

        # Handle digging
        if dig == 1 and ground == 1 and self.aaah_reg == 0:
            new_state['digging'] = 1
            new_state['walk_left'] = 0
            new_state['walk_right'] = 0
            return new_state, new_fall_counter

        if dig == 0 and self.digging_reg == 1 and ground == 0:
            new_state['digging'] = 0
            new_state['aaah'] = 1
            new_state['walk_left'] = 0
            new_state['walk_right'] = 0
            new_fall_counter += 1
            return new_state, new_fall_counter

        # Handle bumping
        if bump_left == 1 and (self.walk_left_reg == 1 or self.walk_right_reg == 0):
            new_state['walk_left'] = 0
            new_state['walk_right'] = 1
        elif bump_right == 1 and (self.walk_right_reg == 1 or self.walk_left_reg == 0):
            new_state['walk_left'] = 1
            new_state['walk_right'] = 0

        # Resume walking in the same direction when back on ground
        if ground == 1 and self.aaah_reg == 1:
            new_state['aaah'] = 0
            if self.walk_left_reg == 1:
                new_state['walk_left'] = 1
                new_state['walk_right'] = 0
            elif self.walk_right_reg == 1:
                new_state['walk_left'] = 0
                new_state['walk_right'] = 1

        return new_state, new_fall_counter
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
