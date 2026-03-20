module top_module (
    input clk,
    input in,
    input reset,
    output done
);

    // State encoding
    typedef enum logic [2:0] {
        IDLE        = 3'b000,
        START_BIT   = 3'b001,
        DATA_BITS   = 3'b010,
        STOP_BIT    = 3'b011,
        ERROR       = 3'b100
    } state_t;

    state_t current_state, next_state;
    reg [2:0] bit_count; // To count 8 data bits
    reg done_reg;

    // State transition logic
    always @(posedge clk) begin
        if (reset)
            current_state <= IDLE;
        else
            current_state <= next_state;
    end

    // Next state logic
    always @(*) begin
        case (current_state)
            IDLE: begin
                if (in == 1'b0)
                    next_state = START_BIT;
                else
                    next_state = IDLE;
            end

            START_BIT: begin
                next_state = DATA_BITS;
            end

            DATA_BITS: begin
                if (bit_count == 3'd7)
                    next_state = STOP_BIT;
                else
                    next_state = DATA_BITS;
            end

            STOP_BIT: begin
                if (in == 1'b1)
                    next_state = IDLE;
                else
                    next_state = ERROR;
            end

            ERROR: begin
                if (in == 1'b1)
                    next_state = IDLE;
                else
                    next_state = ERROR;
            end

            default: next_state = IDLE;
        endcase
    end

    // Output logic
    always @(posedge clk) begin
        if (reset) begin
            bit_count <= 3'b0;
            done_reg <= 1'b0;
        end else begin
            done_reg <= 1'b0;
            case (current_state)
                DATA_BITS: begin
                    bit_count <= bit_count + 1'b1;
                end
                STOP_BIT: begin
                    if (in == 1'b1)
                        done_reg <= 1'b1;
                    bit_count <= 3'b0;
                end
                default: begin
                    bit_count <= 3'b0;
                end
            endcase
        end
    end

    assign done = done_reg;

endmodule
