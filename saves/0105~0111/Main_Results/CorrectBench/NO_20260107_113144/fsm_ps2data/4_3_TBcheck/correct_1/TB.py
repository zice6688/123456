import numpy as np

class GoldenDUT:
    def __init__(self):
        self.state_reg = 'SEARCH'
        self.message_buffer_reg = [0, 0, 0]
        self.out_bytes_reg = 0
        self.done_reg = 0
        self.reset_reg = 0

    def load(self, signal_vector):
        in_signal = signal_vector['in']
        reset_signal = signal_vector['reset']

        if reset_signal:
            self.state_reg = 'SEARCH'
            self.message_buffer_reg = [0, 0, 0]
            self.out_bytes_reg = 0
            self.done_reg = 0
        else:
            if self.state_reg == 'SEARCH':
                if (in_signal & 0x10) == 0x10:
                    self.message_buffer_reg[0] = in_signal
                    self.state_reg = 'RECEIVE_2ND_BYTE'
            elif self.state_reg == 'RECEIVE_2ND_BYTE':
                self.message_buffer_reg[1] = in_signal
                self.state_reg = 'RECEIVE_3RD_BYTE'
            elif self.state_reg == 'RECEIVE_3RD_BYTE':
                self.message_buffer_reg[2] = in_signal
                self.out_bytes_reg = (self.message_buffer_reg[0] << 16) | (self.message_buffer_reg[1] << 8) | self.message_buffer_reg[2]
                self.done_reg = 1
                # Reset the FSM after done is asserted
                self.state_reg = 'SEARCH'
                self.message_buffer_reg = [0, 0, 0]
                self.done_reg = 0

    def check(self, signal_vector):
        out_bytes_observed = signal_vector['out_bytes']
        done_observed = signal_vector['done']

        if self.done_reg != done_observed or (self.done_reg and self.out_bytes_reg != out_bytes_observed):
            print(f"Scenario: {signal_vector['scenario']}, expected: out_bytes={self.out_bytes_reg}, done={self.done_reg}, observed: out_bytes={out_bytes_observed}, done={done_observed}")
            return False
        return True

# Example usage
if __name__ == "__main__":
    golden_dut = GoldenDUT()
    signal_vector = {
        'in': 0xED,
        'reset': 0,
        'out_bytes': 0xED8CF9,
        'done': 1,
        'scenario': 4
    }
    golden_dut.load(signal_vector)
    result = golden_dut.check(signal_vector)
    print(f"Check result: {result}")
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
