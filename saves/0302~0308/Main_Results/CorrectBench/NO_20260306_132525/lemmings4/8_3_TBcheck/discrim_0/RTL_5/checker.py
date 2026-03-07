class GoldenDUT:
    WALK_LEFT = 0b0001
    WALK_RIGHT = 0b0010
    FALLING = 0b0100
    DIGGING = 0b1000
    SPLATTER = 0b10000

    def __init__(self):
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
        else:
            if self.current_state_reg == self.WALK_LEFT:
                if bump_left:
                    self.current_state_reg = self.WALK_RIGHT
                elif not ground:
                    self.current_state_reg = self.FALLING
                    self.fall_counter_reg = 0
                elif dig and ground:
                    self.current_state_reg = self.DIGGING
            elif self.current_state_reg == self.WALK_RIGHT:
                if bump_right:
                    self.current_state_reg = self.WALK_LEFT
                elif not ground:
                    self.current_state_reg = self.FALLING
                    self.fall_counter_reg = 0
                elif dig and ground:
                    self.current_state_reg = self.DIGGING
            elif self.current_state_reg == self.FALLING:
                if ground:
                    if self.fall_counter_reg > 20:
                        self.current_state_reg = self.SPLATTER
                    else:
                        if self.current_state_reg == self.WALK_LEFT or self.current_state_reg == self.WALK_RIGHT:
                            self.current_state_reg = self.WALK_LEFT if (self.current_state_reg == self.WALK_LEFT) else self.WALK_RIGHT
                else:
                    self.fall_counter_reg += 1
            elif self.current_state_reg == self.DIGGING:
                if not ground:
                    self.current_state_reg = self.FALLING
                    self.fall_counter_reg = 0
                elif ground:
                    self.current_state_reg = self.WALK_LEFT if (self.current_state_reg == self.WALK_LEFT) else self.WALK_RIGHT
            elif self.current_state_reg == self.SPLATTER:
                pass  # No further transitions from SPLATTER

        self.update_outputs()

    def update_outputs(self):
        self.walk_left_reg = 1 if self.current_state_reg == self.WALK_LEFT else 0
        self.walk_right_reg = 1 if self.current_state_reg == self.WALK_RIGHT else 0
        self.aaah_reg = 1 if self.current_state_reg == self.FALLING else 0
        self.digging_reg = 1 if self.current_state_reg == self.DIGGING else 0

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
