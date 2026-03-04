```verilog
`timescale 1ns / 1ps

module testbench;
reg clk;
reg [7:0] in;
reg reset;
wire [23:0] out_bytes;
wire done;

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
    reset = 1; in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    reset = 1; in = 8'h00; #10;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    reset = 0; in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h2C; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h81; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h09; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    
    // Scenario 2
    scenario = 2;
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h2C; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h81; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h09; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h6B; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h0D; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h8D; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    
    // Scenario 3
    scenario = 3;
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h2C; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h81; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h09; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h6D; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h12; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h01; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    
    // Scenario 4
    scenario = 4;
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h2C; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h81; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h09; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h6B; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h0D; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h8D; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'hED; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h8C; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'hF9; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    
    // Scenario 5
    scenario = 5;
    in = 8'h2C; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h81; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h09; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h6D; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h12; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h01; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'hED; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h8C; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'hF9; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    
    // Scenario 6
    scenario = 6;
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h2C; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h81; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h09; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h6B; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h0D; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h8D; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h6D; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h12; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h01; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    
    // Scenario 7
    scenario = 7;
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h2C; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h81; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h09; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h6B; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h0D; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h8D; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'hED; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h8C; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'hF9; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    
    // Scenario 8
    scenario = 8;
    in = 8'h00; $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    in = 8'h00; #10; 
    $fdisplay(file, "scenario: %d, clk = %d, in = %d,