//      // verilator_coverage annotation
        module top_module (
 000155 	input clk,
%000003 	input areset,
%000006 	input bump_left,
%000006 	input bump_right,
%000008 	input ground,
%000002 	input dig,
%000008 	output walk_left,
%000001 	output walk_right,
%000007 	output aaah,
%000005 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000007 	reg [2:0] state;
%000007 	reg [2:0] next;
            
~000034     reg [4:0] fall_counter;
            
 000775     always_comb begin
 000775 		case (state)
~000497 			WL: if (!ground) next = FALLL;
 000032 				else if (dig) next = DIGL;
~000038 				else if (bump_left) next = WR;
 000038 				else next = WL;
 000015 			WR: 
~000497 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
~000011 				else if (bump_right) next = WL;
 000011 				else next = WR;
~000497 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000497 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
 000497 			DIGL: next = ground ? DIGL : FALLL;
~000497 			DIGR: next = ground ? DIGR : FALLR;
 000147 			DEAD: next = DEAD;
        		endcase
            end
            
 000158     always @(posedge clk, posedge areset) begin
~000152 		if (areset) state <= WL;
 000152         else state <= next;
        	end
        	
 000155 	always @(posedge clk) begin
~000082 		if (state == FALLL || state == FALLR) begin
~000067 			if (fall_counter < 20)
 000067 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000082 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
