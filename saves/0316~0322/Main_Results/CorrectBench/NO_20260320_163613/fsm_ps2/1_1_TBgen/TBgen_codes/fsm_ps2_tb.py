class GoldenDUT:
    def __init__(self):
        self.state_reg = 'IDLE'
        self.byte_count_reg = 0
        self.done_reg = 0

    def load(self, signal_vector):
        in_signal = signal_vector['in']
        reset = signal_vector['reset']

        if reset:
            self.state_reg = 'IDLE'
            self.byte_count_reg = 0
            self.done_reg = 0
        else:
            if self.state_reg == 'IDLE':
                if in_signal & 0b1000:  # Check if in[3] = 1
                    self.state_reg = 'BYTE1'
                    self.byte_count_reg = 1
                else:
                    self.byte_count_reg = 0
            elif self.state_reg == 'BYTE1':
                if in_signal & 0b1000:  # Check if in[3] = 1
                    self.state_reg = 'BYTE1'
                    self.byte_count_reg = 1
                else:
                    self.state_reg = 'BYTE2'
                    self.byte_count_reg += 1
            elif self.state_reg == 'BYTE2':
                if in_signal & 0b1000:  # Check if in[3] = 1
                    self.state_reg = 'BYTE1'
                    self.byte_count_reg = 1
                else:
                    self.state_reg = 'BYTE3'
                    self.byte_count_reg += 1
            elif self.state_reg == 'BYTE3':
                if in_signal & 0b1000:  # Check if in[3] = 1
                    self.state_reg = 'BYTE1'
                    self.byte_count_reg = 1
                else:
                    self.state_reg = 'IDLE'
                    self.byte_count_reg = 0
                    self.done_reg = 1  # Signal 'done' in the next cycle
            else:
                raise ValueError("Invalid state")

    def check(self, signal_vector):
        expected_done = self.done_reg
        observed_done = signal_vector['done']

        if expected_done != observed_done:
            print(f"Scenario: {signal_vector['scenario']}, expected: done={expected_done}, observed: done={observed_done}")
            return False
        else:
            return True

    def update_done(self):
        self.done_reg = 0  # Reset the 'done' signal for the next cycle

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
