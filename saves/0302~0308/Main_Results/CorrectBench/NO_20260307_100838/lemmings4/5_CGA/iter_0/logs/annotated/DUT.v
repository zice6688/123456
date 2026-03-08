//      // verilator_coverage annotation
        module top_module (
 000054 	input clk,
%000002 	input areset,
%000003 	input bump_left,
%000003 	input bump_right,
%000005 	input ground,
%000002 	input dig,
%000003 	output walk_left,
%000005 	output walk_right,
%000005 	output aaah,
%000001 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000005 	reg [2:0] state;
%000005 	reg [2:0] next;
            
~000014     reg [4:0] fall_counter;
            
 000218     always_comb begin
 000218 		case (state)
~000110 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
~000040 				else if (bump_left) next = WR;
 000040 				else next = WL;
 000048 			WR: 
~000110 				if (!ground) next = FALLR;
%000003 				else if (dig) next = DIGR;
~000033 				else if (bump_right) next = WL;
 000033 				else next = WR;
~000110 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000110 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000110 			DIGL: next = ground ? DIGL : FALLL;
~000110 			DIGR: next = ground ? DIGR : FALLR;
%000006 			DEAD: next = DEAD;
        		endcase
            end
            
 000056     always @(posedge clk, posedge areset) begin
~000052 		if (areset) state <= WL;
 000052         else state <= next;
        	end
        	
 000054 	always @(posedge clk) begin
~000028 		if (state == FALLL || state == FALLR) begin
~000025 			if (fall_counter < 20)
 000025 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000028 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
