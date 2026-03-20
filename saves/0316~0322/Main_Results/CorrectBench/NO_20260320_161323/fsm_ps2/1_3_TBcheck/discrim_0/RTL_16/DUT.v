module top_module (
	input clk,
	input [7:0] in,
	input reset,
	output reg done
);

    // State Encoding
    typedef enum reg [1:0] {
        WAIT_FOR_FIRST_BYTE = 2'b00,
        BYTE_ONE_RECEIVED   = 2'b01,
        BYTE_TWO_RECEIVED   = 2'b10
    } state_t;

    state_t state, next_state;

    // State Transition Logic
    always @(posedge clk) begin
        if (reset) begin
            state <= WAIT_FOR_FIRST_BYTE;
        end else begin
            state <= next_state;
        end
    end

    // Next State Logic
    always @(*) begin
        next_state = state; // default to hold state
        done = 0;
        case (state)
            WAIT_FOR_FIRST_BYTE: begin
                if (in[3] == 1) begin
                    next_state = BYTE_ONE_RECEIVED;
                end
            end
            BYTE_ONE_RECEIVED: begin
                next_state = BYTE_TWO_RECEIVED;
            end
            BYTE_TWO_RECEIVED: begin
                done = 1;
                next_state = WAIT_FOR_FIRST_BYTE;
            end
        endcase
    end

endmodule
