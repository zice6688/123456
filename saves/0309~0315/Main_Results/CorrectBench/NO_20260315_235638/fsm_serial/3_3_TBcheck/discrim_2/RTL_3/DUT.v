module top_module (
    input clk,
    input in,
    input reset,
    output reg done
);

    // State Encoding
    typedef enum logic [2:0] {
        IDLE    = 3'b000,
        START   = 3'b001,
        DATA    = 3'b010,
        STOP    = 3'b011,
        ERROR   = 3'b100
    } state_t;
    
    state_t current_state, next_state;
    reg [2:0] bit_counter;
    reg [7:0] data_byte;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            current_state <= IDLE;
            bit_counter <= 3'b000;
            done <= 1'b0;
        end 
        else begin
            current_state <= next_state;

            if (current_state == DATA) begin
                data_byte[bit_counter] <= in;
                bit_counter <= bit_counter + 1;
            end else if (current_state == STOP || current_state == ERROR) begin
                bit_counter <= 3'b000;
            end

            if (current_state == STOP && in == 1'b1) begin
                done <= 1'b1;
            end else begin
                done <= 1'b0;
            end
        end
    end

    always @(*) begin
        case (current_state)
            IDLE: begin
                if (in == 1'b0)
                    next_state = START;
                else
                    next_state = IDLE;
            end
            START: begin
                if (in == 1'b0)
                    next_state = DATA;
                else
                    next_state = IDLE; // Start bit must be 0
            end
            DATA: begin
                if (bit_counter == 3'b111) // 8 bits received
                    next_state = STOP;
                else
                    next_state = DATA;
            end
            STOP: begin
                if (in == 1'b1)
                    next_state = IDLE;
                else
                    next_state = ERROR;
            end
            ERROR: begin
                if (in == 1'b1)
                    next_state = IDLE;
                else
                    next_state = ERROR;
            end
            default: next_state = IDLE;
        endcase
    end

endmodule
