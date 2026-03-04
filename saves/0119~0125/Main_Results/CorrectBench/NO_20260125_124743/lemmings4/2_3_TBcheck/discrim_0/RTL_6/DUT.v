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

    typedef enum reg [2:0] {
        STATE_WALK_LEFT,
        STATE_WALK_RIGHT,
        STATE_FALLING_LEFT,
        STATE_FALLING_RIGHT,
        STATE_DIG_LEFT,
        STATE_DIG_RIGHT,
        STATE_SPLATTER
    } state_t;

    reg [4:0] fall_counter; // 5 bits to count up to 20
    state_t state, next_state;

    always @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= STATE_WALK_LEFT;
            fall_counter <= 0;
        end else begin
            state <= next_state;
            if (state == STATE_FALLING_LEFT || state == STATE_FALLING_RIGHT) begin
                fall_counter <= fall_counter + 1;
            end else begin
                fall_counter <= 0;
            end
        end
    end

    always @(*) begin
        // Default outputs
        walk_left = 0;
        walk_right = 0;
        aaah = 0;
        digging = 0;

        case (state)
            STATE_WALK_LEFT: begin
                walk_left = 1;
                if (!ground) begin
                    next_state = STATE_FALLING_LEFT;
                end else if (dig) begin
                    next_state = STATE_DIG_LEFT;
                end else if (bump_left || bump_right) begin
                    next_state = STATE_WALK_RIGHT;
                end else begin
                    next_state = STATE_WALK_LEFT;
                end
            end

            STATE_WALK_RIGHT: begin
                walk_right = 1;
                if (!ground) begin
                    next_state = STATE_FALLING_RIGHT;
                end else if (dig) begin
                    next_state = STATE_DIG_RIGHT;
                end else if (bump_left || bump_right) begin
                    next_state = STATE_WALK_LEFT;
                end else begin
                    next_state = STATE_WALK_RIGHT;
                end
            end

            STATE_FALLING_LEFT: begin
                aaah = 1;
                if (ground && fall_counter <= 20) begin
                    next_state = STATE_WALK_LEFT;
                end else if (ground && fall_counter > 20) begin
                    next_state = STATE_SPLATTER;
                end else begin
                    next_state = STATE_FALLING_LEFT;
                end
            end

            STATE_FALLING_RIGHT: begin
                aaah = 1;
                if (ground && fall_counter <= 20) begin
                    next_state = STATE_WALK_RIGHT;
                end else if (ground && fall_counter > 20) begin
                    next_state = STATE_SPLATTER;
                end else begin
                    next_state = STATE_FALLING_RIGHT;
                end
            end

            STATE_DIG_LEFT: begin
                digging = 1;
                if (!ground) begin
                    next_state = STATE_FALLING_LEFT;
                end else begin
                    next_state = STATE_DIG_LEFT;
                end
            end

            STATE_DIG_RIGHT: begin
                digging = 1;
                if (!ground) begin
                    next_state = STATE_FALLING_RIGHT;
                end else begin
                    next_state = STATE_DIG_RIGHT;
                end
            end

            STATE_SPLATTER: begin
                // All outputs are 0
                next_state = STATE_SPLATTER;
            end

            default: begin
                next_state = STATE_SPLATTER;
            end
        endcase
    end

endmodule
