class GoldenDUT:
    def __init__(self):
        self.WALK_LEFT = 0b0001
        self.WALK_RIGHT = 0b0010
        self.FALLING = 0b0100
        self.DIGGING = 0b1000
        self.SPLATTERED = 0b10000

        self.current_state_reg = self.WALK_LEFT
        self.fall_counter_reg = 0
        self.walk_left_reg = 0
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.previous_state_reg = self.WALK_LEFT  # To store the previous state before falling

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.current_state_reg = self.WALK_LEFT
            self.fall_counter_reg = 0
            self.previous_state_reg = self.WALK_LEFT
        else:
            next_state, fall_counter, walk_left, walk_right, aaah, digging = self.fsm_rules(
                bump_left, bump_right, ground, dig, self.current_state_reg, self.fall_counter_reg, self.previous_state_reg
            )
            self.current_state_reg = next_state
            self.fall_counter_reg = fall_counter
            self.walk_left_reg = walk_left
            self.walk_right_reg = walk_right
            self.aaah_reg = aaah
            self.digging_reg = digging
            if self.current_state_reg != self.FALLING:
                self.previous_state_reg = self.current_state_reg  # Update previous state if not falling

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

    def fsm_rules(self, bump_left, bump_right, ground, dig, current_state, fall_counter, previous_state):
        next_state = current_state
        aaah = 0
        walk_left = 0
        walk_right = 0
        digging = 0

        if current_state == self.WALK_LEFT:
            if bump_left:
                next_state = self.WALK_RIGHT
            elif bump_right:
                next_state = self.WALK_LEFT
            elif not ground:
                next_state = self.FALLING
                aaah = 1
            elif dig and ground:
                next_state = self.DIGGING
            else:
                next_state = self.WALK_LEFT
        elif current_state == self.WALK_RIGHT:
            if bump_right:
                next_state = self.WALK_LEFT
            elif bump_left:
                next_state = self.WALK_RIGHT
            elif not ground:
                next_state = self.FALLING
                aaah = 1
            elif dig and ground:
                next_state = self.DIGGING
            else:
                next_state = self.WALK_RIGHT
        elif current_state == self.FALLING:
            if ground:
                if fall_counter >= 20:
                    next_state = self.SPLATTERED
                else:
                    next_state = previous_state  # Resume the previous state before falling
                aaah = 0
                fall_counter = 0  # Reset fall counter when Lemming hits the ground
            else:
                fall_counter += 1
                next_state = self.FALLING
                aaah = 1
        elif current_state == self.DIGGING:
            if not ground:
                next_state = self.FALLING
                aaah = 1
            elif ground:
                next_state = previous_state  # Resume the previous state before digging
            else:
                next_state = self.DIGGING
        elif current_state == self.SPLATTERED:
            next_state = self.SPLATTERED
        else:
            next_state = self.WALK_LEFT

        walk_left = 1 if next_state == self.WALK_LEFT else 0
        walk_right = 1 if next_state == self.WALK_RIGHT else 0
        aaah = 1 if next_state == self.FALLING else 0
        digging = 1 if next_state == self.DIGGING else 0

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
