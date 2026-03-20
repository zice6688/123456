module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output reg done
);

    reg [1:0] state, next_state;

    // State encoding
    localparam WAIT_FIRST_BYTE = 2'b00;
    localparam BYTE_ONE        = 2'b01;
    localparam BYTE_TWO        = 2'b10;
    localparam BYTE_THREE      = 2'b11;

    // State transition
    always @(posedge clk) begin
        if (reset)
            state <= WAIT_FIRST_BYTE;
        else
            state <= next_state;
    end

    // Next state logic
    always @(*) begin
        case (state)
            WAIT_FIRST_BYTE: begin
                if (in[3])
                    next_state = BYTE_ONE;
                else
                    next_state = WAIT_FIRST_BYTE;
            end
            BYTE_ONE: begin
                next_state = BYTE_TWO;
            end
            BYTE_TWO: begin
                next_state = BYTE_THREE;
            end
            BYTE_THREE: begin
                next_state = WAIT_FIRST_BYTE;
            end
            default: begin
                next_state = WAIT_FIRST_BYTE;
            end
        endcase
    end

    // Output logic
    always @(posedge clk) begin
        if (reset)
            done <= 0;
        else if (state == BYTE_THREE)
            done <= 1;
        else
            done <= 0;
    end

endmodule
