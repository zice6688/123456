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
        LEFT = 3'b000,
        RIGHT = 3'b001,
        FALL_LEFT = 3'b010,
        FALL_RIGHT = 3'b011,
        DIG_LEFT = 3'b100,
        DIG_RIGHT = 3'b101,
        SPLATTERED = 3'b110
    } state_t;

    state_t state, next_state;
    reg [4:0] fall_counter; // 5 bits to count from 0 to 31

    // State transition
    always @(*) begin
        case (state)
            LEFT: begin
                if (!ground) 
                    next_state = FALL_LEFT;
                else if (dig) 
                    next_state = DIG_LEFT;
                else if (bump_left || bump_right) 
                    next_state = RIGHT;
                else 
                    next_state = LEFT;
            end
            RIGHT: begin
                if (!ground) 
                    next_state = FALL_RIGHT;
                else if (dig) 
                    next_state = DIG_RIGHT;
                else if (bump_left || bump_right) 
                    next_state = LEFT;
                else 
                    next_state = RIGHT;
            end
            FALL_LEFT: begin
                if (ground && fall_counter > 20) 
                    next_state = SPLATTERED;
                else if (ground) 
                    next_state = LEFT;
                else 
                    next_state = FALL_LEFT;
            end
            FALL_RIGHT: begin
                if (ground && fall_counter > 20) 
                    next_state = SPLATTERED;
                else if (ground) 
                    next_state = RIGHT;
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
            SPLATTERED: begin
                next_state = SPLATTERED;
            end
            default: begin
                next_state = LEFT;
            end
        endcase
    end

    // State flip-flops
    always @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= LEFT;
            fall_counter <= 0;
        end else begin
            state <= next_state;
            if (state == FALL_LEFT || state == FALL_RIGHT)
                fall_counter <= fall_counter + 1;
            else
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
            LEFT: walk_left = 1;
            RIGHT: walk_right = 1;
            FALL_LEFT, FALL_RIGHT: aaah = 1;
            DIG_LEFT: begin 
                digging = 1;
                walk_left = 1;
            end
            DIG_RIGHT: begin 
                digging = 1;
                walk_right = 1;
            end
            SPLATTERED: begin
                walk_left = 0;
                walk_right = 0;
                aaah = 0;
                digging = 0;
            end
        endcase
    end

endmodule
