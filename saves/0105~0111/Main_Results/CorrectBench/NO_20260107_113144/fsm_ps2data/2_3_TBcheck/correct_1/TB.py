import numpy as np

class GoldenDUT:
    def __init__(self):
        self.state_reg = 'IDLE'
        self.message_bytes_reg = []
        self.out_bytes_reg = 0x000000
        self.done_reg = False
        self.reset_reg = False
        self.in_reg = 0

    def load(self, signal_vector):
        self.reset_reg = signal_vector['reset']
        self.in_reg = signal_vector['in']

        if self.reset_reg:
            self.state_reg = 'IDLE'
            self.message_bytes_reg = []
            self.out_bytes_reg = 0x000000
            self.done_reg = False
        else:
            self.process_input()

    def check(self, signal_vector):
        expected_out_bytes = self.out_bytes_reg
        expected_done = self.done_reg
        observed_out_bytes = signal_vector['out_bytes']
        observed_done = signal_vector['done']

        if (expected_out_bytes != observed_out_bytes) or (expected_done != observed_done):
            print(f"Scenario: {signal_vector['scenario']}, expected: out_bytes={expected_out_bytes:06x}, done={expected_done}, observed: out_bytes={observed_out_bytes:06x}, done={observed_done}")
            return False
        return True

    def process_input(self):
        if self.state_reg == 'IDLE':
            if (self.in_reg & 0b10000) != 0:
                self.state_reg = 'RECEIVING'
                self.message_bytes_reg.append(self.in_reg)
        elif self.state_reg == 'RECEIVING':
            self.message_bytes_reg.append(self.in_reg)
            if len(self.message_bytes_reg) == 3:
                self.state_reg = 'DONE'
                self.out_bytes_reg = (self.message_bytes_reg[0] << 16) | (self.message_bytes_reg[1] << 8) | self.message_bytes_reg[2]
                self.done_reg = True
                self.message_bytes_reg = []
                self.state_reg = 'IDLE'
            else:
                self.done_reg = False
                self.out_bytes_reg = 0x000000
        else:
            self.done_reg = False
            self.out_bytes_reg = 0x000000
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
