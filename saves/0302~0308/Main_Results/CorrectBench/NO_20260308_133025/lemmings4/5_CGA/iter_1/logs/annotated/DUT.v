//      // verilator_coverage annotation
        module top_module (
 000213 	input clk,
%000002 	input areset,
%000003 	input bump_left,
%000002 	input bump_right,
%000006 	input ground,
%000002 	input dig,
%000003 	output walk_left,
%000000 	output walk_right,
%000002 	output aaah,
%000001 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000002 	reg [2:0] state;
%000002 	reg [2:0] next;
            
~000015     reg [4:0] fall_counter;
            
 001065     always_comb begin
 001065 		case (state)
 000788 			WL: if (!ground) next = FALLL;
%000005 				else if (dig) next = DIGL;
%000000 				else if (bump_left) next = WR;
%000000 				else next = WL;
%000000 			WR: 
~000788 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
%000000 				else if (bump_right) next = WL;
%000000 				else next = WR;
~000788 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000788 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000788 			DIGL: next = ground ? DIGL : FALLL;
~000788 			DIGR: next = ground ? DIGR : FALLR;
 000745 			DEAD: next = DEAD;
        		endcase
            end
            
 000214     always @(posedge clk, posedge areset) begin
~000210 		if (areset) state <= WL;
 000210         else state <= next;
        	end
        	
 000213 	always @(posedge clk) begin
~000172 		if (state == FALLL || state == FALLR) begin
 000030 			if (fall_counter < 20)
 000030 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000172 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
