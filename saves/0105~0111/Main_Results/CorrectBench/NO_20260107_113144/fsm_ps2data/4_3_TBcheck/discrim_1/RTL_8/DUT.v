module top_module (
	input clk,
	input [7:0] in,
	input reset,
	output reg [23:0] out_bytes,
	output reg done
);

    // Define states
    typedef enum logic [1:0] {
        IDLE = 2'b00,     // Waiting for start of message
        BYTE1 = 2'b01,    // Receiving first byte
        BYTE2 = 2'b10,    // Receiving second byte
        BYTE3 = 2'b11     // Receiving third byte
    } state_t;

    state_t state, next_state;
    reg [7:0] byte1, byte2, byte3;

    // State register
    always @(posedge clk) begin
        if (reset) begin
            state <= IDLE;
        end else begin
            state <= next_state;
        end
    end

    // Next state logic and output logic
    always @(*) begin
        // Default values
        next_state = state;
        byte1 = out_bytes[23:16];
        byte2 = out_bytes[15:8];
        byte3 = out_bytes[7:0];
        done = 1'b0;

        case (state)
            IDLE: begin
                if (in[3] == 1'b1) begin
                    next_state = BYTE1;
                end
            end
            BYTE1: begin
                byte1 = in;
                next_state = BYTE2;
            end
            BYTE2: begin
                byte2 = in;
                next_state = BYTE3;
            end
            BYTE3: begin
                byte3 = in;
                out_bytes = {byte1, byte2, byte3};
                done = 1'b1;
                next_state = IDLE;
            end
        endcase
    end

    // Output register update
    always @(posedge clk) begin
        if (reset) begin
            out_bytes <= 24'b0;
        end else if (done) begin
            out_bytes <= {byte1, byte2, byte3};
        end
    end

endmodule
