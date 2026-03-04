module top_module (
	input clk,
	input [7:0] in,
	input reset,
	output reg [23:0] out_bytes,
	output reg done
);

    reg [1:0] state, next_state;
    reg [23:0] message_reg;

    // State encoding
    localparam IDLE = 2'b00;
    localparam BYTE1 = 2'b01;
    localparam BYTE2 = 2'b10;
    localparam DONE = 2'b11;
	
    // State transition
    always @(posedge clk) begin
        if (reset) begin
            state <= IDLE;
            message_reg <= 24'b0;
            done <= 0;
            out_bytes <= 24'b0;
        end else begin
            state <= next_state;
            case(next_state)
                BYTE1: begin
                    message_reg[23:16] <= in;
                end
                BYTE2: begin
                    message_reg[15:8] <= in;
                end
                DONE: begin
                    message_reg[7:0] <= in;
                    out_bytes <= {message_reg[23:8], in};
                    done <= 1;
                end
                default: begin
                    out_bytes <= 24'b0;
                    done <= 0;
                end
            endcase
        end
    end

    // Next state logic
    always @(*) begin
        case (state)
            IDLE: begin
                if (in[3] == 1)
                    next_state = BYTE1;
                else
                    next_state = IDLE;
            end
            BYTE1: begin
                next_state = BYTE2;
            end
            BYTE2: begin
                next_state = DONE;
            end
            DONE: begin
                next_state = IDLE;
            end
            default: begin
                next_state = IDLE;
            end
        endcase
    end

endmodule
