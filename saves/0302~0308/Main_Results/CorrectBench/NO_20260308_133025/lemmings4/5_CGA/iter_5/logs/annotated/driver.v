//      // verilator_coverage annotation
        `timescale 1ns / 1ps
        module testbench;
 000340 reg  clk;
%000005 reg  areset;
%000004 reg  bump_left;
%000005 reg  bump_right;
 000011 reg  ground;
%000005 reg  dig;
 000012 wire  walk_left;
%000002 wire  walk_right;
 000010 wire  aaah;
%000003 wire  digging;
        
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
~000679     forever #5 clk = ~clk;
        end
        
%000001 initial begin
%000001     file = $fopen("TBout.txt", "w");
        end
        // Scenario Based Test
%000001 initial begin
            // Scenario 1
%000001     scenario = 1;
%000001     areset = 1; bump_left = 0; bump_right = 0; ground = 0; dig = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     areset = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
~000010     repeat(10) begin
 000010         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000010         #10;
            end
        
            // Scenario 2
%000001     scenario = 2;
%000001     bump_left = 1; bump_right = 0; ground = 0; dig = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_left = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
        
            // Scenario 3
%000001     scenario = 3;
%000001     bump_left = 0; bump_right = 1; ground = 0; dig = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000001     #10;
%000001     bump_right = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
        
            // Scenario 4
%000001     scenario = 4;
%000001     bump_left = 0; bump_right = 0; ground = 0; dig = 0;
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
        
            // Scenario 5
%000001     scenario = 5;
%000001     bump_left = 0; bump_right = 0; ground = 0; dig = 0;
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
        
            // Scenario 6
%000001     scenario = 6;
%000001     bump_left = 0; bump_right = 0; ground = 0; dig = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
~000025     repeat(25) begin
 000025         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000025         #10;
            end
%000001     ground = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
        
            // Scenario 7
%000001     scenario = 7;
%000001     bump_left = 0; bump_right = 0; ground = 0; dig = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
~000025     repeat(25) begin
 000025         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000025         #10;
            end
%000001     ground = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
        
            // Scenario 8
%000001     scenario = 8;
%000001     bump_left = 0; bump_right = 0; ground = 1; dig = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
~000010     repeat(10) begin
 000010         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000010         #10;
            end
        
            // Scenario 9
%000001     scenario = 9;
%000001     bump_left = 0; bump_right = 0; ground = 1; dig = 1;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
%000005     repeat(5) begin
%000005         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
%000005         #10;
            end
%000001     ground = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
~000010     repeat(10) begin
 000010         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000010         #10;
            end
        
            // Scenario 10
%000001     scenario = 10;
%000001     bump_left = 1; bump_right = 0; ground = 0; dig = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
~000010     repeat(10) begin
 000010         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000010         #10;
            end
        
            // Scenario 11
%000001     scenario = 11;
%000001     bump_left = 0; bump_right = 1; ground = 0; dig = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
~000010     repeat(10) begin
 000010         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000010         #10;
            end
        
            // Scenario 12
%000001     scenario = 12;
%000001     bump_left = 1; bump_right = 1; ground = 0; dig = 0;
%000001     $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
~000010     repeat(10) begin
 000010         $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
 000010         #10;
            end
            // ========== CGA Iteration 1 ==========
%000001     scenario = 100 + 1;
            // Reset signals to safe state
%000001     areset = 0; bump_left = 0; bump_right = 0; ground = 0; dig = 0;
%000001     #5;
            // CGA generated test sequence:
            // Reset sequence - use ACTUAL input signal names from above
%000001     areset = 1;
%000002     repeat(2) @(posedge clk);
%000001     areset = 0;
            // Wait for FSM to reach the WL state (estimate cycles)
~000010     repeat(10) @(posedge clk);
            // Ensure ground is 1 and dig is 1 to trigger the missing branch
%000001     ground = 1;
%000001     dig = 1;
            // [WARNING] Contains internal signal reference: ['next']
            // Original: bump_left = 0;  // Ensure bump_left is 0 to avoid triggering the next condition
%000002     repeat(2) @(posedge clk);  // Wait for the FSM to transition to DIGL
            // Wait for FSM to reach the WR state (estimate cycles)
~000010     repeat(10) @(posedge clk);
            // Ensure ground is 1 and dig is 1 to trigger the missing branch
%000001     ground = 1;
%000001     dig = 1;
            // [WARNING] Contains internal signal reference: ['next']
            // Original: bump_right = 0;  // Ensure bump_right is 0 to avoid triggering the next condition
%000002     repeat(2) @(posedge clk);  // Wait for the FSM to transition to DIGR
            // Additional wait to ensure the FSM has settled
%000005     repeat(5) @(posedge clk);
            // Log results
%000001     $fdisplay(file, "[CGA-1] walk_left, walk_right, aaah, digging = %b, %b, %b, %b", walk_left, walk_right, aaah, digging);
            // ==============================================
            // ========== CGA Iteration 2 ==========
%000001     scenario = 100 + 2;
            // Reset signals to safe state
%000001     areset = 0; bump_left = 0; bump_right = 0; ground = 0; dig = 0;
%000001     #5;
            // CGA generated test sequence:
            // Reset sequence - use ACTUAL input signal names from above
%000001     areset = 1;
%000002     repeat(2) @(posedge clk);
%000001     areset = 0;
            // Wait for FSM to reach the WL state (estimate cycles)
~000010     repeat(10) @(posedge clk);
            // Ensure ground is high and dig is low to reach the missing branch
%000001     ground = 1;
%000001     dig = 0;
            // Ensure bump_left is high to trigger the missing branch
%000001     bump_left = 1;
%000001     repeat(1) @(posedge clk);  // Wait for the FSM to transition to WR
            // Now, ensure ground is high and dig is low to stay in WR
%000001     ground = 1;
%000001     dig = 0;
            // Ensure bump_right is high to transition back to WL
%000001     bump_right = 1;
%000001     repeat(1) @(posedge clk);  // Wait for the FSM to transition to WL
            // Ensure ground is high and dig is low to stay in WL
%000001     ground = 1;
%000001     dig = 0;
            // Ensure bump_left is high to transition back to WR
%000001     bump_left = 1;
%000001     repeat(1) @(posedge clk);  // Wait for the FSM to transition to WR
            // Now, ensure ground is low to transition to FALLR
%000001     ground = 0;
%000001     repeat(1) @(posedge clk);  // Wait for the FSM to transition to FALLR
            // Ensure ground is high and fall_counter is less than 20 to stay in FALLR
%000001     ground = 1;
            // [INTERNAL_ASSIGN] Cannot modify internal signal
            // Original: fall_counter = 19;  // Assuming fall_counter is an allowed input
%000001     repeat(1) @(posedge clk);  // Wait for the FSM to stay in FALLR
            // Ensure ground is high and fall_counter is 20 or more to transition to DEAD
            // [INTERNAL_ASSIGN] Cannot modify internal signal
            // Original: fall_counter = 20;  // Assuming fall_counter is an allowed input
%000001     repeat(1) @(posedge clk);  // Wait for the FSM to transition to DEAD
            // Ensure ground is high and dig is high to transition to DIGR
%000001     ground = 1;
%000001     dig = 1;
%000001     repeat(1) @(posedge clk);  // Wait for the FSM to transition to DIGR
            // Ensure ground is high and dig is low to transition to FALLR
%000001     dig = 0;
%000001     repeat(1) @(posedge clk);  // Wait for the FSM to transition to FALLR
            // Ensure ground is high and bump_right is high to transition back to WL
%000001     bump_right = 1;
%000001     repeat(1) @(posedge clk);  // Wait for the FSM to transition to WL
            // Ensure ground is high and dig is high to transition to DIGL
%000001     dig = 1;
%000001     repeat(1) @(posedge clk);  // Wait for the FSM to transition to DIGL
            // Ensure ground is high and dig is low to transition to FALLL
%000001     dig = 0;
%000001     repeat(1) @(posedge clk);  // Wait for the FSM to transition to FALLL
            // Ensure ground is high and fall_counter is 20 or more to transition to DEAD
            // [INTERNAL_ASSIGN] Cannot modify internal signal
            // Original: fall_counter = 20;  // Assuming fall_counter is an allowed input
%000001     repeat(1) @(posedge clk);  // Wait for the FSM to transition to DEAD
            // Log results
%000001     $fdisplay(file, "[CGA-2] walk_left, walk_right, aaah, digging = %b, %b, %b, %b", walk_left, walk_right, aaah, digging);
            // ==============================================
            // ========== CGA Iteration 3 ==========
%000001     scenario = 100 + 3;
            // Reset signals to safe state
%000001     areset = 0; bump_left = 0; bump_right = 0; ground = 0; dig = 0;
%000001     #5;
            // CGA generated test sequence:
            // Reset sequence - use ACTUAL input signal names from above
%000001     areset = 1;
%000002     repeat(2) @(posedge clk);
%000001     areset = 0;
            // Wait for FSM to reach the WL state (estimate cycles)
~000010     repeat(10) @(posedge clk);
            // Trigger the missing branch in WL state
%000001     ground = 1;  // Ensure ground is true
%000001     dig = 0;     // Ensure dig is false
%000001     bump_left = 0;  // Ensure bump_left is false
%000001     #10;  // Wait for a short time to ensure the conditions are stable
            // Drive inputs to trigger the missing branch
%000001     ground = 0;  // Make ground false
%000001     dig = 0;     // Ensure dig is still false
%000001     bump_left = 0;  // Ensure bump_left is still false
%000001     #10;  // Wait for a short time to ensure the conditions are stable
            // Wait for FSM to reach the WR state (estimate cycles)
~000010     repeat(10) @(posedge clk);
            // Trigger the missing branch in WR state
%000001     ground = 1;  // Ensure ground is true
%000001     dig = 0;     // Ensure dig is false
%000001     bump_right = 0;  // Ensure bump_right is false
%000001     #10;  // Wait for a short time to ensure the conditions are stable
            // Drive inputs to trigger the missing branch
%000001     ground = 0;  // Make ground false
%000001     dig = 0;     // Ensure dig is still false
%000001     bump_right = 0;  // Ensure bump_right is still false
%000001     #10;  // Wait for a short time to ensure the conditions are stable
            // Log results
%000001     $fdisplay(file, "[CGA-3] walk_left, walk_right, aaah, digging = %b, %b, %b, %b", walk_left, walk_right, aaah, digging);
            // ==============================================
            // ========== CGA Iteration 5 ==========
%000001     scenario = 100 + 5;
            // Reset signals to safe state
%000001     areset = 0; bump_left = 0; bump_right = 0; ground = 0; dig = 0;
%000001     #5;
            // CGA generated test sequence:
            // Reset sequence - use ACTUAL input signal names from above
%000001     areset = 1;
%000002     repeat(2) @(posedge clk);
%000001     areset = 0;
            // Wait for FSM to reach the initial state (estimate cycles)
%000003     repeat(3) @(posedge clk);
            // To cover the missing block "else next = WR;", we need to ensure that:
            // 1. The FSM is in a state where it can transition to WR.
            // 2. The conditions `!ground`, `dig`, and `bump_right` are all false.
            // First, ensure that the FSM is in a state where it can transition to WR.
            // For simplicity, let's assume the FSM starts in a state that can transition to WR.
            // If not, you may need to drive inputs to reach such a state.
            // Ensure `ground` is true
%000001     ground = 1;
%000001     #10;  // Allow some time for the FSM to settle
            // Ensure `dig` is false
%000001     dig = 0;
%000001     #10;  // Allow some time for the FSM to settle
            // Ensure `bump_right` is false
%000001     bump_right = 0;
%000001     #10;  // Allow some time for the FSM to settle
            // Now, the FSM should transition to WR because all higher-priority conditions are false.
            // Wait for a few clock cycles to ensure the transition occurs.
%000005     repeat(5) @(posedge clk);
            // To cover the other missing blocks, we need to ensure the FSM is in the correct states and conditions are met.
            // To cover "FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;"
            // 1. The FSM must be in the FALLL state.
            // 2. `ground` must be true.
            // 3. `fall_counter` must be >= 20.
            // Drive inputs to reach the FALLL state
            // Assuming the FSM can transition to FALLL from the current state
            // (If not, drive inputs to reach a state that can transition to FALLL)
%000001     ground = 1;
%000001     dig = 0;
%000001     bump_right = 0;
%000001     #10;  // Allow some time for the FSM to settle
            // Ensure `fall_counter` is >= 20
            // Since we cannot directly set `fall_counter`, we need to drive inputs to increment it.
            // Assuming `fall_counter` increments with each clock cycle while in FALLL state.
~000020     repeat(20) @(posedge clk);
            // Now, the FSM should transition to DEAD if `fall_counter` is >= 20.
            // Wait for a few clock cycles to ensure the transition occurs.
%000005     repeat(5) @(posedge clk);
            // To cover "FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;"
            // 1. The FSM must be in the FALLR state.
            // 2. `ground` must be true.
            // 3. `fall_counter` must be >= 20.
            // Drive inputs to reach the FALLR state
            // Assuming the FSM can transition to FALLR from the current state
            // (If not, drive inputs to reach a state that can transition to FALLR)
%000001     ground = 1;
%000001     dig = 0;
%000001     bump_right = 1;
%000001     #10;  // Allow some time for the FSM to settle
            // Ensure `fall_counter` is >= 20
            // Assuming `fall_counter` increments with each clock cycle while in FALLR state.
~000020     repeat(20) @(posedge clk);
            // Now, the FSM should transition to DEAD if `fall_counter` is >= 20.
            // Wait for a few clock cycles to ensure the transition occurs.
%000005     repeat(5) @(posedge clk);
            // To cover "DIGL: next = ground ? DIGL : FALLL;"
            // 1. The FSM must be in the DIGL state.
            // 2. `ground` must be true.
            // Drive inputs to reach the DIGL state
            // Assuming the FSM can transition to DIGL from the current state
            // (If not, drive inputs to reach a state that can transition to DIGL)
%000001     ground = 1;
%000001     dig = 1;
%000001     bump_right = 0;
%000001     #10;  // Allow some time for the FSM to settle
            // Now, the FSM should stay in DIGL if `ground` is true.
            // Wait for a few clock cycles to ensure the transition occurs.
%000005     repeat(5) @(posedge clk);
            // To cover "DIGR: next = ground ? DIGR : FALLR;"
            // 1. The FSM must be in the DIGR state.
            // 2. `ground` must be true.
            // Drive inputs to reach the DIGR state
            // Assuming the FSM can transition to DIGR from the current state
            // (If not, drive inputs to reach a state that can transition to DIGR)
%000001     ground = 1;
%000001     dig = 1;
%000001     bump_right = 1;
%000001     #10;  // Allow some time for the FSM to settle
            // Now, the FSM should stay in DIGR if `ground` is true.
            // Wait for a few clock cycles to ensure the transition occurs.
%000005     repeat(5) @(posedge clk);
            // Log results
%000001     $fdisplay(file, "[CGA-5] walk_left, walk_right, aaah, digging = %b, %b, %b, %b", walk_left, walk_right, aaah, digging);
            // ==============================================
        
        
        
        
        
%000001     $fclose(file);
%000001     $finish;
        end
        
        endmodule
        
