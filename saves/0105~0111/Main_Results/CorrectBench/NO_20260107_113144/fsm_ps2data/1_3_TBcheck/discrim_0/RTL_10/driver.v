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
    reset = 1; in = 8'h00;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    reset = 0; in = 8'h00;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h2c;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h81;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h09;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 

    // Scenario 2
    scenario = 2;
    in = 8'h6b;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h0d;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h8d;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h6d;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h12;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h01;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 

    // Scenario 3
    scenario = 3;
    in = 8'h6d;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h12;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h01;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h76;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h3d;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hed;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 

    // Scenario 4
    scenario = 4;
    in = 8'h00;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10;
    repeat(10) begin
        $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    end
    in = 8'hed;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h8c;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hf9;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 

    // Scenario 5
    scenario = 5;
    in = 8'hce;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hc5;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'haa;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    reset = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    reset = 0;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hc5;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'haa;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hce;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 

    // Scenario 6
    scenario = 6;
    in = 8'hc5;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'haa;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hce;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    reset = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    reset = 0;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hc5;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h00;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10;
    repeat(10) begin
        $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    end
    in = 8'haa;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hce;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 

    // Scenario 7
    scenario = 7;
    in = 8'hc5;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'haa;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hce;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    reset = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    reset = 0;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hc5;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h00;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10;
    repeat(10) begin
        $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    end
    in = 8'hc5;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'haa;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hce;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 

    // Scenario 8
    scenario = 8;
    in = 8'hc5;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'haa;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hce;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    reset = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    reset = 0;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hc5;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'h00;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10;
    repeat(10) begin
        $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done); #10; 
    end
    reset = 1;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    reset = 0;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hc5;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'haa;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    in = 8'hce;
    $fdisplay(file, "scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, in = %d, reset = %d, out_bytes = %d, done = %d", scenario, clk, in, reset, out_bytes, done);

    $fclose(file);
    $finish;
end

endmodule
