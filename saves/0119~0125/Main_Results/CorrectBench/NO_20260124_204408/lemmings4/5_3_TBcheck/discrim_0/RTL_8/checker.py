class GoldenDUT:
    def __init__(self):
        # Internal state registers (Moore outputs depend on these *before* update)
        self.state_reg = 'walk_left'           # str: 'walk_left', 'walk_right', 'falling', 'digging', 'splattered'
        self.pre_fall_dir_reg = 'walk_left'    # str: direction before falling started
        self.pre_dig_dir_reg = 'walk_left'     # str: direction before digging started
        self.fall_counter_reg = 0              # int: consecutive falling cycles (resets on exit from falling)
        self.splattered_reg = False            # bool: latched splatter flag (set once, cleared only by areset)

    def _update_state(self, bump_left, bump_right, ground, dig, areset):
        # ASYNCHRONOUS RESET: takes immediate effect THIS cycle — overrides all
        if areset:
            self.state_reg = 'walk_left'
            self.pre_fall_dir_reg = 'walk_left'
            self.pre_dig_dir_reg = 'walk_left'
            self.fall_counter_reg = 0
            self.splattered_reg = False
            return

        # SPLATTERED: irreversible except by reset
        if self.splattered_reg:
            return

        # Determine *next state* based on precedence: Fall > Dig > Bump
        next_state = self.state_reg
        next_pre_fall_dir = self.pre_fall_dir_reg
        next_pre_dig_dir = self.pre_dig_dir_reg
        next_fall_counter = self.fall_counter_reg

        # --- (1) FALL PRECEDENCE: ground == 0 triggers or continues falling
        if ground == 0:
            next_state = 'falling'
            # Record pre-fall direction only when *entering* fall from walking state
            if self.state_reg in ['walk_left', 'walk_right']:
                next_pre_fall_dir = self.state_reg
            # Increment fall counter only while falling (including continuation)
            next_fall_counter += 1
        else:
            # ground == 1: exiting fall or not in fall
            if self.state_reg == 'falling':
                # Exiting fall → check splatter on rising edge of ground
                if next_fall_counter >= 21:
                    self.splattered_reg = True
                    return  # splatter takes immediate effect; no further state updates this cycle
                else:
                    # Resume walking in pre-fall direction
                    next_state = next_pre_fall_dir
                    next_fall_counter = 0

        # --- (2) DIG PRECEDENCE: allowed only if ground==1 AND current state is walking AND dig==1
        if (ground == 1 and 
            self.state_reg in ['walk_left', 'walk_right'] and 
            dig == 1 and 
            self.state_reg != 'falling'):
            next_state = 'digging'
            next_pre_dig_dir = self.state_reg

        # --- (3) BUMP PRECEDENCE: only if ground==1, current state is walking, and no higher-precedence transition occurred
        # Note: we compare against *current* self.state_reg (not next_state) to ensure bump only applies when no fall/dig override happened
        if (ground == 1 and 
            self.state_reg in ['walk_left', 'walk_right'] and 
            self.state_reg != 'falling' and 
            self.state_reg != 'digging'):
            # Only apply bump logic if fall/dig did *not* change state this cycle
            if next_state == self.state_reg:
                if bump_left == 1 and bump_right == 0:
                    next_state = 'walk_right'
                elif bump_right == 1 and bump_left == 0:
                    next_state = 'walk_left'
                elif bump_left == 1 and bump_right == 1:
                    next_state = 'walk_right' if self.state_reg == 'walk_left' else 'walk_left'
                # else: no bump → state unchanged

        # Commit updates for *next* cycle
        self.state_reg = next_state
        self.pre_fall_dir_reg = next_pre_fall_dir
        self.pre_dig_dir_reg = next_pre_dig_dir
        self.fall_counter_reg = next_fall_counter

    def load(self, signal_vector):
        # Extract inputs
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        # Update internal state registers for *next* cycle based on current inputs
        self._update_state(bump_left, bump_right, ground, dig, areset)

    def check(self, signal_vector):
        # Compute Moore outputs based on *current* (pre-update) state
        walk_left_obs = signal_vector['walk_left']
        walk_right_obs = signal_vector['walk_right']
        aaah_obs = signal_vector['aaah']
        digging_obs = signal_vector['digging']

        # Expected outputs from current state (before load() updated it)
        if self.splattered_reg:
            walk_left_exp = 0
            walk_right_exp = 0
            aaah_exp = 0
            digging_exp = 0
        else:
            walk_left_exp = 1 if self.state_reg == 'walk_left' else 0
            walk_right_exp = 1 if self.state_reg == 'walk_right' else 0
            aaah_exp = 1 if self.state_reg == 'falling' else 0
            digging_exp = 1 if self.state_reg == 'digging' else 0

        # Compare
        passed = (
            walk_left_exp == walk_left_obs and
            walk_right_exp == walk_right_obs and
            aaah_exp == aaah_obs and
            digging_exp == digging_obs
        )

        if not passed:
            scenario = signal_vector['scenario']
            print(f"Scenario: {scenario}, expected: walk_left={walk_left_exp}, walk_right={walk_right_exp}, aaah={aaah_exp}, digging={digging_exp}")
            print(f"Scenario: {scenario}, observed: walk_left={walk_left_obs}, walk_right={walk_right_obs}, aaah={aaah_obs}, digging={digging_obs}")
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
