//      // verilator_coverage annotation
        module top_module (
 000082 	input clk,
%000002 	input areset,
%000002 	input bump_left,
%000002 	input bump_right,
%000003 	input ground,
%000003 	input dig,
%000004 	output walk_left,
%000001 	output walk_right,
%000003 	output aaah,
%000001 	output digging
        );
        	parameter WL=0, WR=1, FALLL=2, FALLR=3, DIGL=4, DIGR=5, DEAD=6;
%000003 	reg [2:0] state;
%000002 	reg [2:0] next;
            
~000025     reg [4:0] fall_counter;
            
 000410     always_comb begin
 000410 		case (state)
 000280 			WL: if (!ground) next = FALLL;
%000004 				else if (dig) next = DIGL;
~000042 				else if (bump_left) next = WR;
 000042 				else next = WL;
 000020 			WR: 
~000280 				if (!ground) next = FALLR;
%000000 				else if (dig) next = DIGR;
~000016 				else if (bump_right) next = WL;
 000016 				else next = WR;
~000280 			FALLL: next = ground ? (fall_counter >= 20 ? DEAD : WL) : FALLL;
~000280 			FALLR: next = ground ? (fall_counter >= 20 ? DEAD : WR) : FALLR;
~000280 			DIGL: next = ground ? DIGL : FALLL;
~000280 			DIGR: next = ground ? DIGR : FALLR;
 000050 			DEAD: next = DEAD;
        		endcase
            end
            
 000083     always @(posedge clk, posedge areset) begin
~000078 		if (areset) state <= WL;
 000078         else state <= next;
        	end
        	
 000082 	always @(posedge clk) begin
~000053 		if (state == FALLL || state == FALLR) begin
~000050 			if (fall_counter < 20)
 000050 				fall_counter <= fall_counter + 1'b1;
        		end
        		else
 000029 			fall_counter <= 0;
        	end
        		
        	assign walk_left = (state==WL);
        	assign walk_right = (state==WR);
        	assign aaah = (state == FALLL) || (state == FALLR);
        	assign digging = (state == DIGL) || (state == DIGR);
        	
        endmodule
        
