module top_module (
    input clk,
    input in,
    input reset,
    output done
);

    // State definitions
    typedef enum reg [2:0] {
        IDLE = 3'b000,     // Waiting for start bit
        START = 3'b001,    // Start bit detected
        DATA = 3'b010,     // Receiving data bits
        STOP = 3'b011,     // Expecting stop bit
        DONE = 3'b100,     // Byte successfully received
        ERROR = 3'b101    // Stop bit error
    } state_t;

    state_t state, next_state;
    reg [2:0] bit_count; // To count the number of data bits received
    reg done_reg;

    // Sequential Logic: State Transition and Output Logic
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= IDLE;
            bit_count <= 0;
            done_reg <= 0;
        end else begin
            state <= next_state;
            done_reg <= (next_state == DONE);
        end
    end

    // Combinational Logic: Next State Logic
    always @(*) begin
        next_state = state;
        case (state)
            IDLE: begin
                if (in == 0) // Detect start bit
                    next_state = START;
            end

            START: begin
                next_state = DATA;
                bit_count = 0;
            end

            DATA: begin
                if (bit_count == 7)
                    next_state = STOP;
                else
                    bit_count = bit_count + 1;
            end

            STOP: begin
                if (in == 1)
                    next_state = DONE;
                else
                    next_state = ERROR;
            end

            DONE: begin
                if (in == 1)
                    next_state = IDLE;
            end

            ERROR: begin
                if (in == 1) // Wait for a stop bit to return to IDLE
                    next_state = IDLE;
            end
        endcase
    end

    assign done = done_reg;

endmodule
