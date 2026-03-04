module top_module (
    input clk,
    input in,
    input reset,
    output reg done
);

    // State encoding
    typedef enum logic [2:0] {
        IDLE      = 3'd0,
        START_BIT = 3'd1,
        DATA_BITS = 3'd2,
        STOP_BIT  = 3'd3,
        DONE      = 3'd4
    } state_t;
    
    state_t state, next_state;
    reg [2:0] bit_count;
    
    always_ff @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= IDLE;
            bit_count <= 3'd0;
            done <= 1'b0;
        end else begin
            state <= next_state;
        end
    end

    always_comb begin
        next_state = state; // Default to hold state
        done = 1'b0;        // Default done signal

        case (state)
            IDLE: begin
                if (~in) // Detect start bit (0)
                    next_state = START_BIT;
            end
            
            START_BIT: begin
                next_state = DATA_BITS;
                bit_count = 3'd0;
            end
            
            DATA_BITS: begin
                if (bit_count == 3'd7)
                    next_state = STOP_BIT;
                else
                    bit_count = bit_count + 1;
            end
            
            STOP_BIT: begin
                if (in) // Detect stop bit (1)
                    next_state = DONE;
                else
                    next_state = IDLE; // Go back to IDLE if stop bit not detected
            end
            
            DONE: begin
                done = 1'b1; // Signal the reception is done
                if (~in) // Look for the next start bit
                    next_state = START_BIT;
                else
                    next_state = IDLE;
            end
            
            default: begin
                next_state = IDLE; // Default state
            end
        endcase
    end
endmodule
