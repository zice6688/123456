class GoldenDUT:
    def __init__(self):
        self.current_state_reg = 0b0001  # Initial state: Walking left
        self.fall_counter_reg = 0
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.previous_walking_direction = 0b0001  # Store the previous walking direction

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.current_state_reg = 0b0001  # Reset to walking left
            self.fall_counter_reg = 0
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.previous_walking_direction = 0b0001
        else:
            self.current_state_reg, self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg, self.fall_counter_reg = self.lemming_rules(
                bump_left, bump_right, ground, dig, self.current_state_reg, self.fall_counter_reg)

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
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_left={expected_walk_left}, walk_right={expected_walk_right}, aaah={expected_aaah}, digging={expected_digging}, observed: walk_left={observed_walk_left}, walk_right={observed_walk_right}, aaah={observed_aaah}, digging={observed_digging}")
            return False
        return True

    def lemming_rules(self, bump_left, bump_right, ground, dig, current_state, fall_counter):
        if current_state == 0b0001:  # Walking left
            walk_left = 1
            walk_right = 0
            aaah = 0
            digging = 0
            self.previous_walking_direction = 0b0001
        elif current_state == 0b0010:  # Walking right
            walk_left = 0
            walk_right = 1
            aaah = 0
            digging = 0
            self.previous_walking_direction = 0b0010
        elif current_state == 0b0100:  # Falling
            walk_left = 0
            walk_right = 0
            aaah = 1
            digging = 0
        elif current_state == 0b1000:  # Digging
            walk_left = 0
            walk_right = 0
            aaah = 0
            digging = 1
        else:  # Splattered
            walk_left = 0
            walk_right = 0
            aaah = 0
            digging = 0

        if bump_left and not (current_state & 0b0100) and not (current_state & 0b1000):
            if current_state == 0b0001:
                current_state = 0b0010
                self.previous_walking_direction = 0b0010
            elif current_state == 0b0010:
                current_state = 0b0001
                self.previous_walking_direction = 0b0001
        if bump_right and not (current_state & 0b0100) and not (current_state & 0b1000):
            if current_state == 0b0001:
                current_state = 0b0010
                self.previous_walking_direction = 0b0010
            elif current_state == 0b0010:
                current_state = 0b0001
                self.previous_walking_direction = 0b0001
        if bump_left and bump_right and not (current_state & 0b0100) and not (current_state & 0b1000):
            if current_state == 0b0001:
                current_state = 0b0010
                self.previous_walking_direction = 0b0010
            elif current_state == 0b0010:
                current_state = 0b0001
                self.previous_walking_direction = 0b0001
        if ground == 0 and not (current_state & 0b1000):
            current_state = 0b0100  # Falling
            fall_counter = 0
        if ground == 1 and current_state == 0b0100:
            if fall_counter >= 20:
                current_state = 0b0000  # Splattered
            else:
                current_state = self.previous_walking_direction  # Resume previous walking direction
        if dig and ground == 1 and not (current_state & 0b0100):
            current_state = 0b1000  # Start digging
        if dig and ground == 0 and current_state == 0b1000:
            current_state = 0b0100  # Fall after digging
            fall_counter = 0

        return current_state, walk_left, walk_right, aaah, digging, fall_counter
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
