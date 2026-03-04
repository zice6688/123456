module top_module (
    input clk,
    input [7:0] in,
    input reset,
    output reg [23:0] out_bytes,
    output reg done
);

    // Define states
    typedef enum logic [1:0] {
        IDLE = 2'b00,
        BYTE1 = 2'b01,
        BYTE2 = 2'b10,
        BYTE3 = 2'b11
    } state_t;
    
    // State registers
    reg [1:0] current_state, next_state;
    
    // State transition and output logic
    always @(*) begin
        // Default assignments
        done = 0;
        next_state = current_state;
        
        case (current_state)
            IDLE: begin
                if (in[3]) begin 
                    next_state = BYTE1;
                end
            end
            BYTE1: begin
                next_state = BYTE2;
            end
            BYTE2: begin
                next_state = BYTE3;
            end
            BYTE3: begin
                done = 1;
                next_state = IDLE;
            end
        endcase
    end
    
    // State register update
    always @(posedge clk) begin
        if (reset) begin
            current_state <= IDLE;
        end else begin
            current_state <= next_state;
        end
    end
    
    // Capture bytes logic
    always @(posedge clk) begin
        if (current_state == IDLE && in[3]) begin
            out_bytes[23:16] <= in;
        end else if (current_state == BYTE1) begin
            out_bytes[15:8] <= in;
        end else if (current_state == BYTE2) begin
            out_bytes[7:0] <= in;
        end
    end

endmodule
