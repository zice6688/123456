module top_module (
    input clk,
    input in,
    input reset,
    output done
);

    // State encoding
    typedef enum reg [2:0] {
        IDLE = 3'b000,
        START = 3'b001,
        DATA = 3'b010,
        STOP = 3'b011,
        ERROR = 3'b100
    } state_t;

    state_t current_state, next_state;
    reg [3:0] bit_count;
    reg done_reg;

    // Output logic
    assign done = done_reg;

    // State transition logic
    always @(posedge clk) begin
        if (reset) begin
            current_state <= IDLE;
            bit_count <= 0;
            done_reg <= 0;
        end else begin
            current_state <= next_state;
            if (current_state == DATA) bit_count <= bit_count + 1;
            else bit_count <= 0;
            done_reg <= (next_state == STOP);
        end
    end

    // Next state logic
    always @* begin
        next_state = current_state; // Default: stay in the same state
        case (current_state)
            IDLE: 
                if (!in) next_state = START; // Detect start bit
            START: 
                next_state = DATA; // Move to DATA state
            DATA: 
                if (bit_count == 8) 
                    next_state = (in) ? STOP : ERROR; // Check stop bit after 8 data bits
            STOP: 
                if (!in) next_state = START; // Prepare for a new byte
                else next_state = IDLE; // Stay idle while the line is high
            ERROR: 
                if (in) next_state = IDLE; // Wait to return to idle
        endcase
    end

endmodule
