module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output reg [23:0] out_bytes,
    output reg done
);

    // State encoding
    typedef enum reg [1:0] {WAIT_FOR_HEADER, BYTE_1, BYTE_2, BYTE_3} state_t;
    state_t state, next_state;

    // Internal registers to store bytes
    reg [7:0] byte1, byte2, byte3;

    // State transition
    always @(posedge clk) begin
        if (reset) begin
            state <= WAIT_FOR_HEADER;
            out_bytes <= 24'b0;
            done <= 1'b0;
        end else begin
            state <= next_state;
            if (done) begin
                out_bytes <= {byte1, byte2, byte3};
            end else begin
                out_bytes <= 24'bx; // don't care
            end
        end
    end

    // Next state logic
    always @(*) begin
        // Default assignments
        next_state = state;
        done = 1'b0;

        case (state)
            WAIT_FOR_HEADER: begin
                if (in[3] == 1'b1) begin
                    next_state = BYTE_1;
                end
            end
            BYTE_1: begin
                byte1 = in;
                next_state = BYTE_2;
            end
            BYTE_2: begin
                byte2 = in;
                next_state = BYTE_3;
            end
            BYTE_3: begin
                byte3 = in;
                done = 1'b1;
                next_state = WAIT_FOR_HEADER;
            end
        endcase
    end

endmodule
