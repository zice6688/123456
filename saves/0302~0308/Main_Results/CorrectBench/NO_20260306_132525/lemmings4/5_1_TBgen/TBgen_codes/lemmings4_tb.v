module testbench;
reg  clk;
reg  areset;
reg  bump_left;
reg  bump_right;
reg  ground;
reg  dig;
wire  walk_left;
wire  walk_right;
wire  aaah;
wire  digging;

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
    areset = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    areset = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 2
    scenario = 2;
    bump_left = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    bump_left = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 3
    scenario = 3;
    bump_right = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    bump_right = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 4
    scenario = 4;
    ground = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    ground = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 5
    scenario = 5;
    ground = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    ground = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 6
    scenario = 6;
    dig = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    dig = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 7
    scenario = 7;
    dig = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    dig = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 8
    scenario = 8;
    ground = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    ground = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 9
    scenario = 9;
    ground = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 10
    scenario = 10;
    ground = 0; repeat(21) begin $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10;  end
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
    ground = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 11
    scenario = 11;
    ground = 0; repeat(21) begin $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10;  end
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
    ground = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 12
    scenario = 12;
    bump_left = 1; bump_right = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    bump_left = 0; bump_right = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 13
    scenario = 13;
    bump_left = 1; bump_right = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    bump_left = 0; bump_right = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 14
    scenario = 14;
    bump_left = 1; ground = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    bump_left = 0; ground = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 15
    scenario = 15;
    bump_right = 1; ground = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    bump_right = 0; ground = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 16
    scenario = 16;
    bump_left = 1; dig = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    bump_left = 0; dig = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 17
    scenario = 17;
    bump_right = 1; dig = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    bump_right = 0; dig = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 18
    scenario = 18;
    ground = 0; dig = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    ground = 1; dig = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 19
    scenario = 19;
    ground = 0; dig = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    ground = 1; dig = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 

    // Scenario 20
    scenario = 20;
    ground = 0; repeat(20) begin $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10;  end
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging); #10; 
    ground = 1; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10; 
    ground = 0; 
    $fdisplay(file, "scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);
    #10;
    $fdisplay(file, "[check]scenario: %d, clk = %d, areset = %d, bump_left = %d, bump_right = %d, ground = %d, dig = %d, walk_left = %d, walk_right = %d, aaah = %d, digging = %d", scenario, clk, areset, bump_left, bump_right, ground, dig, walk_left, walk_right, aaah, digging);

    $fclose(file);
    $finish;
end

endmodule
