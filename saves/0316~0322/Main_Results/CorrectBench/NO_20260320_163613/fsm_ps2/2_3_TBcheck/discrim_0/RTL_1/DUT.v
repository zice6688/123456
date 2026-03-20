module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output done
);

    // FSM State Definitions
    typedef enum reg [1:0] {
        IDLE = 2'b00,   // Waiting for the first byte with in[3] = 1
        BYTE_1 = 2'b01, // First byte received, waiting for second byte
        BYTE_2 = 2'b10  // Second byte received, waiting for third byte
    } state_t;

    reg [1:0] state, next_state;
    reg done_reg;

    // State Register
    always @(posedge clk) begin
        if (reset)
            state <= IDLE;
        else
            state <= next_state;
    end

    // Next State Logic and Output Logic
    always @(*) begin
        // Default values
        next_state = state;
        done_reg = 1'b0;

        case (state)
            IDLE: begin
                if (in[3] == 1'b1)
                    next_state = BYTE_1;
            end
            BYTE_1: begin
                next_state = BYTE_2;
            end
            BYTE_2: begin
                done_reg = 1'b1; // Signal done on third byte
                next_state = IDLE;
            end
            default: next_state = IDLE;
        endcase
    end

    assign done = done_reg;

endmodule
