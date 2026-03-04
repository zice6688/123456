module top_module (
    input clk,
    input in,
    input reset,
    output done
);

    typedef enum reg [2:0] {
        IDLE = 3'b000,
        START_BIT = 3'b001,
        DATA_BITS = 3'b010,
        STOP_BIT = 3'b011,
        DONE = 3'b100
    } state_t;
    
    reg [2:0] state, next_state;
    reg [2:0] bit_count;
    reg [7:0] data_byte;
    reg done_reg;
    
    assign done = done_reg;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= IDLE;
            bit_count <= 3'b000;
            data_byte <= 8'b00000000;
            done_reg <= 1'b0;
        end else begin
            state <= next_state;
            if (state == DATA_BITS) begin
                data_byte <= {in, data_byte[7:1]}; // Shift in bits (LSB first)
            end
            if (state == DONE) begin
                done_reg <= 1'b1;
            end else begin
                done_reg <= 1'b0;
            end
        end
    end

    always @(*) begin
        next_state = state; // Default is to remain in the same state
        case (state)
            IDLE: begin
                if (in == 0) begin
                    next_state = START_BIT;
                end
            end
            START_BIT: begin
                next_state = DATA_BITS; // Start bit detected, move to data bits
                bit_count = 3'b000; // Reset bit count for data bits
            end
            DATA_BITS: begin
                if (bit_count == 3'b111) begin
                    next_state = STOP_BIT; // All data bits received, move to stop bit
                end else begin
                    bit_count = bit_count + 3'b001; // Increment bit counter
                end
            end
            STOP_BIT: begin
                if (in == 1) begin
                    next_state = DONE; // Stop bit correct
                end else begin
                    next_state = IDLE; // Wait for a stop bit
                end
            end
            DONE: begin
                next_state = IDLE; // Return to idle after a successful byte capture
            end
            default: next_state = IDLE;
        endcase
    end

endmodule
