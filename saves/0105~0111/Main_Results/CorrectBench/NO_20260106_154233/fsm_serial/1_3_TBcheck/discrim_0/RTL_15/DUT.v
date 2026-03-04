module top_module (
    input clk,
    input in,
    input reset,
    output reg done
);

    // State encoding
    typedef enum logic [3:0] {
        IDLE       = 4'b0000,
        START      = 4'b0001,
        DATA_0     = 4'b0010,
        DATA_1     = 4'b0011,
        DATA_2     = 4'b0100,
        DATA_3     = 4'b0101,
        DATA_4     = 4'b0110,
        DATA_5     = 4'b0111,
        DATA_6     = 4'b1000,
        DATA_7     = 4'b1001,
        STOP       = 4'b1010,
        ERROR      = 4'b1011
    } state_t;

    state_t state, next_state;
    reg [7:0] data_byte; // Storage for received data bits
    integer bit_count;

    // Synchronous state transition logic
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= IDLE;
        end else begin
            state <= next_state;
        end
    end

    // Next state logic and output
    always @(*) begin
        next_state = state; // Default stay in the same state
        done = 1'b0;        // Default done output is 0
        
        case (state)
            IDLE: begin
                if (in == 1'b0) begin // Detect start bit
                    next_state = START;
                end
            end
            
            START: begin
                if (in == 1'b0) begin
                    next_state = DATA_0;
                    bit_count = 0;
                end else begin
                    next_state = ERROR; // If start bit was not '0', go to error
                end
            end
            
            DATA_0, DATA_1, DATA_2, DATA_3, DATA_4, DATA_5, DATA_6, DATA_7: begin
                data_byte[bit_count] = in; // Capture the incoming data bit
                next_state = state + 1;    // Move to the next data state
                bit_count = bit_count + 1;
            end
            
            STOP: begin
                if (in == 1'b1) begin // Check for valid stop bit
                    done = 1'b1;
                    next_state = IDLE;
                end else begin
                    next_state = ERROR; // If stop bit was not '1', go to error
                end
            end
            
            ERROR: begin
                if (in == 1'b1) begin // Wait for a line idle (logic 1) to resync
                    next_state = IDLE;
                end
            end
        endcase
    end

endmodule
