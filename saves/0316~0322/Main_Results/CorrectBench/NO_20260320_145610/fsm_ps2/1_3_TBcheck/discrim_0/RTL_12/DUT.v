module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output done
);

    reg [1:0] state, next_state;
    reg [1:0] byte_counter;

    // State encoding
    localparam IDLE   = 2'd0;
    localparam BYTE_1 = 2'd1;
    localparam BYTE_2 = 2'd2;
    localparam BYTE_3 = 2'd3;

    // State transition logic
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
                if (in[3] == 1'b1) begin
                    next_state = BYTE_1;
                end else begin
                    next_state = IDLE;
                end
            end
            BYTE_1: next_state = BYTE_2;
            BYTE_2: next_state = BYTE_3;
            BYTE_3: begin
                if (in[3] == 1'b1) begin
                    next_state = BYTE_1; // Possible start of a new message
                end else begin
                    next_state = IDLE;
                end
            end
            default: next_state = IDLE;
        endcase
    end

    // Output logic
    assign done = (state == BYTE_3);

endmodule
