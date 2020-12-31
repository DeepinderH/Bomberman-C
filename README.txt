CPSC 355 Project Part A README 
Name: Deepinder Hehar

Surprise packs: 
There are two surprise packs used in the game. The first one is an extra life surprise pack, which is represented on the board as "&". There is only
one of these surprise packs on the board in each game and increments the current number of lives by 1. The second surprise pack is a double score surprise pack, 
which is represented on the board as "!". There is also only one of these surprise packs on the board in each game and it doubles the player's current score
if it is positive.

As per one of the TA's instructions, I have set the max number of rows and columns to fit on my screen, and thus they have both been limited to 25.
This is shown in the script file. Also, the script file contains 3 different games played at different board sizes, followed by showing the top scores
before and after a game. After this point in the script file, input validation for the program is shown.

Instructions to compile & run the code:
Firstly, download the ProjectParta.c file in the dropbox.
To run this program, open command prompt & cd to the directory with all of the files.
Then, compile the ProjectParta.c using gcc and open the compiled file using the following command line arguments:

(compiled_file_name) (player_name) (number_of_rows) (number_of_columns)
