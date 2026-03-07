class GoldenDUT:
    def __init__(self):
        self.current_state_reg = 0b0000  # Initial state: walking left
        self.fall_counter_reg = 0
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.previous_direction = 0b0000  # Initial direction: walking left

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.__init__()
        else:
            self.current_state_reg, self.fall_counter_reg, self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg = self.lemming_rules(bump_left, bump_right, ground, dig, self.current_state_reg, self.fall_counter_reg)

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
        walk_left = 0
        walk_right = 0
        aaah = 0
        digging = 0
        next_state = current_state  # Initialize next_state to the current state

        if current_state == 0b0000:  # Walking left
            if bump_left == 1 or bump_right == 1:
                next_state = 0b0001  # Switch to walking right
            elif ground == 0:
                next_state = 0b0010  # Start falling
                aaah = 1
                self.previous_direction = 0b0000  # Store the current direction
            elif dig == 1 and ground == 1:
                next_state = 0b0100  # Start digging
                digging = 1
                self.previous_direction = 0b0000  # Store the current direction
            else:
                next_state = 0b0000  # Continue walking left
                walk_left = 1
        elif current_state == 0b0001:  # Walking right
            if bump_left == 1 or bump_right == 1:
                next_state = 0b0000  # Switch to walking left
            elif ground == 0:
                next_state = 0b0010  # Start falling
                aaah = 1
                self.previous_direction = 0b0001  # Store the current direction
            elif dig == 1 and ground == 1:
                next_state = 0b0100  # Start digging
                digging = 1
                self.previous_direction = 0b0001  # Store the current direction
            else:
                next_state = 0b0001  # Continue walking right
                walk_right = 1
        elif current_state == 0b0010:  # Falling
            if ground == 1:
                if fall_counter > 20:
                    next_state = 0b1000  # Splatter
                else:
                    if self.previous_direction == 0b0000:
                        next_state = 0b0000  # Resume walking left
                        walk_left = 1
                    elif self.previous_direction == 0b0001:
                        next_state = 0b0001  # Resume walking right
                        walk_right = 1
            else:
                next_state = 0b0010  # Continue falling
                aaah = 1
                fall_counter += 1
        elif current_state == 0b0100:  # Digging
            if ground == 0:
                next_state = 0b0010  # Start falling
                aaah = 1
                self.previous_direction = current_state  # Store the current direction
            else:
                next_state = 0b0100  # Continue digging
                digging = 1
        elif current_state == 0b1000:  # Splattering
            next_state = 0b1000  # Stay in splattered state
        else:
            raise ValueError("Invalid current state")

        return next_state, fall_counter, walk_left, walk_right, aaah, digging
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
