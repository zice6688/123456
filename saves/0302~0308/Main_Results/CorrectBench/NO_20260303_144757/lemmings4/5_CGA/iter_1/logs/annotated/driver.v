//      // verilator_coverage annotation
        module testbench;
 000155 reg  clk;
%000003 reg  areset;
%000006 reg  bump_left;
%000006 reg  bump_right;
%000008 reg  ground;
%000002 reg  dig;
%000008 wire  walk_left;
%000001 wire  walk_right;
%000007 wire  aaah;
%000005 wire  digging;
        
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
~000309     forever #5 clk = ~clk;
        end
        
%000001 initial begin
%000001     file = $fopen("TBout.txt", "w");
        end
        // Scenario Based Test
%000001 initial begin
        
            // scenario 1
%000001     scenario = 1;
%000001     areset = 1; bump_left = 0; bump_right = 0; ground = 1; dig = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     areset = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 2
%000001     scenario = 2;
%000001     bump_left = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 3
%000001     scenario = 3;
%000001     bump_right = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_right = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 4
%000001     scenario = 4;
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
%000001     ground = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 5
%000001     scenario = 5;
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
%000001     ground = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 6
%000001     scenario = 6;
%000001     dig = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
~000010     repeat(10) begin
 000010         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000010         #10;
            end
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
%000001     ground = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 7
%000001     scenario = 7;
%000001     dig = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
~000010     repeat(10) begin
 000010         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000010         #10;
            end
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
%000001     ground = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 8
%000001     scenario = 8;
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
~000025     repeat(25) begin
 000025         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000025         #10;
            end
%000001     ground = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 9
%000001     scenario = 9;
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
~000025     repeat(25) begin
 000025         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000025         #10;
            end
%000001     ground = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 10
%000001     scenario = 10;
%000001     areset = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     areset = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 11
%000001     scenario = 11;
%000001     bump_left = 1; bump_right = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 0; bump_right = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 12
%000001     scenario = 12;
%000001     bump_left = 1; bump_right = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 0; bump_right = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 13
%000001     scenario = 13;
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 1; bump_right = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 0; bump_right = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 14
%000001     scenario = 14;
%000001     dig = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 1; bump_right = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 0; bump_right = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
        
            // scenario 15
%000001     scenario = 15;
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 1; bump_right = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 0; bump_right = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
%000001     ground = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
        
%000001     $fclose(file);
            
%000001     test_coverage_fix_1();
%000001     $finish;
        end
        
        // CGA 1
%000001 task test_coverage_fix_1;
            // Reset the DUT
%000001     areset = 1;
%000002     repeat(2) @(posedge clk);
%000001     areset = 0;
%000001     @(posedge clk);
        
            // Set the initial conditions to reach the WR state
%000001     bump_left = 0;
%000001     dig = 0;
%000001     ground = 0;
%000005     repeat(5) @(posedge clk);  // Wait for enough cycles to ensure the FSM reaches the WR state
        
            // Trigger the missing logic: next = DIGR when in WR state and dig is high
%000001     dig = 1;
%000002     repeat(2) @(posedge clk);  // Wait for the FSM to transition to DIGR
        
            // Reset the inputs to avoid unintended behavior
%000001     dig = 0;
        endtask
        
        
        endmodule
        
