module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output reg [23:0] out_bytes,
    output reg done
);

    // Define state encoding
    typedef enum logic [1:0] {
        IDLE = 2'b00,
        BYTE1 = 2'b01,
        BYTE2 = 2'b10,
        BYTE3 = 2'b11
    } state_t;

    state_t state, next_state;

    // State Register
    always_ff @(posedge clk) begin
        if (reset)
            state <= IDLE;
        else
            state <= next_state;
    end

    // Next State Logic and Output Logic
    always_comb begin
        // Default assignments
        next_state = state;
        done = 0;
        out_bytes = 24'hx;

        case (state)
            IDLE: begin
                if (in[3] == 1) begin
                    next_state = BYTE1;
                end
            end
            BYTE1: begin
                out_bytes[23:16] = in;
                if (~reset) next_state = BYTE2;
            end
            BYTE2: begin
                out_bytes[15:8] = in;
                if (~reset) next_state = BYTE3;
            end
            BYTE3: begin
                out_bytes[7:0] = in;
                done = 1;
                if (~reset) next_state = IDLE;
            end
        endcase
    end

    // Update output bytes
    always_ff @(posedge clk) begin
        if (reset) begin
            out_bytes <= 0;
        end else begin
            if (state == BYTE1) out_bytes[23:16] <= in;
            else if (state == BYTE2) out_bytes[15:8] <= in;
            else if (state == BYTE3) out_bytes[7:0] <= in;
        end
    end

endmodule
