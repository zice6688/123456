module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output reg [23:0] out_bytes,
    output reg done
);

    reg [1:0] state, next_state;
    reg [23:0] message;

    localparam IDLE = 2'b00,
               BYTE1 = 2'b01,
               BYTE2 = 2'b10,
               BYTE3 = 2'b11;

    always @(posedge clk) begin
        if (reset) begin
            state <= IDLE;
            message <= 24'b0;
            out_bytes <= 24'b0;
            done <= 1'b0;
        end else begin
            state <= next_state;
            if (done)
                out_bytes <= message;
        end
    end

    always @(*) begin
        next_state = state;
        done = 1'b0;
        case (state)
            IDLE: begin
                if (in[3] == 1'b1)
                    next_state = BYTE1;
            end
            BYTE1: begin
                message[23:16] = in;
                next_state = BYTE2;
            end
            BYTE2: begin
                message[15:8] = in;
                next_state = BYTE3;
            end
            BYTE3: begin
                message[7:0] = in;
                done = 1'b1;
                next_state = IDLE;
            end
        endcase
    end

endmodule
