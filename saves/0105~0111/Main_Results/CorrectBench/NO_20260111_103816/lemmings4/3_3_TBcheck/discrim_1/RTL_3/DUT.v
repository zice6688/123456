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
	typedef enum {
		STATE_WALK_LEFT,
		STATE_WALK_RIGHT,
		STATE_FALL_LEFT,
		STATE_FALL_RIGHT,
		STATE_DIG_LEFT,
		STATE_DIG_RIGHT,
		STATE_SPLATTERED
	} state_t;
	
	state_t state, next_state;
	integer fall_time;

	// State Transition
	always @(*) begin
		case (state)
			STATE_WALK_LEFT: begin
				if (!ground) next_state = STATE_FALL_LEFT;
				else if (dig) next_state = STATE_DIG_LEFT;
				else if (bump_left) next_state = STATE_WALK_RIGHT;
				else next_state = STATE_WALK_LEFT;
			end
			
			STATE_WALK_RIGHT: begin
				if (!ground) next_state = STATE_FALL_RIGHT;
				else if (dig) next_state = STATE_DIG_RIGHT;
				else if (bump_right) next_state = STATE_WALK_LEFT;
				else next_state = STATE_WALK_RIGHT;
			end
			
			STATE_FALL_LEFT: begin
				if (ground) begin
					if (fall_time > 20) next_state = STATE_SPLATTERED;
					else next_state = STATE_WALK_LEFT;
				end
				else next_state = STATE_FALL_LEFT;
			end
			
			STATE_FALL_RIGHT: begin
				if (ground) begin
					if (fall_time > 20) next_state = STATE_SPLATTERED;
					else next_state = STATE_WALK_RIGHT;
				end
				else next_state = STATE_FALL_RIGHT;
			end
			
			STATE_DIG_LEFT: begin
				if (!ground) next_state = STATE_FALL_LEFT;
				else next_state = STATE_DIG_LEFT;
			end
			
			STATE_DIG_RIGHT: begin
				if (!ground) next_state = STATE_FALL_RIGHT;
				else next_state = STATE_DIG_RIGHT;
			end
			
			STATE_SPLATTERED: begin
				next_state = STATE_SPLATTERED;
			end
			
			default: next_state = STATE_WALK_LEFT;
		endcase
	end
	
	// State Register and Fall Time Counter
	always @(posedge clk or posedge areset) begin
		if (areset) begin
			state <= STATE_WALK_LEFT;
			fall_time <= 0;
		end
		else begin
			state <= next_state;
			if (state == STATE_FALL_LEFT || state == STATE_FALL_RIGHT)
				fall_time <= fall_time + 1;
			else
				fall_time <= 0;
		end
	end
	
	// Output Logic
	always @(*) begin
		walk_left = 0;
		walk_right = 0;
		aaah = 0;
		digging = 0;
		
		case (state)
			STATE_WALK_LEFT: walk_left = 1;
			STATE_WALK_RIGHT: walk_right = 1;
			STATE_FALL_LEFT, STATE_FALL_RIGHT: aaah = 1;
			STATE_DIG_LEFT: begin
				walk_left = 1;
				digging = 1;
			end
			STATE_DIG_RIGHT: begin
				walk_right = 1;
				digging = 1;
			end
		endcase
	end

endmodule
