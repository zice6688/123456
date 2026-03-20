module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output done
);

    reg [1:0] state, next_state;
    reg [1:0] byte_count;

    // State encoding
    localparam IDLE = 2'b00, BYTE1 = 2'b01, BYTE2 = 2'b10, BYTE3 = 2'b11;

    // State transition
    always @(posedge clk) begin
        if (reset) begin
            state <= IDLE;
        end else begin
            state <= next_state;
        end
    end

    // Next state logic and byte count
    always @(*) begin
        next_state = state; // default
        byte_count = 2'b00;
        case (state)
            IDLE: begin
                if (in[3] == 1) begin
                    next_state = BYTE1;
                    byte_count = 2'b01;
                end
            end
            BYTE1: begin
                next_state = BYTE2;
                byte_count = 2'b10;
            end
            BYTE2: begin
                next_state = BYTE3;
                byte_count = 2'b11;
            end
            BYTE3: begin
                if (in[3] == 1) begin
                    next_state = BYTE1;
                    byte_count = 2'b01;
                end else begin
                    next_state = IDLE;
                end
            end
        endcase
    end

    // Output logic
    assign done = (state == BYTE3);

endmodule
