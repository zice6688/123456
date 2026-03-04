class GoldenDUT:
    def __init__(self):
        self.state = 0

    def load(self, signal_vector):
        in_signal = signal_vector.get('in', 0)
        expected_output = self.compute_expected_output(in_signal)
        return expected_output

    def check(self, signal_vector):
        expected_output = self.load(signal_vector)
        actual_output = signal_vector.get('out', 0)
        return expected_output == actual_output

    def compute_expected_output(self, in_signal):
        # Since the DUT is a wire, the output should be exactly the same as the input
        return in_signal

def check_dut(vectors_in):
    golden_dut = GoldenDUT()
    failed_scenarios = []
    for vector in vectors_in:
        check_pass = golden_dut.check(vector)
        if check_pass:
            print(f"Passed; vector: {vector}")
        else:
            print(f"Failed; vector: {vector}")
            failed_scenarios.append(vector["scenario"])
    return failed_scenarios

def SignalTxt_to_dictlist(txt:str):
    lines = txt.strip().split("\n")
    signals = []
    for line in lines:
        signal = {}
        line = line.strip().split(", ")
        for item in line:
            if "scenario" in item:
                item = item.split(": ")
                signal["scenario"] = item[1]
            else:
                item = item.split(" = ")
                key = item[0]
                value = item[1]
                if "x" not in value and "z" not in value:
                    signal[key] = int(value)
                else:
                    signal[key] = value 
        signals.append(signal)
    return signals
with open("TBout.txt", "r") as f:
    txt = f.read()
vectors_in = SignalTxt_to_dictlist(txt)
tb_pass = check_dut(vectors_in)
print(tb_pass)
