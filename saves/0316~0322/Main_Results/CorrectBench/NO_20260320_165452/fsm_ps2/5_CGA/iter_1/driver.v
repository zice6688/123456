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
    // ========== CGA Iteration 1 ==========
    scenario = 100 + 1;
    // Reset signals to safe state
    in = 0; reset = 0;
    #5;
    // CGA generated test sequence:
    // Exploratory test scenario for FSM_state
    // Initialize signals
    reset = 1;
    clk = 0;
    input_signal = 0;
    #10 reset = 0;
    // Test different input combinations and state transitions
    // Start with a known state
    @(posedge clk) input_signal = 1;  // Transition to state 1
    @(posedge clk) input_signal = 0;  // Transition to state 2
    @(posedge clk) input_signal = 1;  // Transition to state 3
    @(posedge clk) input_signal = 0;  // Transition to state 4
    @(posedge clk) input_signal = 1;  // Transition to state 5
    // Test edge cases and boundary conditions
    @(posedge clk) input_signal = 1;  // Stay in state 5
    @(posedge clk) input_signal = 0;  // Stay in state 5
    @(posedge clk) input_signal = 1;  // Stay in state 5
    @(posedge clk) input_signal = 0;  // Stay in state 5
    // Vary timing and sequence of inputs
    @(posedge clk) input_signal = 1;  // Transition to state 1
    @(posedge clk) input_signal = 1;  // Stay in state 1
    @(posedge clk) input_signal = 0;  // Transition to state 2
    @(posedge clk) input_signal = 0;  // Stay in state 2
    @(posedge clk) input_signal = 1;  // Transition to state 3
    @(posedge clk) input_signal = 1;  // Stay in state 3
    @(posedge clk) input_signal = 0;  // Transition to state 4
    @(posedge clk) input_signal = 0;  // Stay in state 4
    @(posedge clk) input_signal = 1;  // Transition to state 5
    @(posedge clk) input_signal = 1;  // Stay in state 5
    // Test rapid transitions
    repeat (10) begin
    @(posedge clk) input_signal = 1;  // Rapidly toggle between states
    @(posedge clk) input_signal = 0;
    // Test long sequences
    repeat (100) begin
    @(posedge clk) input_signal = $random % 2;  // Randomly toggle input
    end
    // Finalize the test
    @(posedge clk) input_signal = 0;  // Ensure a final state is reached
    end
    // Clock generation
    always
    begin
    #5 clk = ~clk;
    end
    // Log results
    $fdisplay(file, "[CGA-1] done = %b", done);
    // ==============================================


    $fclose(file);
    $finish;
end

endmodule
