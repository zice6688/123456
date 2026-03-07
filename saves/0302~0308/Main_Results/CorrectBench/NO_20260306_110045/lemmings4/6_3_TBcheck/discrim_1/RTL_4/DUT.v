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
        LEFT_WALK = 3'b000,
        RIGHT_WALK = 3'b001,
        FALL = 3'b010,
        LEFT_DIG = 3'b011,
        RIGHT_DIG = 3'b100,
        SPLATTER = 3'b101
    } state_t;
    
    state_t state, next_state;
    reg [4:0] fall_count;

    always @(*) begin
        case (state)
            LEFT_WALK: begin
                if (ground == 0) next_state = FALL;
                else if (dig == 1) next_state = LEFT_DIG;
                else if (bump_left) next_state = RIGHT_WALK;
                else next_state = LEFT_WALK;
            end
            RIGHT_WALK: begin
                if (ground == 0) next_state = FALL;
                else if (dig == 1) next_state = RIGHT_DIG;
                else if (bump_right) next_state = LEFT_WALK;
                else next_state = RIGHT_WALK;
            end
            FALL: begin
                if (ground == 1) begin
                    if (fall_count > 20) next_state = SPLATTER;
                    else if (state == LEFT_WALK || state == LEFT_DIG) next_state = LEFT_WALK;
                    else if (state == RIGHT_WALK || state == RIGHT_DIG) next_state = RIGHT_WALK;
                end else next_state = FALL;
            end
            LEFT_DIG: begin
                if (ground == 0) next_state = FALL;
                else next_state = LEFT_DIG;
            end
            RIGHT_DIG: begin
                if (ground == 0) next_state = FALL;
                else next_state = RIGHT_DIG;
            end
            SPLATTER: next_state = SPLATTER; // Remains in SPLATTER state
            default: next_state = LEFT_WALK; // Default to avoid latches
        endcase
    end

    always @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= LEFT_WALK;
            fall_count <= 0;
        end else begin
            state <= next_state;
            if (state == FALL && ground == 0) fall_count <= fall_count + 1;
            else fall_count <= 0;
        end
    end

    always @(*) begin
        walk_left = (state == LEFT_WALK);
        walk_right = (state == RIGHT_WALK);
        aaah = (state == FALL);
        digging = (state == LEFT_DIG || state == RIGHT_DIG);
    end

endmodule
