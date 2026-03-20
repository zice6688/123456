//      // verilator_coverage annotation
        module top_module (
 000062 	input clk,
%000001 	input areset,
%000001 	input bump_left,
%000001 	input bump_right,
%000006 	input ground,
%000002 	input dig,
%000005 	output walk_left,
%000001 	output walk_right,
%000004 	output aaah,
%000000 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000004 	reg [2:0] state;
%000004 	reg [2:0] next;
            
~000018     reg [4:0] fall_counter;
            
 000250     always_comb begin
 000250 		case (state)
 000156 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
~000028 				else if (bump_left) next = WR;
 000028 				else next = WL;
 000012 			WR: 
~000156 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
%000009 				else if (bump_right) next = WL;
%000009 				else next = WR;
~000156 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000156 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000156 			DIGL: next = ground ? DIGL : FALLL;
~000156 			DIGR: next = ground ? DIGR : FALLR;
 000047 			DEAD: next = DEAD;
        		endcase
            end
            
 000063     always @(posedge clk, posedge areset) begin
~000061 		if (areset) state <= WL;
 000061         else state <= next;
        	end
        	
 000062 	always @(posedge clk) begin
~000037 		if (state == FALLL || state == FALLR) begin
~000035 			if (fall_counter < 20)
 000035 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000025 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
