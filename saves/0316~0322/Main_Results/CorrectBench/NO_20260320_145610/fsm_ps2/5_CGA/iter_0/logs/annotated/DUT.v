//      // verilator_coverage annotation
        module top_module (
 000053 	input clk,
~000012 	input [7:0] in,
%000002 	input reset,
%000000 	output done
        );
        	parameter BYTE1=0, BYTE2=1, BYTE3=2, DONE=3;
%000000 	reg [1:0] state;
%000000 	reg [1:0] next;
            
%000000     wire in3 = in[3];
            
 000213     always_comb begin
 000213 		case (state)
~000213 			BYTE1: next = in3 ? BYTE2 : BYTE1;
%000000 			BYTE2: next = BYTE3;
%000000 			BYTE3: next = DONE;
~000213 			DONE: next = in3 ? BYTE2 : BYTE1;
        		endcase
            end
            
 000053     always @(posedge clk) begin
~000051 		if (reset) state <= BYTE1;
 000051         else state <= next;
        	end
        		
        	assign done = (state==DONE);
        	
        endmodule
        
