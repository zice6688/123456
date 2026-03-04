module top_module (
    input clk,
    input in,
    input reset,
    output reg done
);

    typedef enum reg [2:0] {
        IDLE,       // Waiting for start bit
        START,      // Checking start bit
        DATA,       // Receiving data bits
        STOP,       // Checking stop bit
        WAITSTOP    // Wait for a valid stop bit
    } state_t;
    
    state_t state, next_state;
    reg [2:0] bit_count;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= IDLE;
            bit_count <= 3'd0;
            done <= 1'b0;
        end
        else begin
            state <= next_state;
            if (state == DATA) 
                bit_count <= bit_count + 1;
            else 
                bit_count <= 3'd0;
        end
    end

    always @(*) begin
        next_state = state;
        done = 1'b0;
        case (state)
            IDLE: begin
                if (in == 1'b0)  // Start bit detected
                    next_state = START;
            end
            START: begin
                next_state = DATA;
            end
            DATA: begin
                if (bit_count == 3'd7)
                    if (in == 1'b1)
                        next_state = STOP;
                    else
                        next_state = WAITSTOP;
            end
            STOP: begin
                done = 1'b1;
                if (in == 1'b0)
                    next_state = START;
                else
                    next_state = IDLE;
            end
            WAITSTOP: begin
                if (in == 1'b1)
                    next_state = IDLE;
            end
        endcase
    end

endmodule
