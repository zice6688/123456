`timescale 1ns / 1ps
module testbench;
reg  clk;
reg [7:0] in;
reg  reset;
wire  done;

integer file, scenario;
// DUT instantiation
top_module DUT (
	.clk(clk),
	.in(in),
	.reset(reset),
	.done(done)
);
// Clock generation
initial begin
    clk = 0;
    forever #5 clk = ~clk;
end

initial begin
    file = $fopen("TBout.txt", "w");
end
// Scenario Based Test
initial begin

    // Scenario 1
    scenario = 1;
    reset = 1; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; reset = 0; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 2
    scenario = 2;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 3
    scenario = 3;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 4
    scenario = 4;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 5
    scenario = 5;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 6
    scenario = 6;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 7
    scenario = 7;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 8
    scenario = 8;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 9
    scenario = 9;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 10
    scenario = 10;
    reset = 1; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; reset = 0; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    // ========== CGA Iteration 1 ==========
    scenario = 100 + 1;
    // Reset signals to safe state
    in = 0; reset = 0;
    #5;
    // CGA generated test sequence:
    initial begin
    // Initialize signals
    reset = 1;
    clk = 0;
    input_signal = 0;
    #10;
    reset = 0;
    // Test different FSM state transitions
    // Start with a known initial state
    @(posedge clk);
    // [WARNING] Contains internal signal reference: ['state']
    // Original: input_signal = 1;  // Transition to state A
    repeat(5) @(posedge clk);
    // [WARNING] Contains internal signal reference: ['state']
    // Original: input_signal = 0;  // Transition to state B
    repeat(5) @(posedge clk);
    // [WARNING] Contains internal signal reference: ['state']
    // Original: input_signal = 1;  // Transition to state C
    repeat(5) @(posedge clk);
    // [WARNING] Contains internal signal reference: ['state']
    // Original: input_signal = 0;  // Transition back to state B
    repeat(5) @(posedge clk);
    // [WARNING] Contains internal signal reference: ['state']
    // Original: input_signal = 1;  // Transition to state D
    repeat(5) @(posedge clk);
    // Test edge cases and boundary conditions
    // [WARNING] Contains internal signal reference: ['state']
    // Original: input_signal = 2;  // Invalid input, should stay in current state
    repeat(5) @(posedge clk);
    input_signal = 0;  // Valid transition
    repeat(5) @(posedge clk);
    // Vary timing and sequence of inputs
    // [WARNING] Contains internal signal reference: ['state']
    // Original: input_signal = 1;  // Transition to state A
    repeat(3) @(posedge clk);
    // [WARNING] Contains internal signal reference: ['state']
    // Original: input_signal = 0;  // Transition to state B
    repeat(3) @(posedge clk);
    // [WARNING] Contains internal signal reference: ['state']
    // Original: input_signal = 1;  // Transition to state C
    repeat(3) @(posedge clk);
    // [WARNING] Contains internal signal reference: ['state']
    // Original: input_signal = 0;  // Transition back to state B
    repeat(3) @(posedge clk);
    // [WARNING] Contains internal signal reference: ['state']
    // Original: input_signal = 1;  // Transition to state D
    repeat(3) @(posedge clk);
    // Test with rapid changes
    for (int i = 0; i < 10; i++) begin
    input_signal = i % 2;  // Alternate between 0 and 1
    @(posedge clk);
    end
    // Test with long periods of no change
    input_signal = 0;
    repeat(20) @(posedge clk);
    input_signal = 1;
    repeat(20) @(posedge clk);
    // Final reset
    reset = 1;
    repeat(5) @(posedge clk);
    reset = 0;
    end
    // Log results
    $fdisplay(file, "[CGA-1] done = %b", done);
    // ==============================================


    $fclose(file);
    $finish;
end

endmodule
