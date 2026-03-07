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
    typedef enum logic [2:0] {
        WL = 3'b000,  // walk_left
        WR = 3'b001,  // walk_right
        F = 3'b010,   // falling
        DL = 3'b011,  // digging left
        DR = 3'b100,  // digging right
        SPLAT = 3'b101 // splattered
    } state_t;

    state_t state, next_state;
    integer fall_count;

    // State transition
    always_ff @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= WL;
            fall_count <= 0;
        end else begin
            state <= next_state;
            if (next_state == F)
                fall_count <= fall_count + 1;
            else 
                fall_count <= 0;
        end
    end

    // Next state logic
    always_comb begin
        case (state)
            WL: begin
                if (!ground)
                    next_state = F;
                else if (dig)
                    next_state = DL;
                else if (bump_left || bump_right)
                    next_state = WR;
                else
                    next_state = WL;
            end
            WR: begin
                if (!ground)
                    next_state = F;
                else if (dig)
                    next_state = DR;
                else if (bump_left || bump_right)
                    next_state = WL;
                else
                    next_state = WR;
            end
            F: begin
                if (ground) begin
                    if (fall_count > 20)
                        next_state = SPLAT;
                    else if (state == WL)
                        next_state = WL;
                    else
                        next_state = WR;
                end else
                    next_state = F;
            end
            DL: begin
                if (!ground)
                    next_state = F;
                else
                    next_state = DL;
            end
            DR: begin
                if (!ground)
                    next_state = F;
                else
                    next_state = DR;
            end
            SPLAT: begin
                next_state = SPLAT;
            end
            default: next_state = WL;
        endcase
    end

    // Output logic
    always_ff @(posedge clk or posedge areset) begin
        if (areset) begin
            walk_left <= 1;
            walk_right <= 0;
            aaah <= 0;
            digging <= 0;
        end else begin
            walk_left <= (state == WL);
            walk_right <= (state == WR);
            aaah <= (state == F);
            digging <= ((state == DL) || (state == DR));
        end
    end

endmodule
