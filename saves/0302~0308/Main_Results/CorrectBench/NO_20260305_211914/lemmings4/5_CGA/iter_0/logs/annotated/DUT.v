//      // verilator_coverage annotation
        module top_module (
 000096 	input clk,
%000001 	input areset,
%000003 	input bump_left,
%000003 	input bump_right,
%000009 	input ground,
%000002 	input dig,
%000005 	output walk_left,
%000001 	output walk_right,
%000004 	output aaah,
%000000 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000004 	reg [2:0] state;
%000004 	reg [2:0] next;
            
~000015     reg [4:0] fall_counter;
            
 000386     always_comb begin
 000386 		case (state)
 000240 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
~000036 				else if (bump_left) next = WR;
 000036 				else next = WL;
 000012 			WR: 
~000240 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
%000009 				else if (bump_right) next = WL;
%000009 				else next = WR;
~000240 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000240 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000240 			DIGL: next = ground ? DIGL : FALLL;
~000240 			DIGR: next = ground ? DIGR : FALLR;
 000203 			DEAD: next = DEAD;
        		endcase
            end
            
 000097     always @(posedge clk, posedge areset) begin
~000095 		if (areset) state <= WL;
 000095         else state <= next;
        	end
        	
 000096 	always @(posedge clk) begin
~000066 		if (state == FALLL || state == FALLR) begin
~000028 			if (fall_counter < 20)
 000028 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000066 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
