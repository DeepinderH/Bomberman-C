# Bomberman-C

This is an oversimplified version of the retro bomberman game which I created for my CPSC 355 class.
I have added the project specification pdf in the repository.

Instructions to compile & run the code:
Firstly, download the ProjectParta.c file in the dropbox.
To run this program, open command prompt & cd to the directory with all of the files.
Then, compile the ProjectParta.c using gcc and open the compiled file using the following command line arguments:

(compiled_file_name) (player_name) (number_of_rows) (number_of_columns)

The logic of the game is as follows:

Initially, the user is given the choice to either quit, view a certain number of top scores (from the corresponding log file), or play the game.
If the player chooses to play the game, they will be shown the uncovered board with all values (initially for marking purposes), followed by a covered board.
The user chooses a location on the board to place a bomb. The first coordinate is the row location and the second coordinate is the column location. 
For example, on a 10x10 board, when promoted for the bomb location, the user can enter between 0 and 9 for both the row and column (separated by a space), i.e. 3 7. 

All of the float values around the location of the bomb placement will then be added together to determine the players score.
If the score is negative, it will be reset to zero and one life will be lost. If it is positive, the player will keep this score going into the next turn.
The number of bombs will also be decremented by one. 

The game will end in one of the three scenarios, after which the user's score will be added to the log file:
1. The exit tile is found, which is represented by "*".
2. The user runs out of lives.
3. The user runs out of bombs.

There are three other special tiles on the board:
1. Range multipliers: Represented by "$". There are multiple of these on the board. If found, increases the bomb-range by 2^n, where n is the number of
range multipliers found. For example, if 3 range multipliers are found, then 8 layers will be blown up after the next bomb placement. 
2. Score multiplier: Represented by "!". There is only one of these tiles. If the user's score is positive when the tile is found, the score is doubled.
3. Extra life pack: Represented by "&". There is only one of these tiles. Adds one extra life to the user's current number of lives.
