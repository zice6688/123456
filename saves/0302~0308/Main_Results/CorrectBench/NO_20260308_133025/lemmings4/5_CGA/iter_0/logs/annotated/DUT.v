//      // verilator_coverage annotation
        module top_module (
 000181 	input clk,
%000001 	input areset,
%000003 	input bump_left,
%000002 	input bump_right,
%000005 	input ground,
%000001 	input dig,
%000001 	output walk_left,
%000000 	output walk_right,
%000001 	output aaah,
%000000 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000001 	reg [2:0] state;
%000001 	reg [2:0] next;
            
~000010     reg [4:0] fall_counter;
            
 000726     always_comb begin
 000726 		case (state)
~000582 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
%000000 				else if (bump_left) next = WR;
%000000 				else next = WL;
%000000 			WR: 
~000582 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
%000000 				else if (bump_right) next = WL;
%000000 				else next = WR;
~000582 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000582 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000582 			DIGL: next = ground ? DIGL : FALLL;
~000582 			DIGR: next = ground ? DIGR : FALLR;
 000595 			DEAD: next = DEAD;
        		endcase
            end
            
 000182     always @(posedge clk, posedge areset) begin
~000180 		if (areset) state <= WL;
 000180         else state <= next;
        	end
        	
 000181 	always @(posedge clk) begin
~000150 		if (state == FALLL || state == FALLR) begin
 000020 			if (fall_counter < 20)
 000020 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000150 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
