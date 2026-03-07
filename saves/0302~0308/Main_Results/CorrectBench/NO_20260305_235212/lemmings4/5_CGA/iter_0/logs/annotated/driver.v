//      // verilator_coverage annotation
        `timescale 1ns / 1ps
        module testbench;
 000115 reg  clk;
%000001 reg  areset;
%000003 reg  bump_left;
%000002 reg  bump_right;
%000004 reg  ground;
%000001 reg  dig;
%000002 wire  walk_left;
%000003 wire  walk_right;
%000002 wire  aaah;
%000001 wire  digging;
        
        integer file, scenario;
        // DUT instantiation
        top_module DUT (
        	.clk(clk),
        	.areset(areset),
        	.bump_left(bump_left),
        	.bump_right(bump_right),
        	.ground(ground),
        	.dig(dig),
        	.walk_left(walk_left),
        	.walk_right(walk_right),
        	.aaah(aaah),
        	.digging(digging)
        );
        // Clock generation
%000000 initial begin
%000000     clk = 0;
~000230     forever #5 clk = ~clk;
        end
        
%000001 initial begin
%000001     file = $fopen("TBout.txt", "w");
        end
        // Scenario Based Test
%000001 initial begin
            // Scenario 1: Initial state
%000001     scenario = 1;
%000001     areset = 1; bump_left = 0; bump_right = 0; ground = 1; dig = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     areset = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
        
            // Scenario 2: Bump from the left
%000001     scenario = 2;
%000001     bump_left = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
        
            // Scenario 3: Bump from the right
%000001     scenario = 3;
%000001     bump_right = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_right = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
        
            // Scenario 4: Bump from both sides
%000001     scenario = 4;
%000001     bump_left = 1; bump_right = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 0; bump_right = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
        
            // Scenario 5: Falling
%000001     scenario = 5;
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
%000001     ground = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
        
            // Scenario 6: Digging
%000001     scenario = 6;
%000001     dig = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
        
            // Scenario 7: Falling and splattering
%000001     scenario = 7;
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
~000021     repeat(21) begin
 000021         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000021         #10;
            end
%000001     ground = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // Scenario 8: Falling and resuming after 19 clock cycles
%000001     scenario = 8;
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
~000019     repeat(19) begin
 000019         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000019         #10;
            end
%000001     ground = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // Scenario 9: Falling and bumping
%000001     scenario = 9;
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
%000001     bump_left = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // Scenario 10: Falling and digging
%000001     scenario = 10;
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
%000001     dig = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     dig = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
        
%000001     $fclose(file);
%000001     $finish;
        end
        
        endmodule
        
