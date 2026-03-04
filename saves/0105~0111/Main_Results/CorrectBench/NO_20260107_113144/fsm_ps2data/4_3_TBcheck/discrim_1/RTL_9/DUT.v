module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output reg [23:0] out_bytes,
    output reg done
);

    typedef enum reg [1:0] {IDLE, BYTE1, BYTE2, BYTE3} state_t;
    state_t current_state, next_state;

    reg [23:0] message_buffer;

    always @(posedge clk) begin
        if (reset) begin
            current_state <= IDLE;
        end else begin
            current_state <= next_state;
            if (next_state == IDLE) begin
                done <= 0;
                out_bytes <= 24'd0;
            end else if (next_state == BYTE3) begin
                out_bytes <= message_buffer;
                done <= 1;
            end else begin
                done <= 0;
            end
        end
    end

    always @(*) begin
        next_state = current_state;
        case (current_state)
            IDLE: begin
                if (in[3])
                    next_state = BYTE1;
            end
            BYTE1: begin
                message_buffer[23:16] = in;
                next_state = BYTE2;
            end
            BYTE2: begin
                message_buffer[15:8] = in;
                next_state = BYTE3;
            end
            BYTE3: begin
                message_buffer[7:0] = in;
                next_state = IDLE;
            end
        endcase
    end

endmodule
