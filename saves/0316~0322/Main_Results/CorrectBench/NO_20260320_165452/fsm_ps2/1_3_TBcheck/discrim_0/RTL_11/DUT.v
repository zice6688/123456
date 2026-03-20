module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output done
);

    typedef enum reg [1:0] {
        WAIT_BYTE_1 = 2'b00,
        BYTE_2 = 2'b01,
        BYTE_3 = 2'b10
    } state_t;
    
    reg [1:0] state, next_state;
    assign done = (state == BYTE_3); // Signal done in the cycle after BYTE_3
    
    always @(posedge clk) begin
        if (reset) begin
            state <= WAIT_BYTE_1;
        end else begin
            state <= next_state;
        end
    end

    always @(*) begin
        next_state = state;
        case(state)
            WAIT_BYTE_1: begin
                if (in[3] == 1) begin
                    next_state = BYTE_2;   // Found start of a new message
                end
            end
            BYTE_2: begin
                next_state = BYTE_3;       // Transition to byte 3
            end
            BYTE_3: begin
                next_state = WAIT_BYTE_1;  // Go back to waiting for a new message
            end
        endcase
    end

endmodule
