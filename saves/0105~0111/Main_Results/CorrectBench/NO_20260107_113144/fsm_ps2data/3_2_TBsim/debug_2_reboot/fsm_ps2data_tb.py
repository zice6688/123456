import numpy as np

class GoldenDUT:
    def __init__(self):
        self.state_reg = 'IDLE'
        self.out_bytes_reg = 0x000000
        self.done_reg = 0
        self.message_buffer_reg = [0, 0, 0]
        self.message_count_reg = 0
        self.reset_reg = 0

    def load(self, signal_vector):
        in_byte = signal_vector['in']
        reset = signal_vector['reset']

        if reset:
            self.state_reg = 'IDLE'
            self.out_bytes_reg = 0x000000
            self.done_reg = 0
            self.message_buffer_reg = [0, 0, 0]
            self.message_count_reg = 0
            self.reset_reg = 1
        else:
            self.reset_reg = 0
            if self.state_reg == 'IDLE':
                if (in_byte & 0b10000) == 0b10000:  # Check if in[3] = 1
                    self.state_reg = 'RECEIVING'
                    self.message_buffer_reg[0] = in_byte
                    self.message_count_reg = 1
                else:
                    pass
            elif self.state_reg == 'RECEIVING':
                if self.message_count_reg == 1:
                    self.message_buffer_reg[1] = in_byte
                    self.message_count_reg += 1
                elif self.message_count_reg == 2:
                    self.message_buffer_reg[2] = in_byte
                    self.message_count_reg += 1
                    self.out_bytes_reg = (self.message_buffer_reg[0] << 16) | (self.message_buffer_reg[1] << 8) | self.message_buffer_reg[2]
                    self.done_reg = 1
                    self.state_reg = 'IDLE'
                else:
                    pass

    def check(self, signal_vector):
        expected_out_bytes = self.out_bytes_reg
        expected_done = self.done_reg
        observed_out_bytes = signal_vector['out_bytes']
        observed_done = signal_vector['done']

        if (expected_out_bytes != observed_out_bytes) or (expected_done != observed_done):
            print(f"Scenario: {signal_vector['scenario']}, expected: out_bytes={expected_out_bytes:06x}, done={expected_done}, observed: out_bytes={observed_out_bytes:06x}, done={observed_done}")
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
