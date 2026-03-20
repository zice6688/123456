module top_module (
	input clk,
	input [7:0] in,
	input reset,
	output done
);

    reg [1:0] state, next_state;
    reg done_reg;

    localparam WAIT = 2'b00,
               BYTE1 = 2'b01,
               BYTE2 = 2'b10,
               BYTE3 = 2'b11;

    // State Transition
    always @(posedge clk) begin
        if (reset) begin
            state <= WAIT;
        end else begin
            state <= next_state;
        end
    end

    // Next State Logic
    always @(*) begin
        done_reg = 0;
        case (state)
            WAIT: begin
                if (in[3] == 1'b1) begin
                    next_state = BYTE1;
                end else begin
                    next_state = WAIT;
                end
            end
            BYTE1: begin
                next_state = BYTE2;
            end
            BYTE2: begin
                next_state = BYTE3;
            end
            BYTE3: begin
                next_state = WAIT;
                done_reg = 1;
            end
            default: begin
                next_state = WAIT;
            end
        endcase
    end

    // Output Logic
    assign done = done_reg;

endmodule
