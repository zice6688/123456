module top_module (
    input clk,
    input in,
    input reset,
    output done
);

    // State definitions
    typedef enum logic [2:0] {
        IDLE = 3'b000,
        START = 3'b001,
        DATA = 3'b010,
        STOP = 3'b011,
        ERROR = 3'b100
    } state_t;

    state_t current_state, next_state;
    reg [2:0] bit_count;
    reg done_reg;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            current_state <= IDLE;
            bit_count <= 3'd0;
            done_reg <= 1'b0;
        end else begin
            current_state <= next_state;
            done_reg <= (current_state == STOP);
            if (current_state == DATA)
                bit_count <= bit_count + 3'd1;
            else
                bit_count <= 3'd0;
        end
    end

    always @* begin
        case (current_state)
            IDLE: begin
                if (in == 1'b0) // Start bit detected
                    next_state = START;
                else
                    next_state = IDLE;
            end
            START: begin
                next_state = DATA;
            end
            DATA: begin
                if (bit_count == 3'd7)
                    next_state = STOP;
                else
                    next_state = DATA;
            end
            STOP: begin
                if (in == 1'b1) // Correct stop bit
                    next_state = IDLE;
                else
                    next_state = ERROR;
            end
            ERROR: begin
                if (in == 1'b1) // Wait for idle to find stop bit
                    next_state = IDLE;
                else
                    next_state = ERROR;
            end
            default: next_state = IDLE;
        endcase
    end

    assign done = done_reg;

endmodule
