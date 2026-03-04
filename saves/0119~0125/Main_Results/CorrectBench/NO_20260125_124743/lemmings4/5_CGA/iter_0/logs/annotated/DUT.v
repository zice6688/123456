//      // verilator_coverage annotation
        module top_module (
 000090 	input clk,
%000001 	input areset,
%000004 	input bump_left,
%000003 	input bump_right,
%000006 	input ground,
%000001 	input dig,
%000002 	output walk_left,
%000003 	output walk_right,
%000002 	output aaah,
%000000 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000002 	reg [2:0] state;
%000003 	reg [2:0] next;
            
~000013     reg [4:0] fall_counter;
            
 000362     always_comb begin
 000362 		case (state)
~000208 			WL: if (!ground) next = FALLL;
%000000 				else if (dig) next = DIGL;
~000021 				else if (bump_left) next = WR;
 000021 				else next = WL;
 000032 			WR: 
~000208 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
~000022 				else if (bump_right) next = WL;
 000022 				else next = WR;
~000208 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000208 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000208 			DIGL: next = ground ? DIGL : FALLL;
~000208 			DIGR: next = ground ? DIGR : FALLR;
 000175 			DEAD: next = DEAD;
        		endcase
            end
            
 000091     always @(posedge clk, posedge areset) begin
~000089 		if (areset) state <= WL;
 000089         else state <= next;
        	end
        	
 000090 	always @(posedge clk) begin
~000058 		if (state == FALLL || state == FALLR) begin
~000026 			if (fall_counter < 20)
 000026 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000058 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
