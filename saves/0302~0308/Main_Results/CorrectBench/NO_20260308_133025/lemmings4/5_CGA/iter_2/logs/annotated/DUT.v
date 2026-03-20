//      // verilator_coverage annotation
        module top_module (
 000237 	input clk,
%000003 	input areset,
%000004 	input bump_left,
%000003 	input bump_right,
%000008 	input ground,
%000004 	input dig,
%000007 	output walk_left,
%000002 	output walk_right,
%000005 	output aaah,
%000002 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000005 	reg [2:0] state;
%000004 	reg [2:0] next;
            
~000021     reg [4:0] fall_counter;
            
 001185     always_comb begin
 001185 		case (state)
 000853 			WL: if (!ground) next = FALLL;
%000005 				else if (dig) next = DIGL;
~000014 				else if (bump_left) next = WR;
%000000 				else next = WL;
 000010 			WR: 
~000853 				if (!ground) next = FALLR;
%000001 				else if (dig) next = DIGR;
%000009 				else if (bump_right) next = WL;
%000000 				else next = WR;
~000853 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000853 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000853 			DIGL: next = ground ? DIGL : FALLL;
~000853 			DIGR: next = ground ? DIGR : FALLR;
 000745 			DEAD: next = DEAD;
        		endcase
            end
            
 000239     always @(posedge clk, posedge areset) begin
~000233 		if (areset) state <= WL;
 000233         else state <= next;
        	end
        	
 000237 	always @(posedge clk) begin
~000185 		if (state == FALLL || state == FALLR) begin
 000041 			if (fall_counter < 20)
 000041 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000185 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
