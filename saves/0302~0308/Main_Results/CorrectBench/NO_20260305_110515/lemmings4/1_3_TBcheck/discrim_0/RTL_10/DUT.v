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

    // State encoding
    typedef enum reg [2:0] {
        STATE_WALK_LEFT  = 3'b000,
        STATE_WALK_RIGHT = 3'b001,
        STATE_FALL_LEFT  = 3'b010,
        STATE_FALL_RIGHT = 3'b011,
        STATE_DIG_LEFT   = 3'b100,
        STATE_DIG_RIGHT  = 3'b101,
        STATE_SPLATTER   = 3'b110
    } state_t;

    state_t state, next_state;
    reg [4:0] fall_count; // Counter to track falling duration

    always @(posedge clk or posedge areset) begin
        if (areset) begin
            // Asynchronous reset to walk left
            state <= STATE_WALK_LEFT;
            fall_count <= 0;
        end else begin
            state <= next_state;
            if (aaah) begin
                fall_count <= fall_count + 1;
            end else begin
                fall_count <= 0;
            end
        end
    end

    always @(*) begin
        case(state)
            STATE_WALK_LEFT: begin
                if (!ground) begin
                    next_state = STATE_FALL_LEFT;     // Start falling if no ground
                end else if (dig && ground) begin
                    next_state = STATE_DIG_LEFT;      // Start digging if dig command given on ground
                end else if (bump_left || (bump_left && bump_right)) begin
                    next_state = STATE_WALK_RIGHT;    // Switch direction on bump
                end else begin
                    next_state = STATE_WALK_LEFT;     // Continue walking left
                end
            end
            STATE_WALK_RIGHT: begin
                if (!ground) begin
                    next_state = STATE_FALL_RIGHT;    // Start falling if no ground
                end else if (dig && ground) begin
                    next_state = STATE_DIG_RIGHT;     // Start digging if dig command given on ground
                end else if (bump_right || (bump_left && bump_right)) begin
                    next_state = STATE_WALK_LEFT;     // Switch direction on bump
                end else begin
                    next_state = STATE_WALK_RIGHT;    // Continue walking right
                end
            end
            STATE_FALL_LEFT: begin
                if (ground) begin
                    if (fall_count > 20) begin
                        next_state = STATE_SPLATTER; // Splatter when falling exceeds 20 cycles
                    end else begin
                        next_state = STATE_WALK_LEFT; // Land and walk left
                    end
                end else begin
                    next_state = STATE_FALL_LEFT;    // Continue falling
                end
            end
            STATE_FALL_RIGHT: begin
                if (ground) begin
                    if (fall_count > 20) begin
                        next_state = STATE_SPLATTER; // Splatter when falling exceeds 20 cycles
                    end else begin
                        next_state = STATE_WALK_RIGHT; // Land and walk right
                    end
                end else begin
                    next_state = STATE_FALL_RIGHT;   // Continue falling
                end
            end
            STATE_DIG_LEFT: begin
                if (!ground) begin
                    next_state = STATE_FALL_LEFT;    // Start falling when not on ground
                end else begin
                    next_state = STATE_DIG_LEFT;     // Continue digging
                end
            end
            STATE_DIG_RIGHT: begin
                if (!ground) begin
                    next_state = STATE_FALL_RIGHT;   // Start falling when not on ground
                end else begin
                    next_state = STATE_DIG_RIGHT;    // Continue digging
                end
            end
            STATE_SPLATTER: begin
                next_state = STATE_SPLATTER;         // Remain in splatter state
            end
        endcase
    end

    always @(*) begin
        walk_left = (state == STATE_WALK_LEFT);
        walk_right = (state == STATE_WALK_RIGHT);
        aaah = (state == STATE_FALL_LEFT || state == STATE_FALL_RIGHT);
        digging = (state == STATE_DIG_LEFT || state == STATE_DIG_RIGHT);
    end

endmodule
