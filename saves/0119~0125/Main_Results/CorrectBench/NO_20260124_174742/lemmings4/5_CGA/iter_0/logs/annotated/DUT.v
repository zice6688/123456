//      // verilator_coverage annotation
        module top_module (
 000208 	input clk,
%000001 	input areset,
%000002 	input bump_left,
%000003 	input bump_right,
%000005 	input ground,
%000001 	input dig,
%000003 	output walk_left,
%000003 	output walk_right,
%000002 	output aaah,
%000000 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000002 	reg [2:0] state;
%000003 	reg [2:0] next;
            
~000016     reg [4:0] fall_counter;
            
 000834     always_comb begin
 000834 		case (state)
~000498 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
~000102 				else if (bump_left) next = WR;
 000102 				else next = WL;
 000052 			WR: 
~000498 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
~000041 				else if (bump_right) next = WL;
 000041 				else next = WR;
~000498 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000498 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000498 			DIGL: next = ground ? DIGL : FALLL;
~000498 			DIGR: next = ground ? DIGR : FALLR;
 000423 			DEAD: next = DEAD;
        		endcase
            end
            
 000209     always @(posedge clk, posedge areset) begin
~000207 		if (areset) state <= WL;
 000207         else state <= next;
        	end
        	
 000208 	always @(posedge clk) begin
 000146 		if (state == FALLL || state == FALLR) begin
 000031 			if (fall_counter < 20)
 000031 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000146 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
