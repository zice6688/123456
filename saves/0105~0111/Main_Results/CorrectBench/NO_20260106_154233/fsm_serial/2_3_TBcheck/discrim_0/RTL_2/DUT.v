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
        CHECK_STOP  = 3'b100
    } state_t;
    
    state_t state, next_state;
    reg [2:0] bit_counter;
    reg done_reg;

    // Next state logic
    always_comb begin
        next_state = state; // Default to current state
        done_reg = 1'b0; // Default output
        case (state)
            IDLE: begin
                if (in == 1'b0) // Detecting start bit
                    next_state = START_BIT;
            end
            START_BIT: begin
                next_state = DATA_BITS;
                bit_counter = 3'd0; // Reset bit counter
            end
            DATA_BITS: begin
                if (bit_counter == 3'd7)
                    next_state = STOP_BIT;
                else
                    next_state = DATA_BITS;
            end
            STOP_BIT: begin
                next_state = CHECK_STOP;
            end
            CHECK_STOP: begin
                if (in == 1'b1) begin
                    done_reg = 1'b1; // Byte correctly received
                    next_state = IDLE;
                end else begin
                    next_state = IDLE; // Go back to IDLE and try to find new byte
                end
            end
            default: begin
                next_state = IDLE; // In case of unexpected state
            end
        endcase
    end
    
    // Sequential logic for state transitions and output
    always_ff @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= IDLE;
            bit_counter <= 3'd0;
        end else begin
            state <= next_state;
            if (state == DATA_BITS)
                bit_counter <= bit_counter + 1;
        end
    end

    // Output assignment
    assign done = done_reg;

endmodule
