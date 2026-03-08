//      // verilator_coverage annotation
        module top_module (
 000097 	input clk,
%000003 	input areset,
%000004 	input bump_left,
%000003 	input bump_right,
%000006 	input ground,
%000003 	input dig,
%000005 	output walk_left,
%000005 	output walk_right,
%000006 	output aaah,
%000002 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000006 	reg [2:0] state;
%000005 	reg [2:0] next;
            
~000020     reg [4:0] fall_counter;
            
 000485     always_comb begin
 000485 		case (state)
 000287 			WL: if (!ground) next = FALLL;
%000005 				else if (dig) next = DIGL;
~000050 				else if (bump_left) next = WR;
 000050 				else next = WL;
 000060 			WR: 
 000287 				if (!ground) next = FALLR;
%000004 				else if (dig) next = DIGR;
~000040 				else if (bump_right) next = WL;
 000040 				else next = WR;
~000287 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000287 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000287 			DIGL: next = ground ? DIGL : FALLL;
~000287 			DIGR: next = ground ? DIGR : FALLR;
%000007 			DEAD: next = DEAD;
        		endcase
            end
            
 000099     always @(posedge clk, posedge areset) begin
~000093 		if (areset) state <= WL;
 000093         else state <= next;
        	end
        	
 000097 	always @(posedge clk) begin
 000060 		if (state == FALLL || state == FALLR) begin
~000036 			if (fall_counter < 20)
 000036 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000060 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
