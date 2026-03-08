//      // verilator_coverage annotation
        module top_module (
 000108 	input clk,
%000002 	input areset,
%000003 	input bump_left,
%000003 	input bump_right,
%000006 	input ground,
%000002 	input dig,
%000004 	output walk_left,
%000004 	output walk_right,
%000005 	output aaah,
%000001 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000005 	reg [2:0] state;
%000005 	reg [2:0] next;
            
~000033     reg [4:0] fall_counter;
            
 000434     always_comb begin
 000434 		case (state)
~000292 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
~000037 				else if (bump_left) next = WR;
 000037 				else next = WL;
 000040 			WR: 
~000292 				if (!ground) next = FALLR;
%000003 				else if (dig) next = DIGR;
~000027 				else if (bump_right) next = WL;
 000027 				else next = WR;
~000292 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000292 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000292 			DIGL: next = ground ? DIGL : FALLL;
~000292 			DIGR: next = ground ? DIGR : FALLR;
%000009 			DEAD: next = DEAD;
        		endcase
            end
            
 000110     always @(posedge clk, posedge areset) begin
~000106 		if (areset) state <= WL;
 000106         else state <= next;
        	end
        	
 000108 	always @(posedge clk) begin
 000073 		if (state == FALLL || state == FALLR) begin
~000065 			if (fall_counter < 20)
 000065 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000035 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
