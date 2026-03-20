//      // verilator_coverage annotation
        module top_module (
 000343 	input clk,
%000005 	input areset,
%000004 	input bump_left,
%000008 	input bump_right,
 000014 	input ground,
%000007 	input dig,
 000015 	output walk_left,
%000002 	output walk_right,
 000014 	output aaah,
%000005 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
~000014 	reg [2:0] state;
~000010 	reg [2:0] next;
            
~000049     reg [4:0] fall_counter;
            
 001715     always_comb begin
 001715 		case (state)
 001127 			WL: if (!ground) next = FALLL;
 000016 				else if (dig) next = DIGL;
 000129 				else if (bump_left) next = WR;
 000129 				else next = WL;
 000010 			WR: 
~001127 				if (!ground) next = FALLR;
%000001 				else if (dig) next = DIGR;
%000009 				else if (bump_right) next = WL;
%000000 				else next = WR;
~001127 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~001127 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~001127 			DIGL: next = ground ? DIGL : FALLL;
~001127 			DIGR: next = ground ? DIGR : FALLR;
 000745 			DEAD: next = DEAD;
        		endcase
            end
            
 000347     always @(posedge clk, posedge areset) begin
 000337 		if (areset) state <= WL;
 000337         else state <= next;
        	end
        	
 000343 	always @(posedge clk) begin
~000241 		if (state == FALLL || state == FALLR) begin
 000091 			if (fall_counter < 20)
 000091 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000241 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
