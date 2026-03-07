//      // verilator_coverage annotation
        module top_module (
 000061 	input clk,
%000001 	input areset,
%000002 	input bump_left,
%000002 	input bump_right,
%000003 	input ground,
%000002 	input dig,
%000003 	output walk_left,
%000001 	output walk_right,
%000002 	output aaah,
%000001 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000002 	reg [2:0] state;
%000002 	reg [2:0] next;
            
~000016     reg [4:0] fall_counter;
            
 000246     always_comb begin
 000246 		case (state)
~000140 			WL: if (!ground) next = FALLL;
%000003 				else if (dig) next = DIGL;
~000034 				else if (bump_left) next = WR;
 000034 				else next = WL;
 000016 			WR: 
~000140 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
~000013 				else if (bump_right) next = WL;
 000013 				else next = WR;
~000140 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000140 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000140 			DIGL: next = ground ? DIGL : FALLL;
~000140 			DIGR: next = ground ? DIGR : FALLR;
 000039 			DEAD: next = DEAD;
        		endcase
            end
            
 000062     always @(posedge clk, posedge areset) begin
~000059 		if (areset) state <= WL;
 000059         else state <= next;
        	end
        	
 000061 	always @(posedge clk) begin
~000035 		if (state == FALLL || state == FALLR) begin
~000032 			if (fall_counter < 20)
 000032 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000026 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
