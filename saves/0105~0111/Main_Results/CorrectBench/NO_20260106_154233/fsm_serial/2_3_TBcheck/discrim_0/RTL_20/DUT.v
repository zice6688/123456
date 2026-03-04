module top_module (
    input clk,
    input in,
    input reset,
    output reg done
);

    // Define the states
    typedef enum reg [2:0] {
        IDLE = 3'b000,
        START = 3'b001,
        DATA = 3'b010,
        STOP = 3'b011,
        ERROR = 3'b100
    } state_t;

    // State registers
    state_t current_state, next_state;

    // Bit counter for data bits
    reg [2:0] bit_counter;

    // State transition
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            current_state <= IDLE;
            bit_counter <= 3'b000;
        end else begin
            current_state <= next_state;
        end
    end

    // Next state logic
    always @(*) begin
        // Default state
        next_state = current_state;
        done = 1'b0;
        
        case (current_state)
            IDLE: begin
                if (in == 1'b0) begin // Start bit detected
                    next_state = START;
                end
            end
            START: begin
                next_state = DATA;
                bit_counter = 3'b000;
            end
            DATA: begin
                if (bit_counter == 3'b111) begin
                    next_state = STOP;
                end else begin
                    next_state = DATA;
                end
                bit_counter = bit_counter + 1;
            end
            STOP: begin
                if (in == 1'b1) begin // Correct stop bit
                    done = 1'b1;
                    next_state = IDLE;
                end else begin
                    next_state = ERROR;
                end
            end
            ERROR: begin
                if (in == 1'b1) begin // Wait for line to be idle
                    next_state = IDLE;
                end else begin
                    next_state = ERROR;
                end
            end
            default: begin
                next_state = IDLE;
            end
        endcase
    end

endmodule
