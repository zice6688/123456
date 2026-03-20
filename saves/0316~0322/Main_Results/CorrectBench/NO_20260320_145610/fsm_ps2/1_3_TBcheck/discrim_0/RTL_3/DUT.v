module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output done
);

    reg [1:0] state, next_state;
    reg [1:0] byte_count;
    
    // State encoding
    localparam IDLE = 2'd0,
               BYTE1 = 2'd1,
               BYTE2 = 2'd2,
               DONE = 2'd3;

    always @(posedge clk) begin
        if (reset) begin
            state <= IDLE;
        end else begin
            state <= next_state;
        end
    end

    always @(posedge clk) begin
        if (reset) begin
            byte_count <= 2'd0;
        end else if (state == BYTE1 || state == BYTE2) begin
            byte_count <= byte_count + 1;
        end
    end

    always @(*) begin
        next_state = state;
        case (state)
            IDLE: begin
                if (in[3] == 1) begin
                    next_state = BYTE1;
                end
            end
            BYTE1: begin
                next_state = BYTE2;
            end
            BYTE2: begin
                next_state = DONE;
            end
            DONE: begin
                if (in[3] == 1) begin
                    next_state = BYTE1;
                end else begin
                    next_state = IDLE;
                end
            end
        endcase
    end

    assign done = (state == DONE);

endmodule
