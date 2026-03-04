module top_module (
	input clk,
	input [7:0] in,
	input reset,
	output reg [23:0] out_bytes,
	output reg done
);

    // State encoding
    typedef enum reg [1:0] {
        IDLE  = 2'b00,
        BYTE1 = 2'b01,
        BYTE2 = 2'b10,
        BYTE3 = 2'b11
    } state_t;
    
    state_t state, next_state;
    reg [23:0] message;
    
    // State transition
    always @(posedge clk) begin
        if (reset)
            state <= IDLE;
        else
            state <= next_state;
    end
    
    // Next state logic
    always @(*) begin
        case (state)
            IDLE:  next_state = (in[3] == 1) ? BYTE1 : IDLE;
            BYTE1: next_state = BYTE2;
            BYTE2: next_state = BYTE3;
            BYTE3: next_state = IDLE;
            default: next_state = IDLE;
        endcase
    end
    
    // Output logic and message capture
    always @(posedge clk) begin
        if (reset) begin
            message <= 24'b0;
            out_bytes <= 24'b0;
            done <= 0;
        end
        else begin
            done <= 0;
            case (state)
                BYTE1: message[23:16] <= in;
                BYTE2: message[15:8] <= in;
                BYTE3: begin
                    message[7:0] <= in;
                    out_bytes <= message;
                    done <= 1;
                end
            endcase
        end
    end

endmodule
