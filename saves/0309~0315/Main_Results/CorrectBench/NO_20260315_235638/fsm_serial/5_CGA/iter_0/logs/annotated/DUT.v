//      // verilator_coverage annotation
        module top_module (
 000128 	input clk,
 000040 	input in,
%000005 	input reset,
%000004 	output done
        );
        	parameter B0=0, B1=1, B2=2, B3=3, B4=4, B5=5, B6=6, B7=7, START=8, STOP=9, DONE=10, ERR=11;
~000037 	reg [3:0] state;
~000043 	reg [3:0] next;
            
 000513     always_comb begin
 000513 		case (state)
 000267 			START: next = in ? START : B0;	// start bit is 0
 000042 			B0: next = B1;
 000040 			B1: next = B2;
 000040 			B2: next = B3;
 000040 			B3: next = B4;
 000036 			B4: next = B5;
 000036 			B5: next = B6;
 000036 			B6: next = B7;
 000032 			B7: next = STOP;
 000267 			STOP: next = in ? DONE : ERR;  // stop bit is 1. Idle state is 1.
~000267 			DONE: next = in ? START : B0;
~000267 			ERR: next = in ? START : ERR;
        		endcase
            end
            
 000128     always @(posedge clk) begin
 000103 		if (reset) state <= START;
 000103         else state <= next;
        	end
        		
        	assign done = (state==DONE);
        	
        endmodule
        
