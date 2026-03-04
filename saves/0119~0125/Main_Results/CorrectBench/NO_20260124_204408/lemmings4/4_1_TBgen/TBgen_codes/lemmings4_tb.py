class GoldenDUT:
    def __init__(self):
        # Internal state registers (Moore FSM state variables)
        self.walk_left_reg = 1   # initial state: walking left (areset is active high async, but init before any areset)
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.fall_counter_reg = 0
        self.splattered_reg = False

        # Note: no need to store 'last_direction_before_fall_or_dig' separately — it's preserved in walk_left_reg/walk_right_reg
        # because during fall/dig, those values remain unchanged and serve as memory.

    def _update_state(self, bump_left, bump_right, ground, dig, areset):
        # This method computes *next* state and outputs based on current state and inputs.
        # It implements the exact precedence: fall > dig > bump, with splatter logic.
        # Returns: (next_walk_left, next_walk_right, next_aaah, next_digging, next_fall_counter, next_splattered)

        # Handle asynchronous reset (active-high, edge-triggered in RTL, but here we model it as level-sensitive for simplicity in golden model,
        # since signal_vector contains the *level* of areset at this cycle; and per problem: "areset is positive edge triggered asynchronous reset"
        # However, in golden behavioral modeling for verification, we treat areset=1 as forcing immediate reset *this cycle*,
        # because exported vectors reflect sampled values after reset assertion — i.e., if areset==1, FSM is in reset state.
        if areset:
            return (1, 0, 0, 0, 0, False)

        # Current state
        curr_walk_left = self.walk_left_reg
        curr_walk_right = self.walk_right_reg
        curr_aaah = self.aaah_reg
        curr_digging = self.digging_reg
        curr_fall_counter = self.fall_counter_reg
        curr_splattered = self.splattered_reg

        # --- PRECEDENCE LAYER 1: FALL (ground == 0) ---
        if ground == 0:
            # Falling starts or continues
            walk_left = 0
            walk_right = 0
            aaah = 1
            digging = 0
            new_fall_counter = curr_fall_counter + 1
            new_splattered = curr_splattered
            return (walk_left, walk_right, aaah, digging, new_fall_counter, new_splattered)

        # ground == 1 → NOT falling *this cycle*
        if curr_splattered:
            # Splattered is irreversible
            return (0, 0, 0, 0, 0, True)

        elif curr_aaah == 1:
            # Was falling last cycle (so curr_fall_counter >= 1), and ground just returned → check splatter
            if curr_fall_counter > 20:
                # Splatter triggered *on this cycle*
                return (0, 0, 0, 0, 0, True)
            else:
                # Resume walking in same direction as before the fall started
                # curr_walk_* hold that direction (they were not updated during fall)
                return (curr_walk_left, curr_walk_right, 0, 0, 0, False)

        elif curr_digging == 1:
            # Was digging last cycle, ground=1 now → digging ends; resume walking in same direction
            return (curr_walk_left, curr_walk_right, 0, 0, 0, False)

        else:
            # Normal walking state (not falling, not digging, not splattered, ground==1)
            # --- PRECEDENCE LAYER 2: DIG (only if ground==1 AND not falling AND not splattered — already satisfied)
            if dig == 1:
                return (0, 0, 0, 1, 0, False)
            else:
                # --- PRECEDENCE LAYER 3: DIRECTION SWITCH (bump logic)
                # Current direction is (curr_walk_left, curr_walk_right)
                if bump_left == 1 and bump_right == 1:
                    # toggle direction
                    walk_left = curr_walk_right
                    walk_right = curr_walk_left
                elif bump_left == 1 and bump_right == 0:
                    # go right
                    walk_left = 0
                    walk_right = 1
                elif bump_right == 1 and bump_left == 0:
                    # go left
                    walk_left = 1
                    walk_right = 0
                else:
                    # no bump: keep current direction
                    walk_left = curr_walk_left
                    walk_right = curr_walk_right
                return (walk_left, walk_right, 0, 0, 0, False)

    def load(self, signal_vector):
        # Extract inputs
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        # Compute next state and outputs
        (next_walk_left, next_walk_right, next_aaah, next_digging, next_fall_counter, next_splattered) = \
            self._update_state(bump_left, bump_right, ground, dig, areset)

        # Update registers (state transition happens *after* output evaluation — Moore)
        self.walk_left_reg = next_walk_left
        self.walk_right_reg = next_walk_right
        self.aaah_reg = next_aaah
        self.digging_reg = next_digging
        self.fall_counter_reg = next_fall_counter
        self.splattered_reg = next_splattered

    def check(self, signal_vector):
        # Expected outputs are the *current* register values (Moore: outputs depend only on current state)
        expected_walk_left = self.walk_left_reg
        expected_walk_right = self.walk_right_reg
        expected_aaah = self.aaah_reg
        expected_digging = self.digging_reg

        # Observed outputs from DUT (present in signal_vector)
        observed_walk_left = signal_vector['walk_left']
        observed_walk_right = signal_vector['walk_right']
        observed_aaah = signal_vector['aaah']
        observed_digging = signal_vector['digging']

        # Compare
        ok = True
        scenario = signal_vector['scenario']

        if expected_walk_left != observed_walk_left:
            print(f"Scenario: {scenario}, expected: walk_left={expected_walk_left}, observed walk_left={observed_walk_left}")
            ok = False

        if expected_walk_right != observed_walk_right:
            print(f"Scenario: {scenario}, expected: walk_right={expected_walk_right}, observed walk_right={observed_walk_right}")
            ok = False

        if expected_aaah != observed_aaah:
            print(f"Scenario: {scenario}, expected: aaah={expected_aaah}, observed aaah={observed_aaah}")
            ok = False

        if expected_digging != observed_digging:
            print(f"Scenario: {scenario}, expected: digging={expected_digging}, observed digging={observed_digging}")
            ok = False

        return ok

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
