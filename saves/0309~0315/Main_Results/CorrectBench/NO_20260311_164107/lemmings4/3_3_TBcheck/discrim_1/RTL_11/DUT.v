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
        WALK_LEFT,
        WALK_RIGHT,
        DIG_LEFT,
        DIG_RIGHT,
        FALL_LEFT,
        FALL_RIGHT,
        SPLATTER
    } state_t;

    state_t state, next_state;
    reg [4:0] fall_count;  // Counter for falling clock cycles

    always @(*) begin
        // Default outputs
        walk_left = 0;
        walk_right = 0;
        aaah = 0;
        digging = 0;

        case (state)
            WALK_LEFT: begin
                walk_left = 1;
                if (!ground)
                    next_state = FALL_LEFT;
                else if (dig && ground)
                    next_state = DIG_LEFT;
                else if (bump_left)
                    next_state = WALK_RIGHT;
                else
                    next_state = WALK_LEFT;
            end
            WALK_RIGHT: begin
                walk_right = 1;
                if (!ground)
                    next_state = FALL_RIGHT;
                else if (dig && ground)
                    next_state = DIG_RIGHT;
                else if (bump_right)
                    next_state = WALK_LEFT;
                else
                    next_state = WALK_RIGHT;
            end
            DIG_LEFT: begin
                digging = 1;
                if (!ground)
                    next_state = FALL_LEFT;
                else 
                    next_state = DIG_LEFT;
            end
            DIG_RIGHT: begin
                digging = 1;
                if (!ground)
                    next_state = FALL_RIGHT;
                else
                    next_state = DIG_RIGHT;
            end
            FALL_LEFT: begin
                aaah = 1;
                if (ground) begin
                    if (fall_count > 20)
                        next_state = SPLATTER;
                    else
                        next_state = WALK_LEFT;
                end else
                    next_state = FALL_LEFT;
            end
            FALL_RIGHT: begin
                aaah = 1;
                if (ground) begin
                    if (fall_count > 20)
                        next_state = SPLATTER;
                    else
                        next_state = WALK_RIGHT;
                end else
                    next_state = FALL_RIGHT;
            end
            SPLATTER: begin
                next_state = SPLATTER;
            end
        endcase
    end

    always @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= WALK_LEFT;
            fall_count <= 0;
        end else begin
            state <= next_state;
            if (state == FALL_LEFT || state == FALL_RIGHT)
                fall_count <= fall_count + 1;
            else
                fall_count <= 0;
        end
    end
endmodule
