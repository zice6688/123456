`timescale 1ns / 1ps
module testbench;
reg  clk;
reg  in;
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

    // Scenario 1: Initial reset
    scenario = 1;
    reset = 1;
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    reset = 0;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    in = 0; // Start bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // Stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;

    // Scenario 2: Valid byte sequence
    scenario = 2;
    in = 0; // Start bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // Stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;

    // Scenario 3: Multiple valid bytes
    scenario = 3;
    in = 0; // First start bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // First data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // First stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 0; // Second start bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Second data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // Second stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;

    // Scenario 4: Incorrect stop bit
    scenario = 4;
    in = 0; // Start bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 0; // Incorrect stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Correct stop bit after 5 more clock cycles
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;

    // Scenario 5: No start bit
    scenario = 5;
    in = 1; // Data bits without start bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // Stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 0; // Start bit for next valid byte
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // Stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;

    // Scenario 6: Consecutive start bits
    scenario = 6;
    in = 0; // First start bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 0; // Second start bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // Stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;

    // Scenario 7: Long idle period
    scenario = 7;
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(20) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 0; // Start bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // Stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;

    // Scenario 8: Reset during byte reception
    scenario = 8;
    in = 0; // Start bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(7) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // 8th data bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    reset = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    reset = 0;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    in = 0; // Start bit after reset
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // Stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;

    // Scenario 9: Interrupted byte sequence
    scenario = 9;
    in = 0; // Start bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 0; // Incorrect stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Correct stop bit after 5 more clock cycles
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 0; // Start bit for next valid byte
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // Stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;

    // Scenario 10: Edge cases
    scenario = 10;
    in = 0; // Start bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 0; // Start bit for next valid byte
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Data bits
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(8) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // Stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1; // Idle state
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;

    $fclose(file);
    $finish;
end

endmodule
