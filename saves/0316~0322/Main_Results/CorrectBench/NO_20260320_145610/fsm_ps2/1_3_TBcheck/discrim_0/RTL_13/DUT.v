module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output reg done
);

    reg [1:0] state, next_state;
    reg [1:0] byte_count;

    // State encoding
    localparam IDLE = 2'd0;
    localparam BYTE1 = 2'd1;
    localparam BYTE2 = 2'd2;
    localparam BYTE3 = 2'd3;

    // State transition logic
    always @(*) begin
        case (state)
            IDLE: next_state = (in[3] == 1) ? BYTE1 : IDLE;
            BYTE1: next_state = BYTE2;
            BYTE2: next_state = BYTE3;
            BYTE3: next_state = (in[3] == 1) ? BYTE1 : IDLE;
            default: next_state = IDLE;
        endcase
    end

    // State register
    always @(posedge clk) begin
        if (reset) begin
            state <= IDLE;
        end else begin
            state <= next_state;
        end
    end

    // Byte count logic
    always @(posedge clk) begin
        if (reset) begin
            byte_count <= 2'd0;
        end else if (state == BYTE3) begin
            byte_count <= 2'd0;
        end else if (state != IDLE) begin
            byte_count <= byte_count + 2'd1;
        end
    end

    // Output logic
    always @(posedge clk) begin
        if (reset) begin
            done <= 1'b0;
        end else if (state == BYTE3 && byte_count == 2'd2) begin
            done <= 1'b1;
        end else begin
            done <= 1'b0;
        end
    end

endmodule
