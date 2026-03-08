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
        FALLING_LEFT = 3'b010,
        FALLING_RIGHT = 3'b011,
        DIG_LEFT = 3'b100,
        DIG_RIGHT = 3'b101,
        SPLATTER = 3'b110
    } state_t;

    reg [2:0] state, next_state;
    reg [4:0] fall_counter; // Counter for falling

    always @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= LEFT;
            fall_counter <= 0;
        end else begin
            state <= next_state;
            if (aaah)
                fall_counter <= fall_counter + 1;
            else
                fall_counter <= 0;
        end
    end

    always @(*) begin
        walk_left = 0;
        walk_right = 0;
        aaah = 0;
        digging = 0;
        next_state = state;

        case (state)
            LEFT: begin
                walk_left = 1;
                if (!ground) 
                    next_state = FALLING_LEFT;
                else if (dig)
                    next_state = DIG_LEFT;
                else if (bump_left)
                    next_state = RIGHT;
            end

            RIGHT: begin
                walk_right = 1;
                if (!ground) 
                    next_state = FALLING_RIGHT;
                else if (dig)
                    next_state = DIG_RIGHT;
                else if (bump_right)
                    next_state = LEFT;
            end

            FALLING_LEFT: begin
                aaah = 1;
                if (ground) 
                    next_state = (fall_counter >= 20) ? SPLATTER : LEFT;
            end

            FALLING_RIGHT: begin
                aaah = 1;
                if (ground) 
                    next_state = (fall_counter >= 20) ? SPLATTER : RIGHT;
            end

            DIG_LEFT: begin
                digging = 1;
                if (!ground)
                    next_state = FALLING_LEFT;
            end

            DIG_RIGHT: begin
                digging = 1;
                if (!ground)
                    next_state = FALLING_RIGHT;
            end

            SPLATTER: begin
                walk_left = 0;
                walk_right = 0;
                aaah = 0;
                digging = 0;
            end

            default: begin
                next_state = LEFT;
            end
        endcase
    end

endmodule
