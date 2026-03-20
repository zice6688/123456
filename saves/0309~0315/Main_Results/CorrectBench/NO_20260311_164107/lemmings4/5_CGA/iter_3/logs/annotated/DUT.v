//      // verilator_coverage annotation
        module top_module (
 000153 	input clk,
%000002 	input areset,
%000003 	input bump_left,
%000003 	input bump_right,
 000010 	input ground,
%000002 	input dig,
%000003 	output walk_left,
%000004 	output walk_right,
%000004 	output aaah,
%000000 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000004 	reg [2:0] state;
%000004 	reg [2:0] next;
            
~000023     reg [4:0] fall_counter;
            
 000765     always_comb begin
 000765 		case (state)
 000590 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
~000040 				else if (bump_left) next = WR;
 000040 				else next = WL;
 000050 			WR: 
 000590 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
~000033 				else if (bump_right) next = WL;
 000033 				else next = WR;
~000590 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000590 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000590 			DIGL: next = ground ? DIGL : FALLL;
~000590 			DIGR: next = ground ? DIGR : FALLR;
 000420 			DEAD: next = DEAD;
        		endcase
            end
            
 000154     always @(posedge clk, posedge areset) begin
~000150 		if (areset) state <= WL;
 000150         else state <= next;
        	end
        	
 000153 	always @(posedge clk) begin
 000106 		if (state == FALLL || state == FALLR) begin
~000045 			if (fall_counter < 20)
 000045 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000106 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
