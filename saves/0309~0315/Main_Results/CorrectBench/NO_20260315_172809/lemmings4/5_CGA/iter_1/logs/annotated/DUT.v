//      // verilator_coverage annotation
        module top_module (
 000082 	input clk,
%000002 	input areset,
%000001 	input bump_left,
%000001 	input bump_right,
%000007 	input ground,
%000003 	input dig,
%000007 	output walk_left,
%000001 	output walk_right,
%000005 	output aaah,
%000001 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000005 	reg [2:0] state;
%000004 	reg [2:0] next;
            
~000021     reg [4:0] fall_counter;
            
 000410     always_comb begin
 000410 		case (state)
 000233 			WL: if (!ground) next = FALLL;
%000005 				else if (dig) next = DIGL;
~000034 				else if (bump_left) next = WR;
 000034 				else next = WL;
 000015 			WR: 
~000233 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
~000011 				else if (bump_right) next = WL;
 000011 				else next = WR;
~000233 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000233 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000233 			DIGL: next = ground ? DIGL : FALLL;
~000233 			DIGR: next = ground ? DIGR : FALLR;
 000060 			DEAD: next = DEAD;
        		endcase
            end
            
 000083     always @(posedge clk, posedge areset) begin
~000079 		if (areset) state <= WL;
 000079         else state <= next;
        	end
        	
 000082 	always @(posedge clk) begin
~000042 		if (state == FALLL || state == FALLR) begin
~000040 			if (fall_counter < 20)
 000040 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000040 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
