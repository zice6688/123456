module top_module (
    input clk,
    input in,
    input reset,
    output reg done
);

    typedef enum logic [2:0] {
        IDLE = 3'b000,
        START_BIT = 3'b001,
        DATA_BITS = 3'b010,
        STOP_BIT = 3'b011,
        WAIT_STOP = 3'b100
    } state_t;
    
    state_t state, next_state;
    reg [3:0] bit_counter;  // To count the 8 data bits.
    
    always_ff @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= IDLE;
            bit_counter <= 4'b0;
            done <= 1'b0;
        end else begin
            state <= next_state;
        end
    end
    
    always_comb begin
        next_state = state;
        done = 1'b0;
        
        case (state)
            IDLE: begin
                if (in == 1'b0)  // Detected start bit
                    next_state = START_BIT;
            end
            
            START_BIT: begin
                next_state = DATA_BITS;
            end
            
            DATA_BITS: begin
                if (bit_counter < 8) begin
                    next_state = DATA_BITS;
                end else begin
                    next_state = STOP_BIT;
                end
            end
            
            STOP_BIT: begin
                if (in == 1'b1) begin  // Correct stop bit
                    done = 1'b1;       // Byte received correctly
                    next_state = IDLE;
                end else begin
                    next_state = WAIT_STOP;
                end
            end
            
            WAIT_STOP: begin
                if (in == 1'b1) begin  // Waiting for idle
                    next_state = IDLE;
                end
            end
            
            default: begin
                next_state = IDLE;
            end
        endcase
    end
    
    always_ff @(posedge clk) begin
        if (state == DATA_BITS) begin
            bit_counter <= bit_counter + 1;
        end else if (state != DATA_BITS) begin
            bit_counter <= 4'b0;
        end
    end

endmodule
