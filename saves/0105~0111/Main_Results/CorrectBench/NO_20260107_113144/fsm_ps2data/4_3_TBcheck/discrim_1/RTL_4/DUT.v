module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output reg [23:0] out_bytes,
    output reg done
);

    reg [1:0] state, next_state;
    reg [23:0] message;
    reg [7:0] byte1, byte2, byte3;

    localparam IDLE = 2'b00, 
               BYTE1 = 2'b01, 
               BYTE2 = 2'b10, 
               BYTE3 = 2'b11;

    always @(posedge clk) begin
        if (reset) begin
            state <= IDLE;
            done <= 0;
            out_bytes <= 24'b0;
        end else begin
            state <= next_state;
        end
    end

    always @(posedge clk) begin
        if (reset) begin
            byte1 <= 8'b0;
            byte2 <= 8'b0;
            byte3 <= 8'b0;
        end else begin
            case (next_state)
                BYTE1: byte1 <= in;
                BYTE2: byte2 <= in;
                BYTE3: byte3 <= in;
                default: ;
            endcase
        end
    end

    always @(*) begin
        message = {byte1, byte2, byte3};
        out_bytes = message;
        done = 0;
        case (state)
            IDLE: begin
                if (in[3] == 1'b1)
                    next_state = BYTE1;
                else
                    next_state = IDLE;
            end
            BYTE1: next_state = BYTE2;
            BYTE2: next_state = BYTE3;
            BYTE3: begin
                done = 1;
                next_state = IDLE;
            end
            default: next_state = IDLE;
        endcase
    end

endmodule
