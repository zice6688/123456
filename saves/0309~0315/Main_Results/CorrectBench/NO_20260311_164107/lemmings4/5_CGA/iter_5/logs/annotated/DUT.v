//      // verilator_coverage annotation
        module top_module (
 000180 	input clk,
%000003 	input areset,
%000004 	input bump_left,
%000004 	input bump_right,
 000011 	input ground,
%000003 	input dig,
%000005 	output walk_left,
%000004 	output walk_right,
%000006 	output aaah,
%000001 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000006 	reg [2:0] state;
%000004 	reg [2:0] next;
            
~000026     reg [4:0] fall_counter;
            
 000900     always_comb begin
 000900 		case (state)
 000640 			WL: if (!ground) next = FALLL;
%000005 				else if (dig) next = DIGL;
~000040 				else if (bump_left) next = WR;
 000040 				else next = WL;
 000050 			WR: 
 000640 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
~000033 				else if (bump_right) next = WL;
 000033 				else next = WR;
~000640 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000640 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000640 			DIGL: next = ground ? DIGL : FALLL;
~000640 			DIGR: next = ground ? DIGR : FALLR;
 000420 			DEAD: next = DEAD;
        		endcase
            end
            
 000182     always @(posedge clk, posedge areset) begin
~000176 		if (areset) state <= WL;
 000176         else state <= next;
        	end
        	
 000180 	always @(posedge clk) begin
 000125 		if (state == FALLL || state == FALLR) begin
~000050 			if (fall_counter < 20)
 000050 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000125 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
