class GoldenDUT:
    def __init__(self):
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0
        self.ground_reg = 1
        self.prev_walk_left_reg = 0
        self.prev_walk_right_reg = 0
        self.prev_digging_reg = 0

    def load(self, signal_vector):
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']
        areset = signal_vector['areset']

        if areset:
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg = 0
            self.ground_reg = 1
            self.prev_walk_left_reg = 0
            self.prev_walk_right_reg = 0
            self.prev_digging_reg = 0
        else:
            if not ground:
                # Store the current state before falling
                if self.fall_counter_reg == 0:
                    self.prev_walk_left_reg = self.walk_left_reg
                    self.prev_walk_right_reg = self.walk_right_reg
                    self.prev_digging_reg = self.digging_reg

                self.aaah_reg = 1
                self.digging_reg = 0
                self.fall_counter_reg += 1
                self.walk_left_reg = 0
                self.walk_right_reg = 0
            else:
                if self.fall_counter_reg > 20:
                    self.walk_left_reg = 0
                    self.walk_right_reg = 0
                    self.aaah_reg = 0
                    self.digging_reg = 0
                    self.fall_counter_reg = 0
                else:
                    self.aaah_reg = 0
                    self.fall_counter_reg = 0
                    if self.fall_counter_reg > 0:
                        # Restore the previous state after falling
                        self.walk_left_reg = self.prev_walk_left_reg
                        self.walk_right_reg = self.prev_walk_right_reg
                        self.digging_reg = self.prev_digging_reg
                    else:
                        if dig and ground:
                            self.digging_reg = 1
                            self.walk_left_reg = 0
                            self.walk_right_reg = 0
                        else:
                            self.digging_reg = 0
                            if bump_left and not bump_right:
                                self.walk_left_reg = 0
                                self.walk_right_reg = 1
                            elif bump_right and not bump_left:
                                self.walk_left_reg = 1
                                self.walk_right_reg = 0
                            elif bump_left and bump_right:
                                if self.walk_left_reg:
                                    self.walk_left_reg = 0
                                    self.walk_right_reg = 1
                                else:
                                    self.walk_left_reg = 1
                                    self.walk_right_reg = 0
                            else:
                                pass  # No change in direction

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
