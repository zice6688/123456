//      // verilator_coverage annotation
        `timescale 1ns / 1ps
        
        module top_module_tb;
%000002     reg in;
%000002     wire out;
%000008     reg clk;
            integer file;
            integer scenario;
        
            // Instantiate the DUT
            top_module DUT (
                .in(in),
                .out(out)
            );
        
            // Initialize the clock
%000000     initial begin
%000000         clk = 0;
~000016         forever #5 clk = ~clk; // 10 ns period clock
            end
        
            // Initialize the testbench
%000001     initial begin
                // Open the file for writing
%000001         file = $fopen("TBout.txt", "w");
%000001         if (file == 0) begin
%000000             $display("Error: Unable to open file TBout.txt");
%000000             $finish;
                end
        
                // Scenario 1: Initialize input 'in' to 0 and apply for 2 clock cycles
%000001         scenario = 1;
%000001         in = 0;
%000001         #10; // Wait for one clock cycle
%000001         $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
%000001         #10; // Wait for one more clock cycle
%000001         $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        
                // Scenario 2: Change input 'in' to 1 and apply for 2 clock cycles
%000001         scenario = 2;
%000001         in = 1;
%000001         #10; // Wait for one clock cycle
%000001         $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
%000001         #10; // Wait for one more clock cycle
%000001         $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        
                // Scenario 3: Change input 'in' back to 0 and apply for 2 clock cycles
%000001         scenario = 3;
%000001         in = 0;
%000001         #10; // Wait for one clock cycle
%000001         $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
%000001         #10; // Wait for one more clock cycle
%000001         $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        
                // Scenario 4: Change input 'in' to 1 again and apply for 2 clock cycles
%000001         scenario = 4;
%000001         in = 1;
%000001         #10; // Wait for one clock cycle
%000001         $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
%000001         #10; // Wait for one more clock cycle
%000001         $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        
                // Close the file
%000001         $fclose(file);
%000001         $finish;
            end
        endmodule
        
