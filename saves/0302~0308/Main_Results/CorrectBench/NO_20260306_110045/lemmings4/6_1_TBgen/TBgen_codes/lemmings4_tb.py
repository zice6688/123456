class GoldenDUT:
    def __init__(self):
        self.state_reg = 0b0001  # Initial state: WALK_LEFT
        self.fall_counter_reg = 0
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
            self.state_reg = 0b0001  # Reset to WALK_LEFT
            self.fall_counter_reg = 0
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        else:
            self.state_reg, self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg, self.fall_counter_reg = self.lemming_rules(
                self.state_reg, bump_left, bump_right, ground, dig, self.fall_counter_reg)

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

    def lemming_rules(self, current_state, bump_left, bump_right, ground, dig, fall_counter):
        next_state = current_state
        walk_left = 0
        walk_right = 0
        aaah = 0
        digging = 0

        if current_state == 0b10000:  # SPLATTERED
            pass
        elif current_state == 0b0001:  # WALK_LEFT
            if bump_left:
                next_state = 0b0010  # WALK_RIGHT
            elif not ground:
                next_state = 0b0100  # FALLING
            elif dig:
                next_state = 0b1000  # DIGGING
        elif current_state == 0b0010:  # WALK_RIGHT
            if bump_right:
                next_state = 0b0001  # WALK_LEFT
            elif not ground:
                next_state = 0b0100  # FALLING
            elif dig:
                next_state = 0b1000  # DIGGING
        elif current_state == 0b0100:  # FALLING
            if ground:
                if fall_counter > 20:
                    next_state = 0b10000  # SPLATTERED
                else:
                    next_state = current_state & (0b0001 | 0b0010)  # Resume walking in the same direction
                fall_counter = 0
            else:
                fall_counter += 1
        elif current_state == 0b1000:  # DIGGING
            if not ground:
                next_state = 0b0100  # FALLING
            elif ground and not dig:
                next_state = current_state & (0b0001 | 0b0010)  # Resume walking in the same direction

        # Determine the outputs based on the next state
        if next_state == 0b0001:  # WALK_LEFT
            walk_left = 1
        elif next_state == 0b0010:  # WALK_RIGHT
            walk_right = 1
        elif next_state == 0b0100:  # FALLING
            aaah = 1
        elif next_state == 0b1000:  # DIGGING
            digging = 1

        return next_state, walk_left, walk_right, aaah, digging, fall_counter

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
