//      // verilator_coverage annotation
        module top_module (
 000115 	input clk,
%000001 	input areset,
%000003 	input bump_left,
%000002 	input bump_right,
%000004 	input ground,
%000001 	input dig,
%000002 	output walk_left,
%000003 	output walk_right,
%000002 	output aaah,
%000001 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000002 	reg [2:0] state;
%000003 	reg [2:0] next;
            
~000013     reg [4:0] fall_counter;
            
 000462     always_comb begin
 000462 		case (state)
~000286 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
~000053 				else if (bump_left) next = WR;
 000053 				else next = WL;
 000080 			WR: 
~000286 				if (!ground) next = FALLR;
%000003 				else if (dig) next = DIGR;
~000070 				else if (bump_right) next = WL;
 000070 				else next = WR;
~000286 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000286 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000286 			DIGL: next = ground ? DIGL : FALLL;
~000286 			DIGR: next = ground ? DIGR : FALLR;
 000163 			DEAD: next = DEAD;
        		endcase
            end
            
 000116     always @(posedge clk, posedge areset) begin
~000114 		if (areset) state <= WL;
 000114         else state <= next;
        	end
        	
 000115 	always @(posedge clk) begin
~000081 		if (state == FALLL || state == FALLR) begin
~000026 			if (fall_counter < 20)
 000026 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000081 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
