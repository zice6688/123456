module top_module (
    input clk,
    input in,
    input reset,
    output reg done
);

    // State encoding
    typedef enum logic[2:0] {
        IDLE      = 3'b000,
        START_BIT = 3'b001,
        DATA_BITS = 3'b010,
        STOP_BIT  = 3'b011,
        ERROR     = 3'b100
    } state_t;
    
    state_t state, next_state;

    // Count for data bits
    reg [2:0] bit_count;
    
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state     <= IDLE;
            bit_count <= 3'd0;
            done      <= 1'b0;
        end else begin
            state <= next_state;
            
            if (state == DATA_BITS) begin
                bit_count <= bit_count + 3'd1;
            end else begin
                bit_count <= 3'd0;
            end
            
            if (state == STOP_BIT && in == 1'b1) begin
                done <= 1'b1;
            end else begin
                done <= 1'b0;
            end
        end
    end

    always @(*) begin
        case (state)
            IDLE: begin
                if (in == 1'b0)  // Detect start bit (0)
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
                if (in == 1'b1)  // Check for stop bit (1)
                    next_state = IDLE;
                else
                    next_state = ERROR;
            end

            ERROR: begin
                if (in == 1'b1)  // Wait for idle state (stop bit)
                    next_state = IDLE;
                else
                    next_state = ERROR;
            end

            default: next_state = IDLE;
        endcase
    end

endmodule
