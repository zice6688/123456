module top_module (
    input clk,
    input in,
    input reset,
    output done
);

    // State encoding
    typedef enum reg [2:0] {
        IDLE     = 3'b000,
        START    = 3'b001,
        DATA     = 3'b010,
        STOP     = 3'b011,
        ERROR    = 3'b100
    } state_t;

    reg [2:0] state, next_state;
    reg [3:0] bit_count; // 4 bits to count up to 8 data bits
    reg done_reg;

    assign done = done_reg;

    // State transition logic
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= IDLE;
            bit_count <= 4'd0;
            done_reg <= 1'b0;
        end else begin
            state <= next_state;
        end
    end

    // Next state logic
    always @(*) begin
        next_state = state;
        done_reg = 1'b0; // Default done signal to 0

        case (state)
            IDLE: begin
                if (in == 1'b0) begin // Look for start bit (0)
                    next_state = START;
                end
            end
            START: begin
                next_state = DATA; // Move to DATA state
                bit_count = 4'd0;  // Reset bit counter
            end
            DATA: begin
                if (bit_count == 4'd8) begin
                    next_state = (in == 1'b1) ? STOP : ERROR; // Expect stop bit (1)
                end else begin
                    bit_count = bit_count + 1;
                end
            end
            STOP: begin
                done_reg = 1'b1;   // Byte received successfully
                next_state = IDLE; // Return to IDLE state
            end
            ERROR: begin
                if (in == 1'b1) begin // Wait for the stop bit (1) to complete
                    next_state = IDLE;
                end
            end
            default: next_state = IDLE;
        endcase
    end

endmodule
