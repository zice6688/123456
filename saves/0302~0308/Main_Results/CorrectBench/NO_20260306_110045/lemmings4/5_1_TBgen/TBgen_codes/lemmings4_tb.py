class GoldenDUT:
    def __init__(self):
        self.state_reg = 0b0001  # Initial state: Walking Left (WL)
        self.previous_state_reg = 0b0001  # Previous state: Walking Left (WL)
        self.fall_count_reg = 0  # Fall count
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.state_reg = 0b0001  # Reset to Walking Left (WL)
            self.previous_state_reg = 0b0001
            self.fall_count_reg = 0
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        else:
            next_state, outputs = self.generate_expected_values(bump_left, bump_right, ground, dig)
            self.previous_state_reg = self.state_reg
            self.state_reg = next_state
            self.walk_left_reg = outputs['walk_left']
            self.walk_right_reg = outputs['walk_right']
            self.aaah_reg = outputs['aaah']
            self.digging_reg = outputs['digging']

            if self.state_reg == 0b0100:  # Falling (F)
                self.fall_count_reg += 1
            else:
                self.fall_count_reg = 0

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

    def generate_expected_values(self, bump_left, bump_right, ground, dig):
        current_state = self.state_reg
        previous_state = self.previous_state_reg
        fall_count = self.fall_count_reg

        next_state = self.state_transition(current_state, previous_state, bump_left, bump_right, ground, dig, fall_count)
        outputs = self.get_outputs(next_state, previous_state, ground, dig)
        return next_state, outputs

    def get_outputs(self, state, previous_state, ground, dig):
        if state == 0b0001:  # Walking Left (WL)
            return {
                'walk_left': 1,
                'walk_right': 0,
                'aaah': 0,
                'digging': 0
            }
        elif state == 0b0010:  # Walking Right (WR)
            return {
                'walk_left': 0,
                'walk_right': 1,
                'aaah': 0,
                'digging': 0
            }
        elif state == 0b0100:  # Falling (F)
            return {
                'walk_left': 0,
                'walk_right': 0,
                'aaah': 1,
                'digging': 0
            }
        elif state == 0b1000:  # Digging (D)
            return {
                'walk_left': 0,
                'walk_right': 0,
                'aaah': 0,
                'digging': 1
            }
        elif state == 0b10000:  # Splattered (S)
            return {
                'walk_left': 0,
                'walk_right': 0,
                'aaah': 0,
                'digging': 0
            }

    def state_transition(self, current_state, previous_state, bump_left, bump_right, ground, dig, fall_count):
        next_state = current_state
        if current_state == 0b0001:  # Walking Left (WL)
            if bump_left:
                next_state = 0b0010  # Walking Right (WR)
            elif ground == 0:
                next_state = 0b0100  # Falling (F)
            elif dig and ground == 1:
                next_state = 0b1000  # Digging (D)
        elif current_state == 0b0010:  # Walking Right (WR)
            if bump_right:
                next_state = 0b0001  # Walking Left (WL)
            elif ground == 0:
                next_state = 0b0100  # Falling (F)
            elif dig and ground == 1:
                next_state = 0b1000  # Digging (D)
        elif current_state == 0b0100:  # Falling (F)
            if ground == 1:
                if fall_count > 20:
                    next_state = 0b10000  # Splattered (S)
                else:
                    next_state = previous_state
        elif current_state == 0b1000:  # Digging (D)
            if ground == 0:
                next_state = 0b0100  # Falling (F)
            elif ground == 1 and dig == 0:
                next_state = previous_state
        return next_state

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
