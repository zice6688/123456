`timescale 1ns / 1ps

module top_module_tb;
    reg in;
    wire out;
    integer file;
    integer scenario;
    integer i;

    // Instantiate the DUT
    top_module DUT (
        .in(in),
        .out(out)
    );

    initial begin
        // Open the file for writing
        file = $fopen("TBout.txt", "w");

        // Scenario 1: Set the input 'in' to 0 and hold it for 10 clock cycles.
        scenario = 1;
        in = 0;
        for (i = 0; i < 10; i = i + 1) begin
            #10; // Wait for 10 time units to ensure signals are stable
            $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        end

        // Scenario 2: Set the input 'in' to 1 and hold it for 10 clock cycles.
        scenario = 2;
        in = 1;
        for (i = 0; i < 10; i = i + 1) begin
            #10; // Wait for 10 time units to ensure signals are stable
            $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        end

        // Scenario 3: Toggle the input 'in' between 0 and 1, changing it every clock cycle for 20 clock cycles.
        scenario = 3;
        for (i = 0; i < 20; i = i + 1) begin
            in = ~in;
            #10; // Wait for 10 time units to ensure signals are stable
            $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        end

        // Scenario 4: Generate a sequence of random values for 'in' over 50 clock cycles.
        scenario = 4;
        for (i = 0; i < 50; i = i + 1) begin
            in = $random % 2; // Generate a random value (0 or 1)
            #10; // Wait for 10 time units to ensure signals are stable
            $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        end

        // Scenario 5: Set the input 'in' to 0 for 5 clock cycles, then set it to 1 for 5 clock cycles, and repeat this pattern for a total of 50 clock cycles.
        scenario = 5;
        for (i = 0; i < 50; i = i + 1) begin
            if (i % 10 < 5) begin
                in = 0;
            end else begin
                in = 1;
            end
            #10; // Wait for 10 time units to ensure signals are stable
            $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        end

        // Scenario 6: Set the input 'in' to 1 for 5 clock cycles, then set it to 0 for 5 clock cycles, and repeat this pattern for a total of 50 clock cycles.
        scenario = 6;
        for (i = 0; i < 50; i = i + 1) begin
            if (i % 10 < 5) begin
                in = 1;
            end else begin
                in = 0;
            end
            #10; // Wait for 10 time units to ensure signals are stable
            $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        end

        // Scenario 7: Set the input 'in' to 0 for 1 clock cycle, then set it to 1 for 1 clock cycle, and repeat this pattern for a total of 100 clock cycles.
        scenario = 7;
        for (i = 0; i < 100; i = i + 1) begin
            in = i % 2; // Toggle between 0 and 1
            #10; // Wait for 10 time units to ensure signals are stable
            $fdisplay(file, "scenario: %d, in = %d, out = %d", scenario, in, out);
        end

        // Close the file
        $fclose(file);
        $finish;
    end
endmodule
