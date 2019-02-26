**26-02-19: New Implementation**

Implementation (_a simpler one_):

- Store the initial matrix
- Have a separate 2d array for the falling piece 
- Display function combines the both of them 
- Keep track of location of falling piece (CurrentX, CurrentY)
	- Update the initial matrix once the piece has collided/hit the ground
	- check_full_lines
		- if true, clear lines, push everything down, reupdate matrix, add to score
		- else, proceed to insertion of next piece
- rotate_collision_check & rotate needs to be hardcoded for each possibile orientation of each piece (takes in old matrix and new piece) (rotate uses rotate_collision_check to see wheren
- insert_piece needs to be recoded

**19-02-19: Coding Tetris**

Notes:

 - LEDs are arranged in series in a snake-like fashion (15 x 32). -> Need to create a function to convert a 2D array of arrays into a 1D output to display on the Matrix. (Actual game is 10 x 20) (save for the end)
 - Figuring out how to display the 1D array onto the Matrix. (save it for the end)
 - Splitting up the display (game + other things)
 - Tetris colors (and how to display colors)
 - Using C
 - Ticker library to set software interrupt to make piece go down (calls software interrupt function every GAME_SPEED; moving function is separate)

Functions needed (basic matrix manipulation + game):

 - Check for full lines (after collision)
 - Clear full line(s) (adds to score)
 - Item dropping (arguments: Matrix, color of piece)
	 - includes function to return coordinates of lowest tiles of colored piece (part of collision)
	 - includes collision check
	 - movement down (if no collision)
	 - sets next piece flag to true
 - Display next piece
 - Rotate (rotate piece in the display)
 - Move left
 - Move right
 - Slam
 - Display Score
 - game() 
	(includes
	- checking for Game Over
	- generation of next piece (random) (needs a flag to generate after collision of previous piece)
	- clearing line (as above)
	- an increase in speed (changes GAME_SPEED)
	- detect full lines (as above))
- *others...* 
