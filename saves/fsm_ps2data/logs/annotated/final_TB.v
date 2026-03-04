//      // verilator_coverage annotation
        `timescale 1ns / 1ps
        module testbench;
 000069 reg  clk;
~000013 reg [7:0] in;
%000003 reg  reset;
~000018 wire [23:0] out_bytes;
 000018 wire  done;
        
        integer file, scenario;
        // DUT instantiation
        top_module DUT (
        	.clk(clk),
        	.in(in),
        	.reset(reset),
        	.out_bytes(out_bytes),
        	.done(done)
        );
        // Clock generation
%000000 initial begin
%000000     clk = 0;
~000138     forever #5 clk = ~clk;
        end
        
%000001 initial begin
%000001     file = $fopen("TBout.txt", "w");
        end
        // Scenario Based Test
%000001 initial begin
        
            // Scenario 1
%000001     scenario = 1;
%000001     reset = 1; in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     reset = 0; in = 8'h00; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h2C; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h81; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h09; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
        
            // Scenario 2
%000001     scenario = 2;
%000001     in = 8'h6B; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h0D; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h8D; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
        
            // Scenario 3
%000001     scenario = 3;
%000001     in = 8'h6D; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h12; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h01; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'hED; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h76; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h3D; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
        
            // Scenario 4
%000001     scenario = 4;
%000001     in = 8'hED; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h8C; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'hF9; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h00; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h00; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'hCE; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'hC5; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'hAA; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
        
            // Scenario 5
%000001     scenario = 5;
%000001     in = 8'h2C; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h81; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h09; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     reset = 1; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     reset = 0; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h6B; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h0D; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h8D; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
        
            // Scenario 6
%000001     scenario = 6;
%000001     in = 8'h6B; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h0D; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h8D; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h00; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h00; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'hED; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h76; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h3D; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
        
            // Scenario 7
%000001     scenario = 7;
%000001     in = 8'hED; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h8C; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'hF9; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h00; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h00; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'hCE; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'hC5; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'hAA; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
        
            // Scenario 8
%000001     scenario = 8;
%000001     in = 8'h2C; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h81; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h09; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     reset = 1; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     reset = 0; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h6B; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h0D; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
%000001     in = 8'h8D; #10;
%000001     $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
        
%000001     $fclose(file);
%000001     $finish;
        end
        
        endmodule
        
