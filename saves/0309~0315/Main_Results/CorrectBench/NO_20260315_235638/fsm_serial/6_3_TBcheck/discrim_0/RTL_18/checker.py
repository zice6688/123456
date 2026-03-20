class GoldenDUT:
    def __init__(self):
        self.state_reg = 'IDLE'
        self.bit_count_reg = 0
        self.data_bits_reg = []
        self.done_reg = 0
        self.reset_reg = 0

    def load(self, signal_vector):
        in_signal = signal_vector['in']
        reset_signal = signal_vector['reset']

        if reset_signal:
            self.reset()
        else:
            self.update_state(in_signal)

    def update_state(self, in_signal):
        if self.state_reg == 'IDLE':
            if in_signal == 0:  # Start bit detected
                self.state_reg = 'RECEIVING_DATA'
                self.bit_count_reg = 0
                self.data_bits_reg = []
            self.done_reg = 0

        elif self.state_reg == 'RECEIVING_DATA':
            self.data_bits_reg.append(in_signal)
            self.bit_count_reg += 1
            if self.bit_count_reg == 8:  # 8 data bits received
                self.state_reg = 'CHECK_STOP_BIT'
            self.done_reg = 0

        elif self.state_reg == 'CHECK_STOP_BIT':
            if in_signal == 1:  # Stop bit is correct
                self.state_reg = 'IDLE'
                self.done_reg = 1
            else:  # Stop bit is incorrect, wait for a stop bit
                self.state_reg = 'WAIT_FOR_STOP_BIT'
            self.done_reg = 0

        elif self.state_reg == 'WAIT_FOR_STOP_BIT':
            if in_signal == 1:  # Stop bit found
                self.state_reg = 'IDLE'
            self.done_reg = 0

    def reset(self):
        self.state_reg = 'IDLE'
        self.bit_count_reg = 0
        self.data_bits_reg = []
        self.done_reg = 0

    def check(self, signal_vector):
        observed_done = signal_vector['done']
        expected_done = self.done_reg

        if observed_done != expected_done:
            print(f"Scenario: {signal_vector['scenario']}, expected: done={expected_done}, observed: done={observed_done}")
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
