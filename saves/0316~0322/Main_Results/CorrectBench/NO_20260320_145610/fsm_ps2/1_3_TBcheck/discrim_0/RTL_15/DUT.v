module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output done
);
    // State encoding
    parameter IDLE = 2'b00,
              BYTE1 = 2'b01,
              BYTE2 = 2'b10,
              BYTE3 = 2'b11;

    reg [1:0] state, next_state;
    reg done_reg;

    assign done = done_reg;

    // State transition
    always @(posedge clk) begin
        if (reset) begin
            state <= IDLE;
        end else begin
            state <= next_state;
        end
    end

    // Next state logic
    always @(*) begin
        case (state)
            IDLE: begin
                if (in[3] == 1'b1)
                    next_state = BYTE1;
                else
                    next_state = IDLE;
            end
            BYTE1: begin
                next_state = BYTE2;
            end
            BYTE2: begin
                next_state = BYTE3;
            end
            BYTE3: begin
                next_state = IDLE;
            end
            default: begin
                next_state = IDLE;
            end
        endcase
    end

    // Output logic
    always @(posedge clk) begin
        if (reset) begin
            done_reg <= 1'b0;
        end else if (state == BYTE3) begin
            done_reg <= 1'b1;
        end else begin
            done_reg <= 1'b0;
        end
    end

endmodule
