module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output done
);

    typedef enum reg [1:0] {
        WAIT_FOR_FIRST_BYTE = 2'b00,
        SECOND_BYTE = 2'b01,
        THIRD_BYTE = 2'b10
    } state_type;

    state_type state, next_state;
    reg done_reg;

    always @(posedge clk) begin
        if (reset) begin
            state <= WAIT_FOR_FIRST_BYTE;
            done_reg <= 0;
        end else begin
            state <= next_state;
            done_reg <= (state == THIRD_BYTE);
        end
    end

    always @(*) begin
        next_state = state; // Default to stay in the same state
        case (state)
            WAIT_FOR_FIRST_BYTE: begin
                if (in[3] == 1'b1) begin
                    next_state = SECOND_BYTE;
                end
            end
            SECOND_BYTE: begin
                next_state = THIRD_BYTE;
            end
            THIRD_BYTE: begin
                next_state = WAIT_FOR_FIRST_BYTE;
            end
        endcase
    end

    assign done = done_reg;

endmodule
