class GoldenDUT:
    def __init__(self):
        self.WALK_LEFT = 0b0001
        self.WALK_RIGHT = 0b0010
        self.FALLING = 0b0100
        self.DIGGING = 0b1000
        self.SPLATTERED = 0b0000

        self.current_state_reg = self.WALK_LEFT
        self.fall_counter_reg = 0
        self.walk_left_reg = 0
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
            self.current_state_reg = self.WALK_LEFT
            self.fall_counter_reg = 0
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        else:
            self.current_state_reg, self.fall_counter_reg, self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg = self.lemming_fsm(bump_left, bump_right, ground, dig, self.current_state_reg, self.fall_counter_reg)

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
        next_state = current_state  # Initialize next_state to avoid UnboundLocalError
        next_fall_counter = fall_counter

        if current_state == self.WALK_LEFT:
            if bump_right:
                next_state = self.WALK_RIGHT
            elif bump_left:
                next_state = self.WALK_RIGHT
            elif not ground:
                next_state = self.FALLING
                aaah = 1
            elif dig and ground:
                next_state = self.DIGGING
            else:
                walk_left = 1
        elif current_state == self.WALK_RIGHT:
            if bump_left:
                next_state = self.WALK_LEFT
            elif bump_right:
                next_state = self.WALK_LEFT
            elif not ground:
                next_state = self.FALLING
                aaah = 1
            elif dig and ground:
                next_state = self.DIGGING
            else:
                walk_right = 1
        elif current_state == self.FALLING:
            if ground:
                if fall_counter > 20:
                    next_state = self.SPLATTERED
                else:
                    if current_state == self.WALK_LEFT:
                        next_state = self.WALK_LEFT
                        walk_left = 1
                    elif current_state == self.WALK_RIGHT:
                        next_state = self.WALK_RIGHT
                        walk_right = 1
                next_fall_counter = 0  # Reset fall counter when hitting the ground
            else:
                aaah = 1
                next_fall_counter += 1
        elif current_state == self.DIGGING:
            if not ground:
                next_state = self.FALLING
                aaah = 1
            else:
                digging = 1
        elif current_state == self.SPLATTERED:
            next_state = self.SPLATTERED
        else:
            next_state = self.SPLATTERED

        return next_state, next_fall_counter, walk_left, walk_right, aaah, digging
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
