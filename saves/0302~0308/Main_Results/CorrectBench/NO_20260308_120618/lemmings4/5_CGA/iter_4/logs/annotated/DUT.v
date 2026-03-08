//      // verilator_coverage annotation
        module top_module (
 000088 	input clk,
 000012 	input areset,
%000004 	input bump_left,
%000004 	input bump_right,
%000008 	input ground,
%000004 	input dig,
 000010 	output walk_left,
%000002 	output walk_right,
%000008 	output aaah,
%000003 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000008 	reg [2:0] state;
%000008 	reg [2:0] next;
            
~000025     reg [4:0] fall_counter;
            
 000440     always_comb begin
 000440 		case (state)
 000270 			WL: if (!ground) next = FALLL;
 000013 				else if (dig) next = DIGL;
~000084 				else if (bump_left) next = WR;
 000084 				else next = WL;
 000012 			WR: 
~000270 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
%000007 				else if (bump_right) next = WL;
%000007 				else next = WR;
~000270 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000270 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000270 			DIGL: next = ground ? DIGL : FALLL;
~000270 			DIGR: next = ground ? DIGR : FALLR;
%000007 			DEAD: next = DEAD;
        		endcase
            end
            
 000099     always @(posedge clk, posedge areset) begin
 000075 		if (areset) state <= WL;
 000075         else state <= next;
        	end
        	
 000088 	always @(posedge clk) begin
~000049 		if (state == FALLL || state == FALLR) begin
~000047 			if (fall_counter < 20)
 000047 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000039 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
