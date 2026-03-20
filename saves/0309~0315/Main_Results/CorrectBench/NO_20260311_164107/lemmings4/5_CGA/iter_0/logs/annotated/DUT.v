//      // verilator_coverage annotation
        module top_module (
 000132 	input clk,
%000001 	input areset,
%000003 	input bump_left,
%000003 	input bump_right,
~000010 	input ground,
%000001 	input dig,
%000002 	output walk_left,
%000004 	output walk_right,
%000003 	output aaah,
%000000 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000003 	reg [2:0] state;
%000004 	reg [2:0] next;
            
~000014     reg [4:0] fall_counter;
            
 000530     always_comb begin
 000530 		case (state)
~000388 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
~000032 				else if (bump_left) next = WR;
 000032 				else next = WL;
 000040 			WR: 
~000388 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
~000027 				else if (bump_right) next = WL;
 000027 				else next = WR;
~000388 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000388 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000388 			DIGL: next = ground ? DIGL : FALLL;
~000388 			DIGR: next = ground ? DIGR : FALLR;
 000335 			DEAD: next = DEAD;
        		endcase
            end
            
 000133     always @(posedge clk, posedge areset) begin
~000131 		if (areset) state <= WL;
 000131         else state <= next;
        	end
        	
 000132 	always @(posedge clk) begin
~000103 		if (state == FALLL || state == FALLR) begin
~000027 			if (fall_counter < 20)
 000027 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000103 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
