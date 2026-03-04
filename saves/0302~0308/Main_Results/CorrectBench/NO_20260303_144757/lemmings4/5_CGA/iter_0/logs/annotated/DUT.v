//      // verilator_coverage annotation
        module top_module (
 000145 	input clk,
%000002 	input areset,
%000006 	input bump_left,
%000006 	input bump_right,
%000008 	input ground,
%000001 	input dig,
%000008 	output walk_left,
%000001 	output walk_right,
%000006 	output aaah,
%000004 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000006 	reg [2:0] state;
%000006 	reg [2:0] next;
            
~000030     reg [4:0] fall_counter;
            
 000582     always_comb begin
 000582 		case (state)
~000368 			WL: if (!ground) next = FALLL;
 000020 				else if (dig) next = DIGL;
~000031 				else if (bump_left) next = WR;
 000031 				else next = WL;
 000012 			WR: 
~000368 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
%000009 				else if (bump_right) next = WL;
%000009 				else next = WR;
~000368 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000368 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
 000368 			DIGL: next = ground ? DIGL : FALLL;
~000368 			DIGR: next = ground ? DIGR : FALLR;
 000118 			DEAD: next = DEAD;
        		endcase
            end
            
 000147     always @(posedge clk, posedge areset) begin
~000143 		if (areset) state <= WL;
 000143         else state <= next;
        	end
        	
 000145 	always @(posedge clk) begin
~000079 		if (state == FALLL || state == FALLR) begin
~000060 			if (fall_counter < 20)
 000060 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000079 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
