//      // verilator_coverage annotation
        module top_module (
 000060 	input clk,
 000011 	input areset,
%000004 	input bump_left,
%000004 	input bump_right,
%000007 	input ground,
%000003 	input dig,
%000009 	output walk_left,
%000002 	output walk_right,
%000006 	output aaah,
%000002 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000006 	reg [2:0] state;
%000006 	reg [2:0] next;
            
~000015     reg [4:0] fall_counter;
            
 000242     always_comb begin
 000242 		case (state)
 000124 			WL: if (!ground) next = FALLL;
%000006 				else if (dig) next = DIGL;
~000069 				else if (bump_left) next = WR;
 000069 				else next = WL;
 000010 			WR: 
~000124 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
%000006 				else if (bump_right) next = WL;
%000006 				else next = WR;
~000124 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000124 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000124 			DIGL: next = ground ? DIGL : FALLL;
~000124 			DIGR: next = ground ? DIGR : FALLR;
%000006 			DEAD: next = DEAD;
        		endcase
            end
            
 000071     always @(posedge clk, posedge areset) begin
 000049 		if (areset) state <= WL;
 000049         else state <= next;
        	end
        	
 000060 	always @(posedge clk) begin
~000031 		if (state == FALLL || state == FALLR) begin
~000027 			if (fall_counter < 20)
 000027 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000031 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
