class GoldenDUT:
    WL = 0b0001  # Walking Left
    WR = 0b0010  # Walking Right
    F = 0b0100   # Falling
    D = 0b1000   # Digging
    S = 0b10000  # Splattered

    def __init__(self):
        self.state_reg = self.WL
        self.walk_left_reg = 0
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.state_reg = self.WL
            self.fall_counter_reg = 0
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
        else:
            self.state_reg, self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg = self.next_state_and_outputs(bump_left, bump_right, ground, dig)

    def check(self, signal_vector):
        walk_left_observed = signal_vector['walk_left']
        walk_right_observed = signal_vector['walk_right']
        aaah_observed = signal_vector['aaah']
        digging_observed = signal_vector['digging']

        if (self.walk_left_reg != walk_left_observed or
            self.walk_right_reg != walk_right_observed or
            self.aaah_reg != aaah_observed or
            self.digging_reg != digging_observed):
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_left={self.walk_left_reg}, walk_right={self.walk_right_reg}, aaah={self.aaah_reg}, digging={self.digging_reg}")
            print(f"Observed: walk_left={walk_left_observed}, walk_right={walk_right_observed}, aaah={aaah_observed}, digging={digging_observed}")
            return False
        return True

    def next_state_and_outputs(self, bump_left, bump_right, ground, dig):
        walk_left = 0
        walk_right = 0
        aaah = 0
        digging = 0

        if self.state_reg == self.WL:
            if bump_left:
                self.state_reg = self.WR
            elif not ground:
                self.state_reg = self.F
                self.fall_counter_reg = 0
            elif dig and ground:
                self.state_reg = self.D
            else:
                walk_left = 1
        elif self.state_reg == self.WR:
            if bump_right:
                self.state_reg = self.WL
            elif not ground:
                self.state_reg = self.F
                self.fall_counter_reg = 0
            elif dig and ground:
                self.state_reg = self.D
            else:
                walk_right = 1
        elif self.state_reg == self.F:
            if ground:
                if self.fall_counter_reg > 20:
                    self.state_reg = self.S
                else:
                    if self.state_reg == self.WL:
                        self.state_reg = self.WL
                    elif self.state_reg == self.WR:
                        self.state_reg = self.WR
            else:
                self.fall_counter_reg += 1
                aaah = 1
        elif self.state_reg == self.D:
            if not ground:
                self.state_reg = self.F
                self.fall_counter_reg = 0
                aaah = 1
            else:
                digging = 1
        elif self.state_reg == self.S:
            pass  # Stay in splattered state

        return self.state_reg, walk_left, walk_right, aaah, digging
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
