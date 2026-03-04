module top_module (
    input clk,
    input areset,
    input bump_left,
    input bump_right,
    input ground,
    input dig,
    output walk_left,
    output walk_right,
    output aaah,
    output digging
);

    // State encoding
    typedef enum reg [2:0] {
        WALK_LEFT   = 3'b000,
        WALK_RIGHT  = 3'b001,
        FALL_LEFT   = 3'b010,
        FALL_RIGHT  = 3'b011,
        DIG_LEFT    = 3'b100,
        DIG_RIGHT   = 3'b101,
        SPLATTER    = 3'b110
    } state_t;

    state_t current_state, next_state;
    reg [4:0] fall_counter; // Counts the number of cycles while falling

    // State transitions
    always @(*) begin
        case (current_state)
            WALK_LEFT: begin
                if (!ground)
                    next_state = FALL_LEFT;
                else if (dig)
                    next_state = DIG_LEFT;
                else if (bump_left)
                    next_state = WALK_RIGHT;
                else
                    next_state = WALK_LEFT;
            end

            WALK_RIGHT: begin
                if (!ground)
                    next_state = FALL_RIGHT;
                else if (dig)
                    next_state = DIG_RIGHT;
                else if (bump_right)
                    next_state = WALK_LEFT;
                else
                    next_state = WALK_RIGHT;
            end

            FALL_LEFT: begin
                if (ground) begin
                    if (fall_counter > 20)
                        next_state = SPLATTER;
                    else
                        next_state = WALK_LEFT;
                end
                else
                    next_state = FALL_LEFT;
            end

            FALL_RIGHT: begin
                if (ground) begin
                    if (fall_counter > 20)
                        next_state = SPLATTER;
                    else
                        next_state = WALK_RIGHT;
                end
                else
                    next_state = FALL_RIGHT;
            end

            DIG_LEFT: begin
                if (!ground)
                    next_state = FALL_LEFT;
                else
                    next_state = DIG_LEFT;
            end

            DIG_RIGHT: begin
                if (!ground)
                    next_state = FALL_RIGHT;
                else
                    next_state = DIG_RIGHT;
            end

            SPLATTER: begin
                next_state = SPLATTER;
            end

            default: next_state = WALK_LEFT;
        endcase
    end

    // Sequential logic
    always @(posedge clk or posedge areset) begin
        if (areset) begin
            current_state <= WALK_LEFT;
            fall_counter <= 0;
        end
        else begin
            current_state <= next_state;
            if (current_state == FALL_LEFT || current_state == FALL_RIGHT)
                fall_counter <= fall_counter + 1;
            else
                fall_counter <= 0;
        end
    end

    // Outputs
    assign walk_left  = (current_state == WALK_LEFT);
    assign walk_right = (current_state == WALK_RIGHT);
    assign aaah       = (current_state == FALL_LEFT || current_state == FALL_RIGHT);
    assign digging    = (current_state == DIG_LEFT || current_state == DIG_RIGHT);

endmodule
