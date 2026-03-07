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
        WALK_LEFT = 3'd0,
        WALK_RIGHT = 3'd1,
        FALL = 3'd2,
        DIG_LEFT = 3'd3,
        DIG_RIGHT = 3'd4,
        SPLATTER = 3'd5
    } state_t;
    
    state_t state, next_state;
    reg [4:0] fall_count; // Counter to track fall duration
    
    always @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= WALK_LEFT;
            fall_count <= 5'd0;
        end else begin
            state <= next_state;
            if (state == FALL) begin
                fall_count <= fall_count + 1;
            end else begin
                fall_count <= 5'd0;
            end
        end
    end

    always @(*) begin
        // Default output states
        walk_left = 1'b0;
        walk_right = 1'b0;
        aaah = 1'b0;
        digging = 1'b0;
        
        case (state)
            WALK_LEFT: begin
                walk_left = 1'b1;
                if (!ground) begin
                    next_state = FALL;
                end else if (dig) begin
                    next_state = DIG_LEFT;
                end else if (bump_left) begin
                    next_state = WALK_RIGHT;
                end else begin
                    next_state = WALK_LEFT;
                end
            end
            WALK_RIGHT: begin
                walk_right = 1'b1;
                if (!ground) begin
                    next_state = FALL;
                end else if (dig) begin
                    next_state = DIG_RIGHT;
                end else if (bump_right) begin
                    next_state = WALK_LEFT;
                end else begin
                    next_state = WALK_RIGHT;
                end
            end
            FALL: begin
                aaah = 1'b1;
                if (fall_count > 20) begin
                    next_state = SPLATTER;
                end else if (ground) begin
                    if (state == WALK_LEFT || state == DIG_LEFT) begin
                        next_state = WALK_LEFT;
                    end else begin
                        next_state = WALK_RIGHT;
                    end
                end else begin
                    next_state = FALL;
                end
            end
            DIG_LEFT: begin
                digging = 1'b1;
                if (!ground) begin
                    next_state = FALL;
                end else begin
                    next_state = DIG_LEFT;
                end
            end
            DIG_RIGHT: begin
                digging = 1'b1;
                if (!ground) begin
                    next_state = FALL;
                end else begin
                    next_state = DIG_RIGHT;
                end
            end
            SPLATTER: begin
                walk_left = 1'b0;
                walk_right = 1'b0;
                aaah = 1'b0;
                digging = 1'b0;
                next_state = SPLATTER;
            end
        endcase
    end

endmodule
