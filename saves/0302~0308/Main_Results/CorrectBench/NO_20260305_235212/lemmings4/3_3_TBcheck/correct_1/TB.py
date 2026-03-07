class GoldenDUT:
    WALK_LEFT = 0b0001
    WALK_RIGHT = 0b0010
    FALLING = 0b0100
    DIGGING = 0b1000
    SPLATTERING = 0b0000

    def __init__(self):
        self.current_state_reg = self.WALK_LEFT
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0
        self.previous_direction = self.WALK_LEFT

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.current_state_reg = self.WALK_LEFT
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg = 0
            self.previous_direction = self.WALK_LEFT
        else:
            self.current_state_reg, self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg, self.fall_counter_reg = self.lemming_fsm_rules(
                self.current_state_reg, bump_left, bump_right, ground, dig, self.fall_counter_reg)

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
        next_state = current_state
        walk_left = 0
        walk_right = 0
        aaah = 0
        digging = 0

        if current_state == self.WALK_LEFT:
            if bump_left:
                next_state = self.WALK_RIGHT
            elif not ground:
                next_state = self.FALLING
                self.previous_direction = self.WALK_LEFT
            elif dig and ground:
                next_state = self.DIGGING
        elif current_state == self.WALK_RIGHT:
            if bump_right:
                next_state = self.WALK_LEFT
            elif not ground:
                next_state = self.FALLING
                self.previous_direction = self.WALK_RIGHT
            elif dig and ground:
                next_state = self.DIGGING
        elif current_state == self.FALLING:
            if ground:
                if fall_counter > 20:
                    next_state = self.SPLATTERING
                else:
                    next_state = self.previous_direction
                fall_counter = 0
            else:
                fall_counter += 1
                aaah = 1
        elif current_state == self.DIGGING:
            if not ground:
                next_state = self.FALLING
                self.previous_direction = self.WALK_LEFT if (current_state & self.WALK_LEFT) else self.WALK_RIGHT
            elif ground and not dig:
                next_state = self.previous_direction
        elif current_state == self.SPLATTERING:
            pass  # Stay in splattering state

        if next_state == self.WALK_LEFT:
            walk_left = 1
        elif next_state == self.WALK_RIGHT:
            walk_right = 1
        elif next_state == self.FALLING:
            aaah = 1
        elif next_state == self.DIGGING:
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
