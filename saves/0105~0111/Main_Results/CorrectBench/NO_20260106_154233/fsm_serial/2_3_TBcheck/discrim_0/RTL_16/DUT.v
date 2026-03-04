module top_module (
	input clk,
	input in,
	input reset,
	output reg done
);

    typedef enum logic [2:0] {
        IDLE = 3'b000,
        START = 3'b001,
        DATA = 3'b010,
        STOP = 3'b011,
        ERROR = 3'b100
    } state_t;
    
    state_t current_state, next_state;
    reg [2:0] bit_counter;
    reg [7:0] data_byte;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            current_state <= IDLE;
            bit_counter <= 0;
            done <= 0;
        end else begin
            current_state <= next_state;
            if (current_state == DATA) begin
                data_byte[bit_counter] <= in;
                bit_counter <= bit_counter + 1;
            end
        end
    end
    
    always @(*) begin
        done = 0;
        case (current_state)
            IDLE: begin
                if (in == 0)
                    next_state = START;
                else
                    next_state = IDLE;
            end
            START: begin
                if (in == 0)
                    next_state = DATA;
                else
                    next_state = IDLE;
            end
            DATA: begin
                if (bit_counter == 7)
                    next_state = STOP;
                else
                    next_state = DATA;
            end
            STOP: begin
                if (in == 1) begin
                    next_state = IDLE;
                    done = 1;
                end else
                    next_state = ERROR;
            end
            ERROR: begin
                if (in == 1)
                    next_state = IDLE;
                else
                    next_state = ERROR;
            end
            default: next_state = IDLE;
        endcase
    end

endmodule
