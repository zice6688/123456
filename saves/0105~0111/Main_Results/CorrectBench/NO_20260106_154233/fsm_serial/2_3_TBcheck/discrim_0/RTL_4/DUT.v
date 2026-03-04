module top_module (
    input clk,
    input in,
    input reset,
    output done
);

    reg [3:0] state, next_state;
    reg [2:0] bit_counter;
    reg done_reg;

    localparam IDLE      = 4'd0,
               START     = 4'd1,
               DATA_BITS = 4'd2,
               STOP      = 4'd3,
               DONE      = 4'd4,
               ERROR     = 4'd5;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= IDLE;
            bit_counter <= 3'd0;
            done_reg <= 1'b0;
        end else begin
            state <= next_state;
            if (state == DATA_BITS)
                bit_counter <= bit_counter + 3'd1;
            else
                bit_counter <= 3'd0;

            if (state == DONE)
                done_reg <= 1'b1;
            else
                done_reg <= 1'b0;
        end
    end

    always @(*) begin
        next_state = state; // Default to stay in current state
        case (state)
            IDLE: begin
                if (in == 1'b0) // Start bit detected
                    next_state = START;
            end
            START: begin
                next_state = DATA_BITS;
            end
            DATA_BITS: begin
                if (bit_counter == 3'd7)
                    next_state = STOP;
            end
            STOP: begin
                if (in == 1'b1) // Stop bit detected
                    next_state = DONE;
                else
                    next_state = ERROR;
            end
            DONE: begin
                if (in == 1'b1) // Wait for line to return to idle to restart
                    next_state = IDLE;
            end
            ERROR: begin
                if (in == 1'b1) // Wait for line to return to idle to restart
                    next_state = IDLE;
            end
            default: next_state = IDLE;
        endcase
    end

    assign done = done_reg;

endmodule
