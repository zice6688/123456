module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output reg [23:0] out_bytes,
    output reg done
);
    
    reg [1:0] state, next_state;
    reg [23:0] message_buffer;
    
    localparam IDLE = 2'd0;
    localparam BYTE_1 = 2'd1;
    localparam BYTE_2 = 2'd2;
    localparam DONE = 2'd3;
    
    // State Transition
    always @(*) begin
        case (state)
            IDLE: begin
                if (in[3] == 1'b1)
                    next_state = BYTE_1;
                else
                    next_state = IDLE;
            end
            BYTE_1: next_state = BYTE_2;
            BYTE_2: next_state = DONE;
            DONE: next_state = IDLE;
            default: next_state = IDLE;
        endcase
    end

    // State Register
    always @(posedge clk) begin
        if (reset)
            state <= IDLE;
        else
            state <= next_state;
    end

    // Output Logic
    always @(posedge clk) begin
        if (reset) begin
            out_bytes <= 24'd0;
            done <= 1'b0;
            message_buffer <= 24'd0;
        end else begin
            done <= 1'b0;
            case (next_state)
                BYTE_1: begin
                    message_buffer[23:16] <= in;
                end
                BYTE_2: begin
                    message_buffer[15:8] <= in;
                end
                DONE: begin
                    message_buffer[7:0] <= in;
                    out_bytes <= {message_buffer[23:8], in};
                    done <= 1'b1;
                end
            endcase
        end
    end

endmodule
