//      // verilator_coverage annotation
        module top_module (
 000093 	input clk,
%000001 	input areset,
%000002 	input bump_left,
%000002 	input bump_right,
%000006 	input ground,
%000002 	input dig,
%000005 	output walk_left,
%000000 	output walk_right,
%000005 	output aaah,
%000002 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000005 	reg [2:0] state;
%000005 	reg [2:0] next;
            
~000021     reg [4:0] fall_counter;
            
 000374     always_comb begin
 000374 		case (state)
 000248 			WL: if (!ground) next = FALLL;
%000006 				else if (dig) next = DIGL;
~000020 				else if (bump_left) next = WR;
 000020 				else next = WL;
%000000 			WR: 
~000248 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
%000000 				else if (bump_right) next = WL;
%000000 				else next = WR;
~000248 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000248 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000248 			DIGL: next = ground ? DIGL : FALLL;
~000248 			DIGR: next = ground ? DIGR : FALLR;
 000095 			DEAD: next = DEAD;
        		endcase
            end
            
 000094     always @(posedge clk, posedge areset) begin
~000092 		if (areset) state <= WL;
 000092         else state <= next;
        	end
        	
 000093 	always @(posedge clk) begin
~000053 		if (state == FALLL || state == FALLR) begin
~000039 			if (fall_counter < 20)
 000039 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000053 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
