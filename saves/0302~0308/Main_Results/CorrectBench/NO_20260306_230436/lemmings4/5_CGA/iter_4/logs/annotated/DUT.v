//      // verilator_coverage annotation
        module top_module (
 000201 	input clk,
%000002 	input areset,
%000005 	input bump_left,
%000005 	input bump_right,
%000005 	input ground,
%000006 	input dig,
%000007 	output walk_left,
%000003 	output walk_right,
%000004 	output aaah,
%000000 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000004 	reg [2:0] state;
%000005 	reg [2:0] next;
            
~000032     reg [4:0] fall_counter;
            
 001005     always_comb begin
 001005 		case (state)
 000810 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
 000068 				else if (bump_left) next = WR;
 000068 				else next = WL;
 000025 			WR: 
~000810 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
 000013 				else if (bump_right) next = WL;
 000013 				else next = WR;
~000810 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000810 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000810 			DIGL: next = ground ? DIGL : FALLL;
~000810 			DIGR: next = ground ? DIGR : FALLR;
 000465 			DEAD: next = DEAD;
        		endcase
            end
            
 000202     always @(posedge clk, posedge areset) begin
~000198 		if (areset) state <= WL;
 000198         else state <= next;
        	end
        	
 000201 	always @(posedge clk) begin
~000119 		if (state == FALLL || state == FALLR) begin
 000062 			if (fall_counter < 20)
 000062 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000119 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
