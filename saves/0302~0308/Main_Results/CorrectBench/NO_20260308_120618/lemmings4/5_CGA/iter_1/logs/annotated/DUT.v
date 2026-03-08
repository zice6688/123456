//      // verilator_coverage annotation
        module top_module (
 000082 	input clk,
 000012 	input areset,
%000004 	input bump_left,
%000004 	input bump_right,
%000008 	input ground,
%000004 	input dig,
 000010 	output walk_left,
%000002 	output walk_right,
%000007 	output aaah,
%000003 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000007 	reg [2:0] state;
%000007 	reg [2:0] next;
            
~000020     reg [4:0] fall_counter;
            
 000410     always_comb begin
 000410 		case (state)
 000218 			WL: if (!ground) next = FALLL;
%000009 				else if (dig) next = DIGL;
~000093 				else if (bump_left) next = WR;
 000093 				else next = WL;
 000012 			WR: 
~000218 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
%000007 				else if (bump_right) next = WL;
%000007 				else next = WR;
~000218 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000218 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000218 			DIGL: next = ground ? DIGL : FALLL;
~000218 			DIGR: next = ground ? DIGR : FALLR;
%000007 			DEAD: next = DEAD;
        		endcase
            end
            
 000093     always @(posedge clk, posedge areset) begin
 000069 		if (areset) state <= WL;
 000069         else state <= next;
        	end
        	
 000082 	always @(posedge clk) begin
~000043 		if (state == FALLL || state == FALLR) begin
~000037 			if (fall_counter < 20)
 000037 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000043 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
