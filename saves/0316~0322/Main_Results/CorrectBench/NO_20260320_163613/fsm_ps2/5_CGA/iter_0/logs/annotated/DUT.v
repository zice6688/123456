//      // verilator_coverage annotation
        module top_module (
 000086 	input clk,
~000011 	input [7:0] in,
%000007 	input reset,
 000011 	output done
        );
        	parameter BYTE1=0, BYTE2=1, BYTE3=2, DONE=3;
 000019 	reg [1:0] state;
 000022 	reg [1:0] next;
            
 000011     wire in3 = in[3];
            
 000345     always_comb begin
 000345 		case (state)
 000301 			BYTE1: next = in3 ? BYTE2 : BYTE1;
 000044 			BYTE2: next = BYTE3;
 000044 			BYTE3: next = DONE;
~000301 			DONE: next = in3 ? BYTE2 : BYTE1;
        		endcase
            end
            
 000086     always @(posedge clk) begin
~000079 		if (reset) state <= BYTE1;
 000079         else state <= next;
        	end
        		
        	assign done = (state==DONE);
        	
        endmodule
        
