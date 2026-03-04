//      // verilator_coverage annotation
        module top_module (
 000149 	input clk,
%000001 	input areset,
%000004 	input bump_left,
%000004 	input bump_right,
~000010 	input ground,
%000001 	input dig,
%000003 	output walk_left,
%000000 	output walk_right,
%000003 	output aaah,
%000000 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000003 	reg [2:0] state;
%000003 	reg [2:0] next;
            
~000019     reg [4:0] fall_counter;
            
 000598     always_comb begin
 000598 		case (state)
 000464 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
~000010 				else if (bump_left) next = WR;
 000010 				else next = WL;
%000000 			WR: 
~000464 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
%000000 				else if (bump_right) next = WL;
%000000 				else next = WR;
~000464 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000464 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000464 			DIGL: next = ground ? DIGL : FALLL;
~000464 			DIGR: next = ground ? DIGR : FALLR;
 000411 			DEAD: next = DEAD;
        		endcase
            end
            
 000150     always @(posedge clk, posedge areset) begin
~000147 		if (areset) state <= WL;
 000147         else state <= next;
        	end
        	
 000149 	always @(posedge clk) begin
~000109 		if (state == FALLL || state == FALLR) begin
~000038 			if (fall_counter < 20)
 000038 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000109 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
