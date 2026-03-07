class GoldenDUT:
    def __init__(self):
        self.state_reg = 0b00  # Initial state: walking left
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
            self.reset()
        else:
            self.state_reg, outputs = self.lemming_fsm_rules(
                self.state_reg, bump_left, bump_right, ground, dig, self.fall_counter_reg)
            self.walk_left_reg = outputs['walk_left']
            self.walk_right_reg = outputs['walk_right']
            self.aaah_reg = outputs['aaah']
            self.digging_reg = outputs['digging']
            self.ground_reg = ground
            if self.state_reg == 0b10:  # Falling
                if not ground:
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
            print(f"Scenario: {signal_vector['scenario']}, "
                  f"expected: walk_left={expected_walk_left}, walk_right={expected_walk_right}, aaah={expected_aaah}, digging={expected_digging}, "
                  f"observed: walk_left={observed_walk_left}, walk_right={observed_walk_right}, aaah={observed_aaah}, digging={observed_digging}")
            return False
        return True

    def lemming_fsm_rules(self, current_state, bump_left, bump_right, ground, dig, fall_counter):
        outputs = {
            'walk_left': 0,
            'walk_right': 0,
            'aaah': 0,
            'digging': 0
        }

        if current_state == 0b00:  # Walking left
            if bump_left or bump_right:
                next_state = 0b01  # Switch to walking right
            elif not ground:
                next_state = 0b10  # Start falling
                outputs['aaah'] = 1
            elif dig and ground:
                next_state = 0b11  # Start digging
                outputs['digging'] = 1
            else:
                next_state = 0b00  # Continue walking left
                outputs['walk_left'] = 1
        elif current_state == 0b01:  # Walking right
            if bump_left or bump_right:
                next_state = 0b00  # Switch to walking left
            elif not ground:
                next_state = 0b10  # Start falling
                outputs['aaah'] = 1
            elif dig and ground:
                next_state = 0b11  # Start digging
                outputs['digging'] = 1
            else:
                next_state = 0b01  # Continue walking right
                outputs['walk_right'] = 1
        elif current_state == 0b10:  # Falling
            if ground:
                if fall_counter > 20:
                    next_state = 0b00  # Splatter
                    outputs['walk_left'] = 0
                    outputs['walk_right'] = 0
                    outputs['aaah'] = 0
                    outputs['digging'] = 0
                else:
                    next_state = 0b00 if (current_state & 0b01) == 0 else 0b01  # Resume walking in the same direction
                    outputs['walk_left'] = 1 if (current_state & 0b01) == 0 else 0
                    outputs['walk_right'] = 1 if (current_state & 0b01) == 1 else 0
            else:
                next_state = 0b10  # Continue falling
                outputs['aaah'] = 1
        elif current_state == 0b11:  # Digging
            if not ground:
                next_state = 0b10  # Start falling
                outputs['aaah'] = 1
            else:
                next_state = 0b11  # Continue digging
                outputs['digging'] = 1
        else:
            raise ValueError("Invalid current state")

        return next_state, outputs

    def reset(self):
        self.state_reg = 0b00  # Initial state: walking left
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0
        self.ground_reg = 1

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
