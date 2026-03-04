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

    // Scenario 1
    scenario = 1;
    reset = 1;
    in = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(2) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    reset = 0;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end

    // Scenario 2
    scenario = 2;
    {in} = 8'b0_01010101_1; // Start bit, 8 data bits, stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(10) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end

    // Scenario 3
    scenario = 3;
    {in} = 8'b0_01010101_0; // Start bit, 8 data bits, incorrect stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(10) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1; // Correct stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
    #10;
    in = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end

    // Scenario 4
    scenario = 4;
    {in} = 8'b0_01010101_1; // First byte
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(10) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    {in} = 8'b0_01010101_1; // Second byte
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(10) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end

    // Scenario 5
    scenario = 5;
    {in} = 9'b0_0101_0_0101_1; // Start bit, first 4 data bits, additional bit, remaining 4 data bits, stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(11) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end

    // Scenario 6
    scenario = 6;
    {in} = 9'b0_0101_1_0101_1; // Start bit, first 4 data bits, additional bit, remaining 4 data bits, stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(11) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end

    // Scenario 7
    scenario = 7;
    {in} = 9'b0_01010101_0_1; // Start bit, 8 data bits, additional bit, stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(11) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end

    // Scenario 8
    scenario = 8;
    {in} = 9'b0_01010101_1_1; // Start bit, 8 data bits, additional bit, stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(11) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end

    // Scenario 9
    scenario = 9;
    {in} = 9'b0_0_01010101_1; // Additional bit, start bit, 8 data bits, stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(11) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end

    // Scenario 10
    scenario = 10;
    {in} = 9'b1_0_01010101_1; // Additional bit, start bit, 8 data bits, stop bit
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(11) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end
    in = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done); #10; 
    repeat(5) begin
        $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, done = %d", scenario, clk, in, reset, done);
        #10;
    end

    $fclose(file);
    $finish;
end

endmodule
