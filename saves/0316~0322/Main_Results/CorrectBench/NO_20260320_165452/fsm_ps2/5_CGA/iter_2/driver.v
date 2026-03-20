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
    reset = 1; in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    reset = 0; in = 8'b0010_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 2
    scenario = 2;
    reset = 0; in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0010_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 3
    scenario = 3;
    reset = 0; in = 8'b0010_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0010_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 4
    scenario = 4;
    reset = 0; in = 8'b0010_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    reset = 1; in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    reset = 0; in = 8'b0010_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 5
    scenario = 5;
    reset = 0; in = 8'b0010_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0010_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 6
    scenario = 6;
    reset = 0; in = 8'b0010_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    repeat(5) begin
        in = 8'b0000_0000; 
        $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 8'b0010_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 

    // Scenario 7
    scenario = 7;
    reset = 0; in = 8'b0010_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    repeat(5) begin
        in = 8'b0000_0000; 
        $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    reset = 1; in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    reset = 0; in = 8'b0010_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 8'b0000_0000; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    // ========== CGA Iteration 2 ==========
    scenario = 100 + 2;
    // Reset signals to safe state
    in = 0; reset = 0;
    #5;
    // CGA generated test sequence:
    // Exploratory test scenario to cover different FSM state transitions and edge cases
    // Initialize signals
    reset = 1;
    input_signal = 0;
    control_signal = 0;
    #10;
    reset = 0;
    #10;
    // Test case 1: Transition from IDLE to STATE1
    input_signal = 1;
    control_signal = 0;
    #10;
    input_signal = 0;
    #10;
    // Test case 2: Transition from STATE1 to STATE2
    input_signal = 1;
    control_signal = 1;
    #10;
    input_signal = 0;
    #10;
    // Test case 3: Transition from STATE2 back to IDLE
    input_signal = 1;
    control_signal = 0;
    #10;
    input_signal = 0;
    #10;
    // Test case 4: Edge case - rapid transitions
    input_signal = 1;
    control_signal = 0;
    #5;
    input_signal = 0;
    #5;
    input_signal = 1;
    control_signal = 1;
    #5;
    input_signal = 0;
    #5;
    input_signal = 1;
    control_signal = 0;
    #5;
    input_signal = 0;
    #5;
    // Test case 5: Boundary condition - long duration in one state
    input_signal = 1;
    control_signal = 0;
    #100;
    input_signal = 0;
    #10;
    // Test case 6: Transition with varying timing
    input_signal = 1;
    control_signal = 0;
    #20;
    input_signal = 0;
    #5;
    input_signal = 1;
    control_signal = 1;
    #10;
    input_signal = 0;
    #10;
    // Test case 7: Edge case - simultaneous transitions
    input_signal = 1;
    control_signal = 1;
    #10;
    input_signal = 0;
    control_signal = 0;
    #10;
    // Test case 8: Transition with different sequences
    input_signal = 1;
    control_signal = 0;
    #10;
    input_signal = 0;
    control_signal = 1;
    #10;
    input_signal = 1;
    control_signal = 0;
    #10;
    input_signal = 0;
    control_signal = 0;
    #10;
    // End of test
    end
    // Log results
    $fdisplay(file, "[CGA-2] done = %b", done);
    // ==============================================


    $fclose(file);
    $finish;
end

endmodule
