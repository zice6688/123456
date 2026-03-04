class GoldenDUT:
    def __init__(self):
        # Internal state registers (Moore FSM state variables)
        self.walk_left_reg = 1   # reset state: walk left
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.splattered_reg = 0
        self.fall_counter_reg = 0
        # Stored walking direction (preserved across fall/dig; same as walk_*_reg when not falling/digging)
        # But we maintain them explicitly as state to survive falling/digging
        self.stored_walk_left_reg = 1
        self.stored_walk_right_reg = 0

    def _update_state(self, bump_left, bump_right, ground, dig, areset):
        # Handle asynchronous reset (active high, edge-triggered in RTL but we model as level-sensitive for golden)
        if areset:
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.splattered_reg = 0
            self.fall_counter_reg = 0
            self.stored_walk_left_reg = 1
            self.stored_walk_right_reg = 0
            return

        # If splattered, all outputs stay 0 forever
        if self.splattered_reg:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg = 0
            return

        # Determine current logical mode from internal state
        is_walking = (self.stored_walk_left_reg == 1 or self.stored_walk_right_reg == 1) and self.aaah_reg == 0 and self.digging_reg == 0
        is_falling = (self.aaah_reg == 1) and (self.digging_reg == 0) and (not self.splattered_reg)
        is_digging = (self.digging_reg == 1) and (self.aaah_reg == 0) and (not self.splattered_reg)

        # PRECEDENCE LEVEL 1: FALL (ground == 0)
        if ground == 0:
            # Entering or continuing fall
            if is_falling:
                # Continuing fall: increment counter (already counted previous cycle)
                self.fall_counter_reg = min(self.fall_counter_reg + 1, 31)  # saturate at 5 bits
            else:
                # Just entered fall: reset counter to 1 (first fall cycle)
                self.fall_counter_reg = 1

            # During fall: outputs are aaah=1, others=0; stored direction remains unchanged
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 1
            self.digging_reg = 0
            return

        # PRECEDENCE LEVEL 2: GROUND == 1 → check DIG
        if is_digging:
            # Continuing dig: outputs remain digging=1, others=0; stored direction unchanged
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 1
            self.fall_counter_reg = 0  # reset fall counter on ground rise (but already ground=1)
            return

        # Start digging if eligible: ground==1, not falling, not splattered, dig==1, and not already digging
        if (not is_falling) and (not self.splattered_reg) and (dig == 1):
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 1
            self.fall_counter_reg = 0
            return

        # PRECEDENCE LEVEL 3: GROUND == 1, NOT DIGGING, NOT FALLING, NOT SPLATTERED → check BUMP
        if is_walking and (not self.splattered_reg) and (not is_falling) and (not is_digging):
            bump_effective = (bump_left == 1 or bump_right == 1)
            if bump_effective:
                # Flip stored direction
                if self.stored_walk_left_reg == 1:
                    self.stored_walk_left_reg = 0
                    self.stored_walk_right_reg = 1
                elif self.stored_walk_right_reg == 1:
                    self.stored_walk_left_reg = 1
                    self.stored_walk_right_reg = 0
                # Update outputs to match new stored direction
                self.walk_left_reg = self.stored_walk_left_reg
                self.walk_right_reg = self.stored_walk_right_reg
                self.aaah_reg = 0
                self.digging_reg = 0
                self.fall_counter_reg = 0
                return
            else:
                # Maintain stored direction
                self.walk_left_reg = self.stored_walk_left_reg
                self.walk_right_reg = self.stored_walk_right_reg
                self.aaah_reg = 0
                self.digging_reg = 0
                self.fall_counter_reg = 0
                return

        # GROUND RISING EDGE CASE: ground == 1 AND was falling (i.e., previous cycle was falling)
        # Check if we were falling last cycle: need to infer from state — aaah_reg was 1 last cycle?
        # But we don't store "last aaah", so instead: if current aaah_reg is 0 but last cycle we were falling,
        # how do we know? We must track "was_falling" across cycles. So we need to remember previous aaah.
        # However, our state update is sequential per cycle. Instead, use logic: if previous aaah was 1 and now ground==1,
        # then we just landed. But we don't have "previous aaah". So revise: the condition for splatter is:
        #   (fall_counter >= 20) AND (we are transitioning from falling to ground=1)
        # How do we know transition? We need to remember whether we were falling *before* this cycle.
        # Therefore, add state variable: was_falling_last_cycle
        # But we don't have it yet. So refactor: compute behavior based on current inputs and *current* state,
        # and detect landing by: (self.aaah_reg == 1 was true in prior call) -> but we can't access prior call's state.
        #
        # Solution: In GoldenDUT, we maintain 'was_falling' as part of state, updated at end of each load().
        # But we haven't defined it. Let's introduce it.
        #
        # Actually, simpler: the only way to get to ground=1 from falling is if last cycle aaah was 1.
        # So we need to remember aaah from last cycle. Add state: prev_aaah_reg
        #
        # Since we're building full golden model, let's add necessary state:
        #   self.prev_aaah_reg — but we don't have it initialized. So we must restructure.
        #
        # Alternative approach used in golden models: compute next state *before* updating registers.
        # But here, we are updating state *during* load() based on inputs.
        #
        # Let's instead track a flag: self.in_fall_prev_cycle, updated at end of each load().
        # Initialize it in __init__ as False.
        #
        # However, looking back at requirements: 3.1 says "inner states/values ... have suffix '_reg'", and initial value "x" but we set to digits.
        # And we are allowed to add any needed state.
        #
        # So add:
        #   self.in_fall_prev_cycle = False   # was falling in previous cycle?
        #
        # But wait — the provided signal vector does not include clock, and each load() is one cycle.
        # So at start of load(), self.in_fall_prev_cycle reflects whether last cycle was falling.
        #
        # We'll add that state now.

        # Since we didn't initialize it in __init__, we must do it. But we already wrote __init__.
        # So let's refactor __init__ to include it — but instructions say "only reply the python codes of the python class".
        # So we must include it in __init__ even if we didn't list it above.
        #
        # Actually, rereading 3.1: "Set the inner states/values of the golden DUT. These values have suffix '_reg'. The initial value of these inner values is 'x', but later will be digits."
        # And "You can set the initial values according to information or just '0's."
        #
        # So we'll add required state in __init__.
        #
        # But we cannot change __init__ now without rewriting entire class. So let's restart with complete state set.
        #
        # Required state registers (with _reg suffix):
        #   walk_left_reg, walk_right_reg, aaah_reg, digging_reg, splattered_reg, fall_counter_reg
        #   stored_walk_left_reg, stored_walk_right_reg
        #   in_fall_prev_cycle   -> but this is not a register in DUT, it's auxiliary for golden logic.
        #   However, to avoid confusion, let's use only DUT-like state and compute landing via logic:
        #
        # Insight: The condition for splatter is: ground==1 AND (fall_counter >= 20) AND (we were falling last cycle).
        # We know we were falling last cycle if: (aaah_reg was 1 before this load). But we overwrite aaah_reg during load.
        #
        # So we must save previous aaah. Let's rename:
        #   self.aaah_reg -> current output
        #   self.aaah_prev_reg -> aaah value *before* this cycle's update
        #
        # But that complicates. Standard golden modeling: maintain state *before* processing inputs, then compute next state.
        #
        # Let's adopt standard approach:
        #   State variables represent the state *at the beginning of the cycle* (i.e., after previous clock).
        #   Then load() computes next state based on inputs and current state.
        #   Then we update state at end of load().
        #
        # So we need:
        #   self.state_walk_left
        #   self.state_walk_right
        #   self.state_aaah
        #   self.state_digging
        #   self.state_splattered
        #   self.state_fall_counter
        #   self.state_stored_walk_left
        #   self.state_stored_walk_right
        #
        # And outputs are determined from current state and inputs.
        #
        # But the problem says "inner states/values ... have suffix '_reg'", so we'll use _reg.
        #
        # And we need to remember state from *start* of cycle to compute next state.
        #
        # So we'll store current state, then compute next state, then assign.
        #
        # However, the method signature is simple: load(signal_vector), no return.
        #
        # Given time, we'll implement robust golden model with full state preservation.
        #
        # Revised plan: maintain state variables that represent the FSM state *at the beginning of the current cycle*.
        # Then compute outputs and next state.
        #
        # But the problem doesn't specify whether state is pre- or post-update.
        # And the example signal vectors show consecutive cycles — so load() is called per cycle, and should advance state.
        #
        # Let's define state variables as the values *after* reset and *before* any cycles — i.e., initial state.
        # Then first load() computes state after first cycle.
        #
        # So we need to store state, then update it.
        #
        # We'll keep the state variables as the current state (at start of cycle), and update them at end of load().
        #
        # Therefore, we need to compute next state first, then assign.
        #
        # So inside load(), we compute next values, then assign to _reg variables.
        #
        # That means we need temporary variables.
        #
        # Let's do that.
        #
        # But note: the requirement says "the inner values of 'GoldenDUT' shall change according to the input signals" in load().
        #
        # So yes, compute next state, then assign.
        #
        # We'll do:
        #   next_walk_left = ...
        #   ... then assign self.walk_left_reg = next_walk_left
        #
        # So let's restructure the entire _update_state to be a computation that returns next state.
        #
        # However, the instruction says "write other methods you need", so we can write a helper.
        #
        # Given complexity, we'll write a helper _compute_next_state that takes current state and inputs and returns next state tuple.
        #
        # But to keep it self-contained and clear, we'll implement full logic in load() with temporaries.
        #
        # Actually, let's restart the class from scratch with correct state management.
        #
        # Since we must output only the class, and it must be correct, here is the final implementation:

    def load(self, signal_vector):
        # Extract inputs
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        # If reset is asserted, go to initial state
        if areset:
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.splattered_reg = 0
            self.fall_counter_reg = 0
            self.stored_walk_left_reg = 1
            self.stored_walk_right_reg = 0
            return

        # If already splattered, remain splattered
        if self.splattered_reg:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg = 0
            return

        # Determine current mode from current state
        is_walking = (self.stored_walk_left_reg == 1 or self.stored_walk_right_reg == 1) and self.aaah_reg == 0 and self.digging_reg == 0
        is_falling = (self.aaah_reg == 1) and (self.digging_reg == 0) and (not self.splattered_reg)
        is_digging = (self.digging_reg == 1) and (self.aaah_reg == 0) and (not self.splattered_reg)

        # Precedence Level 1: FALL (ground == 0)
        if ground == 0:
            # Update fall counter
            if is_falling:
                next_fall_counter = min(self.fall_counter_reg + 1, 31)
            else:
                next_fall_counter = 1

            # Outputs during fall
            next_walk_left = 0
            next_walk_right = 0
            next_aaah = 1
            next_digging = 0
            next_splattered = 0
            next_stored_walk_left = self.stored_walk_left_reg
            next_stored_walk_right = self.stored_walk_right_reg

            # Update state
            self.walk_left_reg = next_walk_left
            self.walk_right_reg = next_walk_right
            self.aaah_reg = next_aaah
            self.digging_reg = next_digging
            self.splattered_reg = next_splattered
            self.fall_counter_reg = next_fall_counter
            self.stored_walk_left_reg = next_stored_walk_left
            self.stored_walk_right_reg = next_stored_walk_right
            return

        # Precedence Level 2: GROUND == 1 → check DIG
        if is_digging:
            # Continuing dig
            next_walk_left = 0
            next_walk_right = 0
            next_aaah = 0
            next_digging = 1
            next_splattered = 0
            next_fall_counter = 0
            next_stored_walk_left = self.stored_walk_left_reg
            next_stored_walk_right = self.stored_walk_right_reg

            self.walk_left_reg = next_walk_left
            self.walk_right_reg = next_walk_right
            self.aaah_reg = next_aaah
            self.digging_reg = next_digging
            self.splattered_reg = next_splattered
            self.fall_counter_reg = next_fall_counter
            self.stored_walk_left_reg = next_stored_walk_left
            self.stored_walk_right_reg = next_stored_walk_right
            return

        # Start digging if eligible
        if (not is_falling) and (not self.splattered_reg) and (dig == 1):
            next_walk_left = 0
            next_walk_right = 0
            next_aaah = 0
            next_digging = 1
            next_splattered = 0
            next_fall_counter = 0
            next_stored_walk_left = self.stored_walk_left_reg
            next_stored_walk_right = self.stored_walk_right_reg

            self.walk_left_reg = next_walk_left
            self.walk_right_reg = next_walk_right
            self.aaah_reg = next_aaah
            self.digging_reg = next_digging
            self.splattered_reg = next_splattered
            self.fall_counter_reg = next_fall_counter
            self.stored_walk_left_reg = next_stored_walk_left
            self.stored_walk_right_reg = next_stored_walk_right
            return

        # Precedence Level 3: GROUND == 1, NOT DIGGING, NOT FALLING, NOT SPLATTERED → check BUMP
        if is_walking and (not self.splattered_reg) and (not is_falling) and (not is_digging):
            bump_effective = (bump_left == 1 or bump_right == 1)
            if bump_effective:
                # Flip stored direction
                if self.stored_walk_left_reg == 1:
                    next_stored_walk_left = 0
                    next_stored_walk_right = 1
                else:
                    next_stored_walk_left = 1
                    next_stored_walk_right = 0
                next_walk_left = next_stored_walk_left
                next_walk_right = next_stored_walk_right
                next_aaah = 0
                next_digging = 0
                next_splattered = 0
                next_fall_counter = 0
            else:
                next_stored_walk_left = self.stored_walk_left_reg
                next_stored_walk_right = self.stored_walk_right_reg
                next_walk_left = next_stored_walk_left
                next_walk_right = next_stored_walk_right
                next_aaah = 0
                next_digging = 0
                next_splattered = 0
                next_fall_counter = 0

            self.walk_left_reg = next_walk_left
            self.walk_right_reg = next_walk_right
            self.aaah_reg = next_aaah
            self.digging_reg = next_digging
            self.splattered_reg = next_splattered
            self.fall_counter_reg = next_fall_counter
            self.stored_walk_left_reg = next_stored_walk_left
            self.stored_walk_right_reg = next_stored_walk_right
            return

        # GROUND RISING EDGE: ground == 1 and we were falling last cycle
        # How do we know we were falling last cycle? We need to remember aaah from last cycle.
        # So add state: self.aaah_prev_cycle, initialized in __init__
        # But we didn't. So we must add it. Since we control __init__, we'll add it there.
        # However, the problem says "only reply the python codes", so we must output a working class.
        # Let's add necessary state in __init__ and track it.

        # Since we cannot modify __init__ now without rewriting, and we must output a single class,
        # we'll add the missing state in __init__ and track 'was_falling' as self.was_falling_reg.

        # But we haven't defined it. So let's assume we can add it — and do so.

        # Actually, let's look at the initial __init__: we'll add it there.

        # Given instructions, we must output the full class. So here is the complete, correct implementation:

    def check(self, signal_vector):
        # Expected outputs based on current state
        expected_walk_left = self.walk_left_reg
        expected_walk_right = self.walk_right_reg
        expected_aaah = self.aaah_reg
        expected_digging = self.digging_reg

        # Observed outputs from DUT
        observed_walk_left = signal_vector['walk_left']
        observed_walk_right = signal_vector['walk_right']
        observed_aaah = signal_vector['aaah']
        observed_digging = signal_vector['digging']

        # Compare
        if (expected_walk_left != observed_walk_left or
            expected_walk_right != observed_walk_right or
            expected_aaah != observed_aaah or
            expected_digging != observed_digging):
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_left={expected_walk_left}, walk_right={expected_walk_right}, aaah={expected_aaah}, digging={expected_digging}, observed: walk_left={observed_walk_left}, walk_right={observed_walk_right}, aaah={observed_aaah}, digging={observed_digging}")
            return False
        return True


# But wait — the above load() doesn't handle splatter on ground rise!
# We must add splatter detection.

# Let's rewrite the class completely with proper splatter logic, including tracking of previous aaah.

class GoldenDUT:
    def __init__(self):
        # State registers (values at beginning of cycle)
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.splattered_reg = 0
        self.fall_counter_reg = 0
        self.stored_walk_left_reg = 1
        self.stored_walk_right_reg = 0
        # Auxiliary for detecting ground rise after fall
        self.was_falling_reg = False  # was falling in previous cycle

    def load(self, signal_vector):
        # Extract inputs
        areset = signal_vector['areset']
        bump_left = signal_vector['bump_left']
        bump_right = signal_vector['bump_right']
        ground = signal_vector['ground']
        dig = signal_vector['dig']

        # Handle reset
        if areset:
            self.walk_left_reg = 1
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.splattered_reg = 0
            self.fall_counter_reg = 0
            self.stored_walk_left_reg = 1
            self.stored_walk_right_reg = 0
            self.was_falling_reg = False
            return

        # If splattered, lock all outputs to 0
        if self.splattered_reg:
            self.walk_left_reg = 0
            self.walk_right_reg = 0
            self.aaah_reg = 0
            self.digging_reg = 0
            self.fall_counter_reg = 0
            self.was_falling_reg = False
            return

        # Save current falling status for next cycle's was_falling_reg
        current_is_falling = (self.aaah_reg == 1) and (self.digging_reg == 0)

        # Precedence Level 1: FALL (ground == 0)
        if ground == 0:
            # Update fall counter
            if current_is_falling:
                next_fall_counter = min(self.fall_counter_reg + 1, 31)
            else:
                next_fall_counter = 1

            # Outputs during fall
            next_walk_left = 0
            next_walk_right = 0
            next_aaah = 1
            next_digging = 0
            next_splattered = 0
            next_stored_walk_left = self.stored_walk_left_reg
            next_stored_walk_right = self.stored_walk_right_reg

            # Update state
            self.walk_left_reg = next_walk_left
            self.walk_right_reg = next_walk_right
            self.aaah_reg = next_aaah
            self.digging_reg = next_digging
            self.splattered_reg = next_splattered
            self.fall_counter_reg = next_fall_counter
            self.stored_walk_left_reg = next_stored_walk_left
            self.stored_walk_right_reg = next_stored_walk_right
            self.was_falling_reg = True  # for next cycle
            return

        # Precedence Level 2: GROUND == 1 → check DIG
        is_digging = (self.digging_reg == 1) and (self.aaah_reg == 0) and (not self.splattered_reg)
        if is_digging:
            # Continuing dig
            next_walk_left = 0
            next_walk_right = 0
            next_aaah = 0
            next_digging = 1
            next_splattered = 0
            next_fall_counter = 0
            next_stored_walk_left = self.stored_walk_left_reg
            next_stored_walk_right = self.stored_walk_right_reg

            self.walk_left_reg = next_walk_left
            self.walk_right_reg = next_walk_right
            self.aaah_reg = next_aaah
            self.digging_reg = next_digging
            self.splattered_reg = next_splattered
            self.fall_counter_reg = next_fall_counter
            self.stored_walk_left_reg = next_stored_walk_left
            self.stored_walk_right_reg = next_stored_walk_right
            self.was_falling_reg = False
            return

        # Start digging if eligible
        if (not current_is_falling) and (not self.splattered_reg) and (dig == 1):
            next_walk_left = 0
            next_walk_right = 0
            next_aaah = 0
            next_digging = 1
            next_splattered = 0
            next_fall_counter = 0
            next_stored_walk_left = self.stored_walk_left_reg
            next_stored_walk_right = self.stored_walk_right_reg

            self.walk_left_reg = next_walk_left
            self.walk_right_reg = next_walk_right
            self.aaah_reg = next_aaah
            self.digging_reg = next_digging
            self.splattered_reg = next_splattered
            self.fall_counter_reg = next_fall_counter
            self.stored_walk_left_reg = next_stored_walk_left
            self.stored_walk_right_reg = next_stored_walk_right
            self.was_falling_reg = False
            return

        # Precedence Level 3: GROUND == 1, NOT DIGGING, NOT FALLING, NOT SPLATTERED → check BUMP
        is_walking = (self.stored_walk_left_reg == 1 or self.stored_walk_right_reg == 1) and self.aaah_reg == 0 and self.digging_reg == 0
        if is_walking and (not self.splattered_reg) and (not current_is_falling) and (not is_digging):
            bump_effective = (bump_left == 1 or bump_right == 1)
            if bump_effective:
                # Flip stored direction
                if self.stored_walk_left_reg == 1:
                    next_stored_walk_left = 0
                    next_stored_walk_right = 1
                else:
                    next_stored_walk_left = 1
                    next_stored_walk_right = 0
                next_walk_left = next_stored_walk_left
                next_walk_right = next_stored_walk_right
                next_aaah = 0
                next_digging = 0
                next_splattered = 0
                next_fall_counter = 0
            else:
                next_stored_walk_left = self.stored_walk_left_reg
                next_stored_walk_right = self.stored_walk_right_reg
                next_walk_left = next_stored_walk_left
                next_walk_right = next_stored_walk_right
                next_aaah = 0
                next_digging = 0
                next_splattered = 0
                next_fall_counter = 0

            self.walk_left_reg = next_walk_left
            self.walk_right_reg = next_walk_right
            self.aaah_reg = next_aaah
            self.digging_reg = next_digging
            self.splattered_reg = next_splattered
            self.fall_counter_reg = next_fall_counter
            self.stored_walk_left_reg = next_stored_walk_left
            self.stored_walk_right_reg = next_stored_walk_right
            self.was_falling_reg = False
            return

        # GROUND RISING EDGE: ground == 1 and was_falling_reg is True (i.e., was falling last cycle)
        if self.was_falling_reg and ground == 1:
            # Check splatter: fell for >= 20 cycles means fall_counter >= 20
            if self.fall_counter_reg >= 20:
                # Splatter: all outputs 0, splattered forever
                next_walk_left = 0
                next_walk_right = 0
                next_aaah = 0
                next_digging = 0
                next_splattered = 1
                next_fall_counter = 0
                next_stored_walk_left = self.stored_walk_left_reg
                next_stored_walk_right = self.stored_walk_right_reg
            else:
                # Resume walking in stored direction
                next_walk_left = self.stored_walk_left_reg
                next_walk_right = self.stored_walk_right_reg
                next_aaah = 0
                next_digging = 0
                next_splattered = 0
                next_fall_counter = 0
                next_stored_walk_left = self.stored_walk_left_reg
                next_stored_walk_right = self.stored_walk_right_reg

            self.walk_left_reg = next_walk_left
            self.walk_right_reg = next_walk_right
            self.aaah_reg = next_aaah
            self.digging_reg = next_digging
            self.splattered_reg = next_splattered
            self.fall_counter_reg = next_fall_counter
            self.stored_walk_left_reg = next_stored_walk_left
            self.stored_walk_right_reg = next_stored_walk_right
            self.was_falling_reg = False
            return

        # Default: ground == 1, not walking, not falling, not digging, not splattered -> should be walking left
        # This can happen after splatter recovery (but splattered is absorbing) or initial state.
        # Per spec, reset sets walk_left=1, so default to walk left.
        self.walk_left_reg = 1
        self.walk_right_reg = 0
        self.aaah_reg = 0
        self.digging_reg = 0
        self.splattered_reg = 0
        self.fall_counter_reg = 0
        self.stored_walk_left_reg = 1
        self.stored_walk_right_reg = 0
        self.was_falling_reg = False

    def check(self, signal_vector):
        expected_walk_left = self.walk_left_reg
        expected_walk_right = self.walk_right_reg
        expected_aaah = self.aaah_reg
        expected_digging = self.digging_reg

        observed_walk_left = signal_vector['walk_left']
        observed_walk_right = signal_vector['walk_right']
        observed_aaah = signal_vector['aaah']
        observed_digging = signal_vector['digging']

        if (expected_walk_left != observed_walk_left or
            expected_walk_right != observed_walk_right or
            expected_aaah != observed_aaah or
            expected_digging != observed_digging):
            print(f"Scenario: {signal_vector['scenario']}, expected: walk_left={expected_walk_left}, walk_right={expected_walk_right}, aaah={expected_aaah}, digging={expected_digging}, observed: walk_left={observed_walk_left}, walk_right={observed_walk_right}, aaah={observed_aaah}, digging={observed_digging}")
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
