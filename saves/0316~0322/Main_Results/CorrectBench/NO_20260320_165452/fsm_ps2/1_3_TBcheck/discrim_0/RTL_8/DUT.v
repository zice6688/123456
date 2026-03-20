module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output reg done
);
    
    reg [1:0] state, next_state;
    
    localparam WAIT   = 2'b00,
               BYTE1  = 2'b01,
               BYTE2  = 2'b10,
               BYTE3  = 2'b11;

    // State transition logic
    always @(*) begin
        case (state)
            WAIT:  next_state = (in[3] == 1'b1) ? BYTE1 : WAIT;
            BYTE1: next_state = BYTE2;
            BYTE2: next_state = BYTE3;
            BYTE3: next_state = (in[3] == 1'b1) ? BYTE1 : WAIT;
            default: next_state = WAIT;
        endcase
    end

    // State flip-flops with synchronous reset
    always @(posedge clk) begin
        if (reset)
            state <= WAIT;
        else
            state <= next_state;
    end

    // Output logic
    always @(posedge clk) begin
        if (reset)
            done <= 1'b0;
        else
            done <= (state == BYTE3);
    end

endmodule
