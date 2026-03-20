//      // verilator_coverage annotation
        module top_module (
 000055 	input clk,
~000012 	input [7:0] in,
%000003 	input reset,
%000000 	output done
        );
        	parameter BYTE1=0, BYTE2=1, BYTE3=2, DONE=3;
%000000 	reg [1:0] state;
%000000 	reg [1:0] next;
            
%000000     wire in3 = in[3];
            
 000221     always_comb begin
 000221 		case (state)
~000221 			BYTE1: next = in3 ? BYTE2 : BYTE1;
%000000 			BYTE2: next = BYTE3;
%000000 			BYTE3: next = DONE;
~000221 			DONE: next = in3 ? BYTE2 : BYTE1;
        		endcase
            end
            
 000055     always @(posedge clk) begin
~000052 		if (reset) state <= BYTE1;
 000052         else state <= next;
        	end
        		
        	assign done = (state==DONE);
        	
        endmodule
        
