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
        STATE_WALK_LEFT   = 3'b000,
        STATE_WALK_RIGHT  = 3'b001,
        STATE_FALL_LEFT   = 3'b010,
        STATE_FALL_RIGHT  = 3'b011,
        STATE_DIG_LEFT    = 3'b100,
        STATE_DIG_RIGHT   = 3'b101,
        STATE_SPLATTER    = 3'b110
    } state_t;

    state_t state, next_state;
    integer fall_count;

    always_ff @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= STATE_WALK_LEFT;
            fall_count <= 0;
        end else begin
            state <= next_state;
            if (aaah) begin
                fall_count <= fall_count + 1;
            end else if (ground) begin
                fall_count <= 0;
            end
        end
    end

    always_comb begin
        next_state = state; // Default to no state change.
        walk_left = 0;
        walk_right = 0;
        aaah = 0;
        digging = 0;

        case (state)
            STATE_WALK_LEFT: begin
                walk_left = 1;
                if (!ground) begin
                    next_state = STATE_FALL_LEFT; 
                end else if (dig) begin
                    next_state = STATE_DIG_LEFT;
                end else if (bump_left || bump_right) begin
                    next_state = STATE_WALK_RIGHT;
                end
            end

            STATE_WALK_RIGHT: begin
                walk_right = 1;
                if (!ground) begin
                    next_state = STATE_FALL_RIGHT;
                end else if (dig) begin
                    next_state = STATE_DIG_RIGHT;
                end else if (bump_left || bump_right) begin
                    next_state = STATE_WALK_LEFT;
                end
            end

            STATE_FALL_LEFT: begin
                aaah = 1;
                if (fall_count > 20 && ground) begin
                    next_state = STATE_SPLATTER;
                end else if (ground) begin
                    next_state = STATE_WALK_LEFT;
                end
            end

            STATE_FALL_RIGHT: begin
                aaah = 1;
                if (fall_count > 20 && ground) begin
                    next_state = STATE_SPLATTER;
                end else if (ground) begin
                    next_state = STATE_WALK_RIGHT;
                end
            end

            STATE_DIG_LEFT: begin
                digging = 1;
                if (!ground) begin
                    next_state = STATE_FALL_LEFT;
                end
            end

            STATE_DIG_RIGHT: begin
                digging = 1;
                if (!ground) begin
                    next_state = STATE_FALL_RIGHT;
                end
            end

            STATE_SPLATTER: begin
                // Do nothing; all outputs are 0.
            end
        endcase
    end

endmodule
