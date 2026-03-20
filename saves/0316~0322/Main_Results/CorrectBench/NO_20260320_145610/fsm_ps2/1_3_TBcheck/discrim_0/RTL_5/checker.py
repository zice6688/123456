class GoldenDUT:
    def __init__(self):
        self.state_reg = 'IDLE'
        self.count_reg = 0
        self.done_reg = False

    def load(self, signal_vector):
        in_signal = signal_vector['in']
        reset_signal = signal_vector['reset']

        if reset_signal:
            self.state_reg = 'IDLE'
            self.count_reg = 0
            self.done_reg = False
        else:
            if self.state_reg == 'IDLE':
                if (in_signal & 0b00001000) == 0b00001000:
                    self.state_reg = 'COUNTING'
                    self.count_reg = 1
                    self.done_reg = False
            elif self.state_reg == 'COUNTING':
                self.count_reg += 1
                if self.count_reg == 3:
                    self.state_reg = 'DONE'
                    self.done_reg = True
                else:
                    self.done_reg = False
            elif self.state_reg == 'DONE':
                if (in_signal & 0b00001000) == 0b00001000:
                    self.state_reg = 'COUNTING'
                    self.count_reg = 1
                    self.done_reg = False
                else:
                    self.state_reg = 'IDLE'
                    self.count_reg = 0
                    self.done_reg = False

    def check(self, signal_vector):
        done_observed = signal_vector['done']
        expected_done = self.done_reg

        if expected_done != done_observed:
            print(f"Scenario: {signal_vector['scenario']}, expected: done={expected_done}, observed: done={done_observed}")
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
