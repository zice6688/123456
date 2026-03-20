class GoldenDUT:
    def __init__(self):
        self.state_reg = 'IDLE'
        self.bit_count_reg = 0
        self.data_bits_reg = []
        self.done_reg = 0

    def load(self, signal_vector):
        in_bit = signal_vector['in']
        reset = signal_vector['reset']

        if reset:
            self.state_reg = 'IDLE'
            self.bit_count_reg = 0
            self.data_bits_reg = []
            self.done_reg = 0
            return

        if self.state_reg == 'IDLE':
            if in_bit == 0:  # Start bit detected
                self.state_reg = 'RECEIVING_DATA'
                self.bit_count_reg = 0
                self.data_bits_reg = []
        elif self.state_reg == 'RECEIVING_DATA':
            self.data_bits_reg.append(in_bit)
            self.bit_count_reg += 1
            if self.bit_count_reg == 8:
                self.state_reg = 'VERIFY_STOP_BIT'
        elif self.state_reg == 'VERIFY_STOP_BIT':
            if in_bit == 1:  # Correct stop bit
                self.state_reg = 'IDLE'
                self.done_reg = 1  # Set done to 1
            else:  # Incorrect stop bit
                self.state_reg = 'WAIT_FOR_STOP_BIT'
                self.done_reg = 0  # Ensure done is 0
        elif self.state_reg == 'WAIT_FOR_STOP_BIT':
            if in_bit == 1:  # Correct stop bit found
                self.state_reg = 'IDLE'
                self.done_reg = 0  # Reset done to 0
            else:
                self.done_reg = 0  # Ensure done is 0

    def check(self, signal_vector):
        expected_done = self.done_reg
        observed_done = signal_vector['done']

        if expected_done != observed_done:
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
