module top_module (
    input clk,
    input areset,
    input bump_left,
    input bump_right,
    input ground,
    input dig,
    output reg walk_left,
    output reg walk_right,
    output reg aaah,
    output reg digging
);

    typedef enum logic [2:0] {
        LEFT = 3'b000,
        RIGHT = 3'b001,
        FALL_LEFT = 3'b010,
        FALL_RIGHT = 3'b011,
        DIG_LEFT = 3'b100,
        DIG_RIGHT = 3'b101,
        SPLATTER = 3'b110
    } state_t;

    state_t state, next_state;
    logic [4:0] fall_count; // 5 bits to count up to 21

    always @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= LEFT;
            fall_count <= 5'd0;
        end else begin
            state <= next_state;
            if (aaah) 
                fall_count <= fall_count + 1;
            else 
                fall_count <= 5'd0;
        end
    end

    always @(*) begin
        // Default outputs
        walk_left = 1'b0;
        walk_right = 1'b0;
        aaah = 1'b0;
        digging = 1'b0;
        next_state = state;

        case (state)
            LEFT: begin
                walk_left = 1'b1;
                if (!ground) 
                    next_state = FALL_LEFT;
                else if (dig) 
                    next_state = DIG_LEFT;
                else if (bump_left || bump_right) 
                    next_state = RIGHT;
            end

            RIGHT: begin
                walk_right = 1'b1;
                if (!ground) 
                    next_state = FALL_RIGHT;
                else if (dig) 
                    next_state = DIG_RIGHT;
                else if (bump_left || bump_right) 
                    next_state = LEFT;
            end

            FALL_LEFT: begin
                aaah = 1'b1;
                if (fall_count >= 5'd20 && ground) 
                    next_state = SPLATTER;
                else if (ground) 
                    next_state = LEFT;
            end

            FALL_RIGHT: begin
                aaah = 1'b1;
                if (fall_count >= 5'd20 && ground) 
                    next_state = SPLATTER;
                else if (ground) 
                    next_state = RIGHT;
            end

            DIG_LEFT: begin
                digging = 1'b1;
                if (!ground) 
                    next_state = FALL_LEFT;
            end

            DIG_RIGHT: begin
                digging = 1'b1;
                if (!ground) 
                    next_state = FALL_RIGHT;
            end

            SPLATTER: begin
                // Stay in SPLATTER, all outputs should be 0
            end
        endcase
    end
endmodule
