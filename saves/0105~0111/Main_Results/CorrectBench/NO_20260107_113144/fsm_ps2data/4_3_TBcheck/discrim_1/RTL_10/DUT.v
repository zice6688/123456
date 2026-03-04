module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output reg [23:0] out_bytes,
    output reg done
);

    typedef enum logic [1:0] {
        IDLE = 2'b00,
        BYTE1 = 2'b01,
        BYTE2 = 2'b10,
        BYTE3 = 2'b11
    } state_t;

    state_t current_state, next_state;

    always_ff @(posedge clk) begin
        if (reset) begin
            current_state <= IDLE;
            out_bytes <= 24'b0;
            done <= 1'b0;
        end else begin
            current_state <= next_state;
        end
    end

    always_comb begin
        next_state = current_state;
        done = 1'b0;
        
        case (current_state)
            IDLE: begin
                if (in[3] == 1'b1) begin
                    next_state = BYTE1;
                end
            end
            BYTE1: begin
                out_bytes[23:16] = in;
                next_state = BYTE2;
            end
            BYTE2: begin
                out_bytes[15:8] = in;
                next_state = BYTE3;
            end
            BYTE3: begin
                out_bytes[7:0] = in;
                done = 1'b1;
                next_state = IDLE;
            end
        endcase
    end

endmodule
