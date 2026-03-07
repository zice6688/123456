`timescale 1ns / 1ps

module top_module_tb;
    reg in;
    wire out;
    reg clk;
    integer file;
    integer scenario;

    // Instantiate the DUT
    top_module DUT (
        .in(in),
        .out(out)
    );

    // Initialize the clock
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // 10 ns period clock
    end

    // Initialize the testbench
    initial begin
        // Open the file for writing
        file = $fopen("TBout.txt", "w");
        if (file == 0) begin
            $display("Error: Unable to open file TBout.txt");
            $finish;
        end

        // Scenario 1: Initialize input 'in' to 0 and apply for 2 clock cycles
        scenario = 1;
        in = 0;
        #10; // Wait for one clock cycle
        $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        #10; // Wait for one more clock cycle
        $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);

        // Scenario 2: Change input 'in' to 1 and apply for 2 clock cycles
        scenario = 2;
        in = 1;
        #10; // Wait for one clock cycle
        $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        #10; // Wait for one more clock cycle
        $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);

        // Scenario 3: Change input 'in' back to 0 and apply for 2 clock cycles
        scenario = 3;
        in = 0;
        #10; // Wait for one clock cycle
        $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        #10; // Wait for one more clock cycle
        $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);

        // Scenario 4: Change input 'in' to 1 again and apply for 2 clock cycles
        scenario = 4;
        in = 1;
        #10; // Wait for one clock cycle
        $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        #10; // Wait for one more clock cycle
        $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);

        // Close the file
        $fclose(file);
        $finish;
    end
endmodule
