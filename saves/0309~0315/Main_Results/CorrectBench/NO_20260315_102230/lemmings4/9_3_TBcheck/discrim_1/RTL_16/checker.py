class GoldenDUT:
    WALK_LEFT = 0b0001
    WALK_RIGHT = 0b0010
    FALLING = 0b0100
    DIGGING = 0b1000
    SPLATTERED = 0b0000

    def __init__(self):
        self.state_reg = self.WALK_LEFT
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_count_reg = 0
        self.previous_direction = self.WALK_LEFT  # Track the direction before falling

    def load(self, signal_vector):
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        if areset:
            self.state_reg = self.WALK_LEFT
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_count_reg = 0
            self.previous_direction = self.WALK_LEFT
        else:
            self.state_reg, self.walk_left_reg, self.walk_right_reg, self.aaah_reg, self.digging_reg = self.get_next_state(
                self.state_reg, bump_left, bump_right, ground, dig, self.fall_count_reg)
            if self.state_reg == self.FALLING:
                self.fall_count_reg += 1
            else:
                self.fall_count_reg = 0

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

    def get_next_state(self, current_state, bump_left, bump_right, ground, dig, fall_count):
        if current_state == self.WALK_LEFT:
            if bump_left:
                return self.WALK_RIGHT, 0, 1, 0, 0
            elif bump_right:
                return self.WALK_LEFT, 1, 0, 0, 0
            elif not ground:
                self.previous_direction = self.WALK_LEFT  # Update previous direction
                return self.FALLING, 0, 0, 1, 0
            elif dig and ground:
                return self.DIGGING, 0, 0, 0, 1
            else:
                return self.WALK_LEFT, 1, 0, 0, 0
        
        elif current_state == self.WALK_RIGHT:
            if bump_left:
                return self.WALK_RIGHT, 0, 1, 0, 0
            elif bump_right:
                return self.WALK_LEFT, 1, 0, 0, 0
            elif not ground:
                self.previous_direction = self.WALK_RIGHT  # Update previous direction
                return self.FALLING, 0, 0, 1, 0
            elif dig and ground:
                return self.DIGGING, 0, 0, 0, 1
            else:
                return self.WALK_RIGHT, 0, 1, 0, 0
        
        elif current_state == self.FALLING:
            if ground and fall_count > 20:
                return self.SPLATTERED, 0, 0, 0, 0
            elif ground:
                if self.previous_direction == self.WALK_LEFT:
                    return self.WALK_LEFT, 1, 0, 0, 0
                else:
                    return self.WALK_RIGHT, 0, 1, 0, 0
            else:
                return self.FALLING, 0, 0, 1, 0
        
        elif current_state == self.DIGGING:
            if not ground:
                self.previous_direction = self.WALK_LEFT  # Update previous direction
                return self.FALLING, 0, 0, 1, 0
            else:
                return self.DIGGING, 0, 0, 0, 1
        
        elif current_state == self.SPLATTERED:
            return self.SPLATTERED, 0, 0, 0, 0
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
