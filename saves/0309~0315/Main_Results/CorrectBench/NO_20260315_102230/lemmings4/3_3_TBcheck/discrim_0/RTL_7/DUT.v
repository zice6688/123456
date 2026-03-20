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

    // Define states
    typedef enum logic [2:0] {
        WALKING_LEFT = 3'b000,
        WALKING_RIGHT = 3'b001,
        FALLING_LEFT = 3'b010,
        FALLING_RIGHT = 3'b011,
        DIGGING_LEFT = 3'b100,
        DIGGING_RIGHT = 3'b101,
        SPLATTERED = 3'b110
    } state_t;

    state_t state, next_state;
    logic [4:0] fall_counter; // 5 bits to count up to 20

    // State transition logic
    always @(*) begin
        case (state)
            WALKING_LEFT: begin
                if (!ground) next_state = FALLING_LEFT;
                else if (dig) next_state = DIGGING_LEFT;
                else if (bump_left || bump_right) next_state = WALKING_RIGHT;
                else next_state = WALKING_LEFT;
            end
            WALKING_RIGHT: begin
                if (!ground) next_state = FALLING_RIGHT;
                else if (dig) next_state = DIGGING_RIGHT;
                else if (bump_left || bump_right) next_state = WALKING_LEFT;
                else next_state = WALKING_RIGHT;
            end
            FALLING_LEFT: begin
                if (ground) next_state = (fall_counter > 20) ? SPLATTERED : WALKING_LEFT;
                else next_state = FALLING_LEFT;
            end
            FALLING_RIGHT: begin
                if (ground) next_state = (fall_counter > 20) ? SPLATTERED : WALKING_RIGHT;
                else next_state = FALLING_RIGHT;
            end
            DIGGING_LEFT: begin
                if (!ground) next_state = FALLING_LEFT;
                else next_state = DIGGING_LEFT;
            end
            DIGGING_RIGHT: begin
                if (!ground) next_state = FALLING_RIGHT;
                else next_state = DIGGING_RIGHT;
            end
            SPLATTERED: begin
                next_state = SPLATTERED;
            end
            default: next_state = WALKING_LEFT;
        endcase
    end

    // State flip-flops and fall counter
    always @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= WALKING_LEFT;
            fall_counter <= 0;
        end else begin
            state <= next_state;
            if (!ground && (state == FALLING_LEFT || state == FALLING_RIGHT))
                fall_counter <= fall_counter + 1;
            else if (ground)
                fall_counter <= 0;
        end
    end

    // Output logic
    always @(*) begin
        walk_left = 0;
        walk_right = 0;
        aaah = 0;
        digging = 0;

        case (state)
            WALKING_LEFT: walk_left = 1;
            WALKING_RIGHT: walk_right = 1;
            FALLING_LEFT, FALLING_RIGHT: aaah = 1;
            DIGGING_LEFT: digging = 1;
            DIGGING_RIGHT: digging = 1;
            SPLATTERED: begin
                walk_left = 0;
                walk_right = 0;
                aaah = 0;
                digging = 0;
            end
        endcase
    end

endmodule
