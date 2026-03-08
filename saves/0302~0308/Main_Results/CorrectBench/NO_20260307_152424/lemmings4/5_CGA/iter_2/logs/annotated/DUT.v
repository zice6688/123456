//      // verilator_coverage annotation
        module top_module (
 000137 	input clk,
%000003 	input areset,
%000004 	input bump_left,
%000003 	input bump_right,
%000007 	input ground,
%000003 	input dig,
%000006 	output walk_left,
%000004 	output walk_right,
%000006 	output aaah,
%000002 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000006 	reg [2:0] state;
%000005 	reg [2:0] next;
            
~000038     reg [4:0] fall_counter;
            
 000685     always_comb begin
 000685 		case (state)
 000428 			WL: if (!ground) next = FALLL;
%000005 				else if (dig) next = DIGL;
~000046 				else if (bump_left) next = WR;
 000046 				else next = WL;
 000050 			WR: 
~000428 				if (!ground) next = FALLR;
%000004 				else if (dig) next = DIGR;
~000033 				else if (bump_right) next = WL;
 000033 				else next = WR;
~000428 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000428 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000428 			DIGL: next = ground ? DIGL : FALLL;
~000428 			DIGR: next = ground ? DIGR : FALLR;
 000012 			DEAD: next = DEAD;
        		endcase
            end
            
 000139     always @(posedge clk, posedge areset) begin
~000133 		if (areset) state <= WL;
 000133         else state <= next;
        	end
        	
 000137 	always @(posedge clk) begin
 000083 		if (state == FALLL || state == FALLR) begin
~000075 			if (fall_counter < 20)
 000075 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000054 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
