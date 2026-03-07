class GoldenDUT:
    def __init__(self):
        # Initialize any internal state if needed
        pass

    def load(self, signal_vector):
        # Load the input signal and compute the expected output
        in_value = signal_vector['in']
        expected_out = self.dut_rules(in_value)
        return expected_out

    def check(self, signal_vector):
        # Get the expected output from the load method
        expected_out = self.load(signal_vector)
        # Compare the expected output with the actual output from the DUT
        actual_out = signal_vector['out']
        return expected_out == actual_out

    def dut_rules(self, input_value):
        # The DUT is supposed to behave like a wire, so the output should be the same as the input
        return input_value

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
