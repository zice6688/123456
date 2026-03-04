```verilog
`timescale 1ns / 1ps
module testbench;
reg  clk;
reg [7:0] in;
reg  reset;
wire [23:0] out_bytes;
wire  done;

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
    reset = 1; in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    reset = 1; in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    reset = 0; in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h2C; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h81; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h09; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 

    // Scenario 2
    scenario = 2;
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h2C; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h81; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h09; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h6B; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h0D; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h8D; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 

    // Scenario 3
    scenario = 3;
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h2C; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h81; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h09; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h6D; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h12; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h01; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 

    // Scenario 4
    scenario = 4;
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h2C; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h81; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h09; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h6B; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h0D; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h8D; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'hED; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h8C; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'hF9; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 

    // Scenario 5
    scenario = 5;
    in = 8'h2C; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h81; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h09; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h6D; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h12; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h01; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'hED; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h8C; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'hF9; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 

    // Scenario 6
    scenario = 6;
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h2C; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h81; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h09; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);fdisplay(file, "scenario: %d, clk = %d, in = %d, reset