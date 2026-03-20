//      // verilator_coverage annotation
        module top_module (
 000164 	input clk,
%000004 	input areset,
%000003 	input bump_left,
%000005 	input bump_right,
 000010 	input ground,
%000002 	input dig,
%000005 	output walk_left,
%000004 	output walk_right,
%000006 	output aaah,
%000000 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000006 	reg [2:0] state;
%000004 	reg [2:0] next;
            
~000028     reg [4:0] fall_counter;
            
 000820     always_comb begin
 000820 		case (state)
 000645 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
~000040 				else if (bump_left) next = WR;
 000040 				else next = WL;
 000050 			WR: 
 000645 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
~000033 				else if (bump_right) next = WL;
 000033 				else next = WR;
~000645 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000645 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000645 			DIGL: next = ground ? DIGL : FALLL;
~000645 			DIGR: next = ground ? DIGR : FALLR;
 000420 			DEAD: next = DEAD;
        		endcase
            end
            
 000165     always @(posedge clk, posedge areset) begin
~000157 		if (areset) state <= WL;
 000157         else state <= next;
        	end
        	
 000164 	always @(posedge clk) begin
 000110 		if (state == FALLL || state == FALLR) begin
~000052 			if (fall_counter < 20)
 000052 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000110 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
