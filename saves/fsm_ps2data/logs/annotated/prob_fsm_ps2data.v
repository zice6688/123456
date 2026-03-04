//      // verilator_coverage annotation
        module top_module (
 000069 	input clk,
~000013 	input [7:0] in,
%000003 	input reset,
~000018 	output [23:0] out_bytes,
 000018 	output done
        );
        	parameter BYTE1=0, BYTE2=1, BYTE3=2, DONE=3;
 000027 	reg [1:0] state;
 000028 	reg [1:0] next;
            
 000012     wire in3 = in[3];
            
 000277     always_comb begin
 000277 		case (state)
 000210 			BYTE1: next = in3 ? BYTE2 : BYTE1;
 000084 			BYTE2: next = BYTE3;
 000075 			BYTE3: next = DONE;
 000210 			DONE: next = in3 ? BYTE2 : BYTE1;
        		endcase
            end
            
 000069     always @(posedge clk) begin
~000066 		if (reset) state <= BYTE1;
 000066         else state <= next;
        	end
        		
        	assign done = (state==DONE);
        	
~000013 	reg [23:0] out_bytes_r;
 000069 	always @(posedge clk)
 000069 		out_bytes_r <= {out_bytes_r[15:0], in};
        	
        	// Implementations may vary: Allow user to do anything while the output doesn't have to be valid.	
 000052 	assign out_bytes = done ? out_bytes_r : 'x;		
        	
        endmodule
        
