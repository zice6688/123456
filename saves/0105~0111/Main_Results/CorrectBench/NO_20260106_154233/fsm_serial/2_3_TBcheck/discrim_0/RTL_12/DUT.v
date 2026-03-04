module top_module (
    input clk,
    input in,
    input reset,
    output done
);

    reg [3:0] state, next_state;
    reg [7:0] data_bits;
    reg done_reg;

    // State encoding
    localparam IDLE     = 4'd0,
               START    = 4'd1,
               DATA_0   = 4'd2,
               DATA_1   = 4'd3,
               DATA_2   = 4'd4,
               DATA_3   = 4'd5,
               DATA_4   = 4'd6,
               DATA_5   = 4'd7,
               DATA_6   = 4'd8,
               DATA_7   = 4'd9,
               STOP     = 4'd10,
               ERROR    = 4'd11;

    // State transition
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= IDLE;
            done_reg <= 1'b0;
        end 
        else begin
            state <= next_state;
            if (state == STOP && in == 1'b1) 
                done_reg <= 1'b1;
            else 
                done_reg <= 1'b0;
        end
    end

    // Next state logic
    always @(*) begin
        case (state)
            IDLE: begin
                if (in == 1'b0)
                    next_state = START;
                else
                    next_state = IDLE;
            end
            START: begin
                next_state = DATA_0;
            end
            DATA_0: begin
                next_state = DATA_1;
            end
            DATA_1: begin
                next_state = DATA_2;
            end
            DATA_2: begin
                next_state = DATA_3;
            end
            DATA_3: begin
                next_state = DATA_4;
            end
            DATA_4: begin
                next_state = DATA_5;
            end
            DATA_5: begin
                next_state = DATA_6;
            end
            DATA_6: begin
                next_state = DATA_7;
            end
            DATA_7: begin
                next_state = STOP;
            end
            STOP: begin
                if (in == 1'b1)
                    next_state = IDLE;
                else
                    next_state = ERROR;
            end
            ERROR: begin
                if (in == 1'b1)
                    next_state = IDLE;
                else
                    next_state = ERROR;
            end
            default: next_state = IDLE;
        endcase
    end

    assign done = done_reg;

endmodule
