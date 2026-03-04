class GoldenDUT:
    def __init__(self):
        self.state_reg = 'walk_left'
        self.walk_left_reg = 1
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

        if areset == 1:
            self.reset()
        else:
            self.state_reg, outputs, self.fall_counter_reg = self.lemming_fsm(bump_left, bump_right, ground, dig, self.state_reg, self.fall_counter_reg)
            self.walk_left_reg = outputs['walk_left']
            self.walk_right_reg = outputs['walk_right']
            self.aaah_reg = outputs['aaah']
            self.digging_reg = outputs['digging']

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

    def lemming_fsm(self, bump_left, bump_right, ground, dig, current_state, fall_counter):
        walk_left = 0
        walk_right = 0
        aaah = 0
        digging = 0
        new_fall_counter = fall_counter

        if current_state == 'walk_left':
            if bump_left == 1 or (bump_left == 1 and bump_right == 1):
                next_state = 'walk_right'
            elif bump_right == 1:
                next_state = 'walk_left'
            elif ground == 0:
                next_state = 'fall'
                aaah = 1
                new_fall_counter = 1
            elif dig == 1 and ground == 1:
                next_state = 'dig'
                digging = 1
            else:
                next_state = 'walk_left'
                walk_left = 1
        elif current_state == 'walk_right':
            if bump_right == 1 or (bump_left == 1 and bump_right == 1):
                next_state = 'walk_left'
            elif bump_left == 1:
                next_state = 'walk_right'
            elif ground == 0:
                next_state = 'fall'
                aaah = 1
                new_fall_counter = 1
            elif dig == 1 and ground == 1:
                next_state = 'dig'
                digging = 1
            else:
                next_state = 'walk_right'
                walk_right = 1
        elif current_state == 'fall':
            if ground == 1:
                if fall_counter >= 20:
                    next_state = 'splatter'
                    new_fall_counter = 0
                else:
                    if self.state_reg == 'walk_left':
                        next_state = 'walk_left'
                        walk_left = 1
                    else:
                        next_state = 'walk_right'
                        walk_right = 1
                    new_fall_counter = 0
                    aaah = 0
            else:
                next_state = 'fall'
                aaah = 1
                new_fall_counter += 1
        elif current_state == 'dig':
            if ground == 0:
                next_state = 'fall'
                aaah = 1
                new_fall_counter = 1
            else:
                next_state = 'dig'
                digging = 1
                new_fall_counter = 0
        elif current_state == 'splatter':
            next_state = 'splatter'
            new_fall_counter = 0
            walk_left = 0
            walk_right = 0
            aaah = 0
            digging = 0
        else:
            raise ValueError("Invalid current state")

        return next_state, {'walk_left': walk_left, 'walk_right': walk_right, 'aaah': aaah, 'digging': digging}, new_fall_counter

    def reset(self):
        self.state_reg = 'walk_left'
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0
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
