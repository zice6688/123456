//      // verilator_coverage annotation
        `timescale 1ns / 1ps
        module testbench;
 000053 reg  clk;
~000012 reg [7:0] in;
%000002 reg  reset;
%000000 wire  done;
        
        integer file, scenario;
        // DUT instantiation
        top_module DUT (
        	.clk(clk),
        	.in(in),
        	.reset(reset),
        	.done(done)
        );
        // Clock generation
%000000 initial begin
%000000     clk = 0;
~000106     forever #5 clk = ~clk;
        end
        
%000001 initial begin
%000001     file = $fopen("TBout.txt", "w");
        end
        // Scenario Based Test
%000001 initial begin
        
            // Scenario 1
%000001     scenario = 1;
%000001     reset = 1; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; reset = 0; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
        
            // Scenario 2
%000001     scenario = 2;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
        
            // Scenario 3
%000001     scenario = 3;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
        
            // Scenario 4
%000001     scenario = 4;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
        
            // Scenario 5
%000001     scenario = 5;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
        
            // Scenario 6
%000001     scenario = 6;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
        
            // Scenario 7
%000001     scenario = 7;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
        
            // Scenario 8
%000001     scenario = 8;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
        
            // Scenario 9
%000001     scenario = 9;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
        
            // Scenario 10
%000001     scenario = 10;
%000001     reset = 1; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; reset = 0; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0010_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     in = 8'b0000_0000; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        
%000001     $fclose(file);
%000001     $finish;
        end
        
        endmodule
        
