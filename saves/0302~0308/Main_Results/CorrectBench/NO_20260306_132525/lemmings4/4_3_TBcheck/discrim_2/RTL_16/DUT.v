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
        STATE_WALK_LEFT = 3'b000,
        STATE_WALK_RIGHT = 3'b001,
        STATE_FALL_LEFT = 3'b010,
        STATE_FALL_RIGHT = 3'b011,
        STATE_DIG_LEFT = 3'b100,
        STATE_DIG_RIGHT = 3'b101,
        STATE_SPLATTER = 3'b110
    } state_t;

    state_t state, next_state;
    logic [4:0] fall_count;

    always_ff @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= STATE_WALK_LEFT;
            fall_count <= 5'd0;
        end else begin
            state <= next_state;
            if (aaah)
                fall_count <= fall_count + 5'd1;
            else
                fall_count <= 5'd0;
        end
    end

    always_comb begin
        // Default outputs
        walk_left = 1'b0;
        walk_right = 1'b0;
        aaah = 1'b0;
        digging = 1'b0;
        next_state = state;

        case (state)
            STATE_WALK_LEFT: begin
                if (!ground) begin
                    aaah = 1'b1;
                    next_state = STATE_FALL_LEFT;
                end else if (dig) begin
                    digging = 1'b1;
                    next_state = STATE_DIG_LEFT;
                end else if (bump_left | bump_right) begin
                    next_state = STATE_WALK_RIGHT;
                end else begin
                    walk_left = 1'b1;
                end
            end
            STATE_WALK_RIGHT: begin
                if (!ground) begin
                    aaah = 1'b1;
                    next_state = STATE_FALL_RIGHT;
                end else if (dig) begin
                    digging = 1'b1;
                    next_state = STATE_DIG_RIGHT;
                end else if (bump_left | bump_right) begin
                    next_state = STATE_WALK_LEFT;
                end else begin
                    walk_right = 1'b1;
                end
            end
            STATE_FALL_LEFT: begin
                aaah = 1'b1;
                if (ground) begin
                    if (fall_count > 5'd20) begin
                        next_state = STATE_SPLATTER;
                    end else begin
                        next_state = STATE_WALK_LEFT;
                    end
                end
            end
            STATE_FALL_RIGHT: begin
                aaah = 1'b1;
                if (ground) begin
                    if (fall_count > 5'd20) begin
                        next_state = STATE_SPLATTER;
                    end else begin
                        next_state = STATE_WALK_RIGHT;
                    end
                end
            end
            STATE_DIG_LEFT: begin
                digging = 1'b1;
                if (!ground) begin
                    aaah = 1'b1;
                    next_state = STATE_FALL_LEFT;
                end
            end
            STATE_DIG_RIGHT: begin
                digging = 1'b1;
                if (!ground) begin
                    aaah = 1'b1;
                    next_state = STATE_FALL_RIGHT;
                end
            end
            STATE_SPLATTER: begin
                // All outputs are 0
            end
        endcase
    end

endmodule
