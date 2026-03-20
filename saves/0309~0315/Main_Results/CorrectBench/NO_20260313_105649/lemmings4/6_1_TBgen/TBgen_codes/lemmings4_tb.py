class GoldenDUT:
    def __init__(self):
        self.state_reg = 0b0001  # Initial state: walking left
        self.fall_count_reg = 0
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
            self.state_reg = 0b0001  # Asynchronous reset to walking left
            self.fall_count_reg = 0
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        else:
            next_state = self.get_next_state(bump_left, bump_right, ground, dig)
            self.update_state(next_state, ground)

    def check(self, signal_vector):
        walk_left_observed = signal_vector['walk_left']
        walk_right_observed = signal_vector['walk_right']
        aaah_observed = signal_vector['aaah']
        digging_observed = signal_vector['digging']

        if (self.walk_left_reg != walk_left_observed or
                self.walk_right_reg != walk_right_observed or
                self.aaah_reg != aaah_observed or
                self.digging_reg != digging_observed):
            print(f"Scenario: {signal_vector['scenario']}, "
                  f"expected: walk_left={self.walk_left_reg}, walk_right={self.walk_right_reg}, "
                  f"aaah={self.aaah_reg}, digging={self.digging_reg}, "
                  f"observed: walk_left={walk_left_observed}, walk_right={walk_right_observed}, "
                  f"aaah={aaah_observed}, digging={digging_observed}")
            return False
        return True

    def get_next_state(self, bump_left, bump_right, ground, dig):
        if self.state_reg == 0b0001:  # Walking left
            if bump_left:
                return 0b0010  # Walking right
            elif ground == 0:
                return 0b0100  # Falling
            elif dig and ground == 1:
                return 0b1000  # Digging
            else:
                return 0b0001  # Stay in walking left
        elif self.state_reg == 0b0010:  # Walking right
            if bump_right:
                return 0b0001  # Walking left
            elif ground == 0:
                return 0b0100  # Falling
            elif dig and ground == 1:
                return 0b1000  # Digging
            else:
                return 0b0010  # Stay in walking right
        elif self.state_reg == 0b0100:  # Falling
            if ground == 1:
                if self.fall_count_reg > 20:
                    return 0b0000  # Splattered
                else:
                    return 0b0001  # Resume walking left
            else:
                return 0b0100  # Continue falling
        elif self.state_reg == 0b1000:  # Digging
            if ground == 0:
                return 0b0100  # Falling
            else:
                return 0b1000  # Stay in digging
        elif self.state_reg == 0b0000:  # Splattered
            return 0b0000  # Stay in splattered state
        else:
            raise ValueError("Invalid state")

    def update_state(self, next_state, ground):
        self.state_reg = next_state
        if self.state_reg == 0b0001:  # Walking left
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        elif self.state_reg == 0b0010:  # Walking right
            self.walk_left_reg = 0
            self.walk_right_reg = 1
            self.aaah_reg = 0
            self.digging_reg = 0
        elif self.state_reg == 0b0100:  # Falling
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 1
            self.digging_reg = 0
            if ground == 0:
                self.fall_count_reg += 1
            else:
                self.fall_count_reg = 0
        elif self.state_reg == 0b1000:  # Digging
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 1
        elif self.state_reg == 0b0000:  # Splattered
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0

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
