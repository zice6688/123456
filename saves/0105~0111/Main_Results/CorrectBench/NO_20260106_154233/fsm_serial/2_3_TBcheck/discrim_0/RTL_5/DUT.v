module top_module (
    input clk,
    input in,
    input reset,
    output reg done
);

    // State encoding
    typedef enum logic [2:0] {
        IDLE = 3'b000,
        START = 3'b001,
        DATA = 3'b010,
        STOP = 3'b011,
        ERROR = 3'b100
    } state_t;

    state_t current_state, next_state;
    reg [2:0] bit_count;
    reg [7:0] data_byte;

    // State transition logic
    always_ff @(posedge clk or posedge reset) begin
        if (reset) begin
            current_state <= IDLE;
            bit_count <= 3'd0;
            done <= 1'b0;
        end
        else begin
            current_state <= next_state;
        end
    end

    // Next state logic and output logic
    always_comb begin
        next_state = current_state; // Default to remain in the current state
        done = 1'b0;  // Default done output
        case (current_state)
            IDLE: begin
                if (in == 1'b0) begin
                    next_state = START;
                end
            end
            START: begin
                if (in == 1'b0) begin
                    next_state = DATA;
                    bit_count = 3'd0;
                end
                else begin
                    next_state = IDLE;  // False start, back to IDLE
                end
            end
            DATA: begin
                data_byte[bit_count] = in;
                if (bit_count == 3'd7) begin
                    next_state = STOP;
                end
                bit_count = bit_count + 3'd1;
            end
            STOP: begin
                if (in == 1'b1) begin
                    done = 1'b1;  // Byte received successfully
                    next_state = IDLE;
                end
                else begin
                    next_state = ERROR;  // Stop bit not correct
                end
            end
            ERROR: begin
                if (in == 1'b1) begin
                    next_state = IDLE; // Wait for line to go idle
                end
            end
        endcase
    end

endmodule
