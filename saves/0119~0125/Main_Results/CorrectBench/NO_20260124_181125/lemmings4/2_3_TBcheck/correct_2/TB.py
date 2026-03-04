class GoldenDUT:
    def __init__(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.current_state_reg = 'walk_left'
        self.fall_counter_reg = 0

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.current_state_reg = 'walk_left'
            self.fall_counter_reg = 0
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        else:
            self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg, self.current_state_reg, self.fall_counter_reg = self.lemming_rules(
                bump_left, bump_right, ground, dig, self.current_state_reg, self.fall_counter_reg
            )

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
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_left={expected_walk_left}, walk_right={expected_walk_right}, aaah={expected_aaah}, digging={expected_digging}")
            print(f"Observed: walk_left={observed_walk_left}, walk_right={observed_walk_right}, aaah={observed_aaah}, digging={observed_digging}")
            return False
        return True

    def lemming_rules(self, bump_left, bump_right, ground, dig, current_state, fall_counter):
        walk_left = 0
        walk_right = 0
        aaah = 0
        digging = 0

        if current_state == 'walk_left':
            if bump_left or bump_right:
                current_state = 'walk_right'
            elif not ground:
                current_state = 'falling'
                fall_counter = 1
            elif dig and ground:
                current_state = 'digging_left'

        elif current_state == 'walk_right':
            if bump_left or bump_right:
                current_state = 'walk_left'
            elif not ground:
                current_state = 'falling'
                fall_counter = 1
            elif dig and ground:
                current_state = 'digging_right'

        elif current_state == 'falling':
            if ground:
                if fall_counter > 20:
                    current_state = 'splattered'
                else:
                    if bump_left or bump_right:
                        current_state = 'walk_left' if bump_left else 'walk_right'
                    else:
                        current_state = 'walk_left' if (bump_left or bump_right) else 'walk_right'
                fall_counter = 0  # Reset fall counter when hitting the ground
            else:
                fall_counter += 1

        elif current_state == 'digging_left':
            if not ground:
                current_state = 'falling'
                fall_counter = 1
            elif bump_left or bump_right:
                current_state = 'walk_right'
            elif not dig:
                current_state = 'walk_left'
            else:
                walk_left = 1
                digging = 1

        elif current_state == 'digging_right':
            if not ground:
                current_state = 'falling'
                fall_counter = 1
            elif bump_left or bump_right:
                current_state = 'walk_left'
            elif not dig:
                current_state = 'walk_right'
            else:
                walk_right = 1
                digging = 1

        elif current_state == 'splattered':
            pass  # No state change, all outputs remain 0

        if current_state == 'walk_left':
            walk_left = 1
        elif current_state == 'walk_right':
            walk_right = 1
        elif current_state == 'falling':
            aaah = 1
        elif current_state == 'digging_left':
            walk_left = 1
            digging = 1
        elif current_state == 'digging_right':
            walk_right = 1
            digging = 1
        elif current_state == 'splattered':
            walk_left = 0
            walk_right = 0
            aaah = 0
            digging = 0

        return walk_left, walk_right, aaah, digging, current_state, fall_counter
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
