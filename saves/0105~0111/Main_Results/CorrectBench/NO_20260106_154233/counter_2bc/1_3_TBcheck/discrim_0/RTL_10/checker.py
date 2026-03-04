class GoldenDUT:
    def __init__(self):
        self.state_reg = 0b01  # Initial state after reset

    def load(self, signal_vector):
        areset = signal_vector['areset']
        train_valid = signal_vector['train_valid']
        train_taken = signal_vector['train_taken']

        if areset:
            self.state_reg = 0b01  # Reset to weakly not-taken state (2'b01)
        elif train_valid:
            if train_taken:
                if self.state_reg < 0b11:  # Increment if less than maximum value (2'b11)
                    self.state_reg += 1
            else:
                if self.state_reg > 0b00:  # Decrement if greater than minimum value (2'b00)
                    self.state_reg -= 1

    def check(self, signal_vector):
        expected_state = self.state_reg
        observed_state = signal_vector['state']

        if expected_state == observed_state:
            return True
        else:
            print(f"Scenario: {signal_vector['scenario']}, expected: state={expected_state}, observed: state={observed_state}")
            return False

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
