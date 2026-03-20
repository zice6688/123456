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

    // State Encoding
    typedef enum reg [2:0] {
        S_WALK_LEFT      = 3'd0,
        S_WALK_RIGHT     = 3'd1,
        S_FALL_LEFT      = 3'd2,
        S_FALL_RIGHT     = 3'd3,
        S_DIG_LEFT       = 3'd4,
        S_DIG_RIGHT      = 3'd5,
        S_SPLATTER       = 3'd6
    } state_t;
    
    reg [2:0] state, next_state;
    reg [4:0] fall_counter; // 5 bits to count up to 20

    // Next state logic
    always @(*) begin
        next_state = state; // Default: stay in the same state
        case(state)
            S_WALK_LEFT: begin
                if (~ground)
                    next_state = S_FALL_LEFT;
                else if (dig)
                    next_state = S_DIG_LEFT;
                else if (bump_left)
                    next_state = S_WALK_RIGHT;
            end
            S_WALK_RIGHT: begin
                if (~ground)
                    next_state = S_FALL_RIGHT;
                else if (dig)
                    next_state = S_DIG_RIGHT;
                else if (bump_right)
                    next_state = S_WALK_LEFT;
            end
            S_FALL_LEFT, S_FALL_RIGHT: begin
                if (ground) begin
                    if (fall_counter > 20)
                        next_state = S_SPLATTER;
                    else
                        next_state = (state == S_FALL_LEFT) ? S_WALK_LEFT : S_WALK_RIGHT;
                end
            end
            S_DIG_LEFT: begin
                if (~ground)
                    next_state = S_FALL_LEFT;
            end
            S_DIG_RIGHT: begin
                if (~ground)
                    next_state = S_FALL_RIGHT;
            end
            S_SPLATTER: begin
                // Remain in S_SPLATTER
            end
        endcase
    end

    // State register update
    always @(posedge clk or posedge areset) begin
        if (areset)
            state <= S_WALK_LEFT;
        else
            state <= next_state;
    end
    
    // Fall counter logic
    always @(posedge clk or posedge areset) begin
        if (areset)
            fall_counter <= 0;
        else if (state == S_FALL_LEFT || state == S_FALL_RIGHT)
            fall_counter <= fall_counter + 1;
        else
            fall_counter <= 0;
    end

    // Output logic
    always @(*) begin
        walk_left = (state == S_WALK_LEFT);
        walk_right = (state == S_WALK_RIGHT);
        aaah = (state == S_FALL_LEFT || state == S_FALL_RIGHT);
        digging = (state == S_DIG_LEFT || state == S_DIG_RIGHT);
    end
    
endmodule
