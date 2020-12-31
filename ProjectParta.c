#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//Functions to be used during the project
//These will be explained below.
void initialize(float *grid, int rows, int cols, int n, int m, int positiveNumberMax, int negativeNumberMax, int specialNumberMax, int exitTileCounter, int extraLivesCounter, int doubleScoreCounter);
float randomNum (int n, int m, bool neg);
void displayGame(float *grid, int rows, int cols);
void initializeCoveredGame (char *coveredGrid, int rows, int cols);
void displayCoveredGame(char *coveredGrid, int rows, int cols, int lives, float score, int bombs, int specialChar);
int updateCoveredGame(float *grid, char *coveredGrid, int rows, int cols, int bombLocationX, int bombLocationY, int specialChar);
float calculateScore(float *grid, char *coveredGrid, int rows, int cols, int bombLocationX, int bombLocationY, int specialChar, float score);
void exitGame(char *playerName, float score, time_t startTime);
void logScore(FILE *file, char *playerName, float score, int endTime);
void displayTopScores(FILE *file, int n);
void selectionSort(float arr[], int arrIndex[], int n);
void swapFloat(float *xp, float *yp);
void swapInteger(int *xp, int *yp);

//Main function which takes in the command line arguments
// and calls the other functions to create the game & show top results to the user
int main(int argc, char *argv[]) 
{ 
    //if statement to ensure there are a valid number of command line arguments
    if (argc == 4){
        //variables to be read from command line arguments
        int rows;
        int cols;
        char *playerName;

        //variables used in the creation of the game/info displayed to the user
        int numOfExitTiles;
        int numOfExtraLives;
        int numOfDoubleScores;
        int lives;
        int bombs;
        float score;
        float scoreTemp;

        //minimum/maximum number of different tiles used to create the gameboard
        int minimumTileValue;
        int maximumTileValue;
        int positiveNumberMax;
        int negativeNumberMax;
        int specialNumberMax;

        //bomb location variables from scanf & specialChar used for surprise packs
        int bombLocationX;
        int bombLocationY;
        int specialChar;

        // startTime which is used to figure out duration of gameplay
        time_t startTime;

        //variables used to show the topscore to user
        int quitOrTopScore;
        int numberOfScore;

        //variable used for input validation
        int checkForScan;

        //reading command line arguments and storing the values
        rows = atoi (argv[2]);
        cols = atoi (argv[3]);
        playerName = malloc(strlen(argv[1])+1);
        strcpy(playerName, argv[1]);

        //initializing the covered/uncovered boards and setting pointers
        float grid [rows][cols];
        float* gridPointer = &grid[0][0];
        char coveredGrid [rows][cols];
        char* coveredPointer = &coveredGrid[0][0];

        // initializing minimum and maximum values for random numbers
        minimumTileValue = -15;
        maximumTileValue = 15;

        //initializing number of tiles with corresponding special packs
        numOfExitTiles = 1;
        numOfDoubleScores = 1;
        numOfExtraLives = 1;
        
        //initializing number of positive/negative/special numbers on board
        positiveNumberMax = (int)(rows * cols * 0.4);
        negativeNumberMax = (int)(rows * cols * 0.4);
        specialNumberMax = (int) (rows * cols * 0.2);

        //initializing lives, score and number of bombs
        lives = 3;
        score = 0.00;
        bombs = (rows * cols) * 0.05;

        //initializing specialChar (which identifies the number of $ hit) to zero
        specialChar = 0;
        
    //input validation for rows * columns to ensure they are greater than 10 and less than 25 (so they fit on screen)
     if(rows < 10 || rows > 25){
        printf("Invalid values entered! The values entered for rows & columns must be an integers between 10 and 25 (both inclusive). ");
        exit(0);
    }

     if(cols < 10 || cols > 25){
        printf("Invalid values entered! The values entered for rows & columns must be an integers between 10 and 25 (both inclusive). ");
        exit(0);
        }

    //getting user input to determine if they want to see top scores, exit program, or play the game.
    printf("Enter 1 to see top scores, -1 to exit the program or enter 0 and press enter to play the game: ");
    checkForScan = scanf("%d", &quitOrTopScore);

    //ensuring the user inputs an integer
    if(checkForScan != 1){
        printf("Invalid input! Exiting the program.\n");
        exit(0);
    }
    checkForScan = 0;

    //If statement for if the user wants to see top scores
    if(quitOrTopScore == 1){
        //Opening the log file 
        FILE *logFile = fopen("ProjectParta.log", "a+");

        //asking user for the number of top scores they want to see
        printf("Enter the number of top scores you want to see: ");
        checkForScan = scanf("%d", &numberOfScore);

        //ensuring the user inputs an integer
        if(checkForScan != 1){
            printf("Invalid input! Exiting the program.\n");
            exit(0);
        }
        checkForScan = 0;

        //calling function to display top scores to user
        displayTopScores(logFile, numberOfScore);

        //do while loop to keep asking the user for inputs
        do{
            //asking user for input again
            printf("Enter 1 to see a different number of top scores, -1 to exit the program or enter 0 and press enter to play the game: ");
            checkForScan = scanf("%d", &quitOrTopScore);

            //ensuring user inputs an integer 
            if(checkForScan != 1){
                    printf("Invalid input! Exiting the program.\n");
                    exit(0);
                }
            checkForScan = 0;

            //If statement for if the user wants to see the top scores
            if(quitOrTopScore == 1){
                printf("Enter the number of top scores you want to see: ");

                checkForScan = scanf("%d", &numberOfScore);

                //ensuring user inputs an integer
                if(checkForScan != 1){
                    printf("Invalid input! Exiting the program.\n");
                    exit(0);
                }
                checkForScan = 0;

                //displaying the top scores to user via dispalytopscores function
                displayTopScores(logFile, numberOfScore);
            }

            //else if statement for if the user wants to quit
            else if (quitOrTopScore == -1){
                fclose(logFile);
                printf("Exiting program. \n");
                exit(0);
            }

            //else if statement for if the user wants to play the game
            else if(quitOrTopScore == 0){
                fclose(logFile);
            }

            //else statement for if the user inputs an invalid value
            else{
                fclose(logFile);
                printf("Invalid input! \n");
                printf("Exiting program. \n");
                exit(0);
            }

        }while (quitOrTopScore == 1); //do while loop continues if the user continues to enter 1
        
    }

    //else if statement for if the user enters -1 (wants to quit)
    else if(quitOrTopScore == -1){
        printf("Exiting program. \n");
        exit(0);
    }

    //else if to do nothing if the user wants to play the game
    else if(quitOrTopScore == 0){}

    //else statement for if the user enters an invalid input
    else{
        printf("Invalid input! \n");
        printf("Exiting program. \n");
        exit(0);
    }

    //starting the time if the user wants to play the game
    startTime = time(NULL);

    //printing the input values of the player name, number of rows and columns
    printf("\n");
    printf("The player name is %s, the number of rows is %d and the number of columns is %d. \n \n", playerName, rows, cols);

    //calling srand to ensure random numbers are printed every time
    srand(time(0));

    //initializing and displaying the uncovered board
    initialize(gridPointer, rows, cols, minimumTileValue, maximumTileValue, positiveNumberMax, negativeNumberMax, specialNumberMax, numOfExitTiles ,numOfExtraLives, numOfDoubleScores);
    displayGame(gridPointer, rows, cols);
    
    //initializing and displaying the covered board
    initializeCoveredGame(coveredPointer,rows,cols);
    printf("\n");
    printf("Displaying the covered table...");
    printf("\n");
    displayCoveredGame(coveredPointer,rows,cols,lives,score,bombs,specialChar);

    //asking user for input location of bomb
    printf("Enter bomb position (x y) or enter -1 to quit the program: ");
    checkForScan = scanf("%d", &bombLocationX);

    //ensuring user inputs an integer
    if(checkForScan != 1){
        printf("Invalid input! Exiting the program.\n");
        exit(0);
    }
    checkForScan = 0;

    //exitting the game if the user inputs -1
    if(bombLocationX == -1){
        printf("Quitting Game. \n");
        exitGame(playerName,score,startTime);
    }
    checkForScan = scanf("%d", &bombLocationY);

    //ensuring user inputs an integer
    if(checkForScan != 1){
        printf("Invalid input! Exiting the program.\n");
        exit(0);
    }
    checkForScan = 0;

    //while loop to keep asking the user for an input until a valid input is entered
    while(bombLocationX < 0 || bombLocationX>= cols || bombLocationY < 0 || bombLocationY >= rows){
        //asking the user for input
        printf("Invalid location for bomb placement. Please enter a valid location for bomb placement.\n");
        printf("Enter bomb position (x y) or enter -1 to quit the program: ");
        checkForScan = scanf("%d", &bombLocationX);

        //ensuring the input is an integer
        if(checkForScan != 1){
            printf("Invalid input! Exiting the program.\n");
            exit(0);
        }
        checkForScan = 0;

        //exitting the game if the user inputs -1
        if(bombLocationX == -1){
            printf("Quitting Game. \n");
            exitGame(playerName,score,startTime);
        }
        checkForScan = scanf("%d", &bombLocationY);

        //ensuring the user inputs an integer
        if(checkForScan != 1){
            printf("Invalid input! Exiting the program.\n");
            exit(0);
        }
        checkForScan = 0;
    }

    //do while loop to run the game
    do {
       //score function which returns the new score after bomb is planted 
        score = calculateScore (gridPointer,coveredPointer,rows,cols,bombLocationX, bombLocationY, specialChar, score);

        //SpecialChar which counts the number of special tiles hit 
        specialChar = updateCoveredGame(gridPointer,coveredPointer,rows,cols,bombLocationX, bombLocationY, specialChar);

        //reducing the number of bombs by 1
        bombs = bombs - 1;

        //decrease lives by 1 if score is 0.
        if(score < 0){
            lives = lives - 1;
        }

        //displaying the covered game
        displayCoveredGame(coveredPointer,rows,cols,lives,score,bombs, specialChar);

        //if statement to check if the double score surprise pack is hit
        if(specialChar >= 400 && specialChar <1000 || specialChar >= 1400){
            specialChar = specialChar - 400;
            //if statement to check if the score is positive
            if(score > 0){
                score = score * 2;
                printf("Found Score x2 multiplier! Score has been doubled!\n");
                printf("New score: %.2f \n", score);
                printf("\n");
            }
            //Double score does nothing otherwise
            else{
                printf("Found Score x2 multiplier! It had no effect since score is not positive.\n");
                printf("\n");

            }
        }

        //if statement checking if the bomb hit the extra life surprise pack and incrementing lives by 1 if they did
        if(specialChar >= 200 && specialChar <400 || specialChar >= 1200 && specialChar <1400 || specialChar >=1600){
            specialChar = specialChar - 200;
            lives = lives + 1;
            printf("Found an extra life!!\n");
            printf("New number of lives: %d \n", lives);
            printf("\n");
        }

        //Ending game if player runs out of bombs
        if(bombs == 0){
            printf("Out of bombs! \n");
            printf("Game over. \n");
            exitGame(playerName,score,startTime);
        }

        //Ending game if player runs out of lives
        if(score <= 0 && lives == 0){
            printf("Out of lives! \n");
            printf("Game over. \n");
            exitGame(playerName,score,startTime);
        }

        //Ending game if exit tile is found
        if(specialChar >= 1000){
            printf("Exit Tile Found! \n");
            printf("Game over. \n");
            exitGame(playerName,score,startTime);
        }

        //temp score to store negative score
        scoreTemp = score;

        // resetting score to 0 if score negative and more lives are left
        if(score < 0 && lives >= 1){
            printf("Negative score. Resetting score to zero for next life. \n");
            printf("\n");
            score = 0.00;
        }

        // asking player for new bomb location
         printf("Enter bomb position (x y) or enter -1 to quit the program: ");
         checkForScan = scanf("%d", &bombLocationX);

        //Ensuring user inputs an integer
        if(checkForScan != 1){
            printf("Invalid input! Exiting the program.\n");
            exit(0);
        }
        checkForScan = 0;

        //Ending game if user enters -1
         if(bombLocationX == -1){
            printf("Exiting Game. \n");
            exitGame(playerName,scoreTemp,startTime);
        }

        checkForScan = scanf("%d", &bombLocationY);
        //Ensuring user enter an integer
        if(checkForScan != 1){
            printf("Invalid input! Exiting the program.\n");
            exit(0);
        }
        checkForScan = 0;

        //While loop to keep asking user for valid bomb location until valid location is put in
        while(bombLocationX < 0 || bombLocationX>= cols || bombLocationY < 0 || bombLocationY >= rows){
            printf("Invalid location for bomb placement. Please enter a valid location for bomb placement.\n");
            printf("Enter bomb position (x y) or enter -1 to quit the program: ");
            checkForScan = scanf("%d", &bombLocationX);

            //ensuring user enters an integer
            if(checkForScan != 1){
                printf("Invalid input! Exiting the program.\n");
                exit(0);
            }
            checkForScan = 0;

            //ending game if user enters -1
            if(bombLocationX == -1){
                printf("Quitting Game. \n");
                exitGame(playerName,score,startTime);
            }
            checkForScan = scanf("%d", &bombLocationY);

            //ensuring user enter an integer
            if(checkForScan != 1){
                printf("Invalid input! Exiting the program.\n");
                exit(0);
            }
            checkForScan = 0;
        }

        printf("\n");
    } while (bombLocationX != -1); //Looping until user enters -1

    free(playerName); //freeing player name space
    }

    //else statement for if invalid number of arguments entered
    else{
        printf("Invalid number of arguments! Use file name followed by player name, the number of rows and then the number of columns. ");
    }

    
}

//Some of the code for this function is from my assignment1
//initialize function to initialize the uncovered tables
void initialize(float *grid, int rows, int cols, int n, int m, int positiveNumberMax, int negativeNumberMax, int specialNumberMax, int exitTileCounter, int extraLivesCounter, int doubleScoreCounter){
//Counters to be used in loops
int counter1 = 0;
int counter2 = 0;
int counter3 = 0;
int counter4 = 0;
int counter5 = 0;
int counter6 = 0;
//bool neg to be used in randomnum function
bool neg;

//initializing all values to 0
for(int i = 0; i< rows; i++){
    for(int j = 0; j< cols; j++){
        *((grid + i*cols) +j) = 0;
    }
}

//while loop for filling 40% of random spots in the table with a random positive float  
while(counter1 < positiveNumberMax){
    int rand1 = rand();
    int rand2 = rand();
    int tempRow = (rand1 - rows * (rand1/rows)); 
    int tempCol = (rand2 - cols * (rand2/cols));
    neg = false;

        //If statement to only update if the current table spot doesnt have a value
        if(*((grid + tempRow * cols) + tempCol) == 0){

            *((grid + tempRow * cols) + tempCol) = randomNum(n,m,neg);
            counter1++;

    }

}

//while loop for filling 40% of random spots in the table with a random negative float  
while(counter2 < negativeNumberMax){
    int rand1 = rand();
    int rand2 = rand();
    int tempRow = (rand1 - rows * (rand1/rows)); 
    int tempCol = (rand2 - cols * (rand2/cols));
    neg = true;

    //If statement to only update if the current table spot doesnt have a value
    if(*((grid + tempRow * cols) + tempCol) == 0){
        *((grid + tempRow * cols) + tempCol) = randomNum(n,m,neg);
        counter2++;

    }

}

//while loop for filling 20% - 3 spots of random spots in the table with a "111", which represents a "$"
while(counter3 < specialNumberMax-3){
    int rand1 = rand();
    int rand2 = rand();
    int tempRow = (rand1 - rows * (rand1/rows)); 
    int tempCol = (rand2 - cols * (rand2/cols));

     //If statement to only update if the current table spot doesnt have a value
    if(*((grid + tempRow * cols) + tempCol) == 0){
        *((grid + tempRow * cols) + tempCol) = 111;
        counter3++;

    }

}

//while loop for filling 1 random spot in the table with a "999", which represents an exit tile
while (counter4 < exitTileCounter){
    int rand1 = rand();
    int rand2 = rand();
    int tempRow = (rand1 - rows * (rand1/rows)); 
    int tempCol = (rand2 - cols * (rand2/cols)); 

    //If statement to only update if the current table spot doesnt have a value
    if(*((grid + tempRow * cols) + tempCol) == 0){
        *((grid + tempRow * cols) + tempCol) = 999;
        counter4++;
    }
}

//while loop for filling 1 random spot in the table with a "222", which represents an extra life surprise pack
while (counter5 < extraLivesCounter){
    int rand1 = rand();
    int rand2 = rand();
    int tempRow = (rand1 - rows * (rand1/rows)); 
    int tempCol = (rand2 - cols * (rand2/cols)); 

    //If statement to only update if the current table spot doesnt have a value
    if(*((grid + tempRow * cols) + tempCol) == 0){
        *((grid + tempRow * cols) + tempCol) = 222;
        counter5++;
    }
}

//while loop for filling 1 random spot in the table with a "333", which represents a double score surprise pack
while (counter6 < doubleScoreCounter){
    int rand1 = rand();
    int rand2 = rand();
    int tempRow = (rand1 - rows * (rand1/rows)); 
    int tempCol = (rand2 - cols * (rand2/cols)); 

    //If statement to only update if the current table spot doesnt have a value
    if(*((grid + tempRow * cols) + tempCol) == 0){
        *((grid + tempRow * cols) + tempCol) = 333;
        counter6++;
    }
}

//for loop to fill any open spots with "111" which represents a "$"
for(int k = 0; k< rows; k++){
    for(int l = 0; l< cols; l++){
        if(*((grid + k*cols) +l) == 0){
            *((grid + k*cols) +l) = 111;
        }
    }
}

//percentage float, which represents the number of negative floats on the board
float percentage;
percentage =  (float) ((float)counter2 / (float) (rows*cols)) * 100;

//printing the percentage of negative floats
printf("The total negative numbers %d/%d = %.2f percent, which is less than or equal to 40 percent. \n", counter2, rows*cols, percentage);
}

//random num function which generates a positive or negative float within n and m, based on the neg parameter
float randomNum (int n, int m, bool neg){

    //if statement for if neg is false, generates positive random float
    if(neg == false){
        float temp = (float) (rand() & m) - ((float) rand()/ (float)(RAND_MAX));
         return temp;
    }
    
    //else statement for if neg is true, generates negative float
    else{
        float temp = ((float) rand()/ (float)(RAND_MAX)) - (float)(rand() & (-n));
         return temp;
    }
}

//Some of the code for this function is from my assignment1
//displays the uncovered board to user
void displayGame(float *grid, int rows, int cols){
//counters used in while loops
int Counter1 = 0;
int Counter2 = 0;
printf("\n");
printf("Displaying the uncovered table...");
printf("\n");

//iterating through the entire board and printing the surprise pack character values based on previously declared floats

while(Counter1 < rows){
    while(Counter2 <  cols){

        //printing "$ " if the current float is 111
        if(*(((grid + Counter1 * cols) + Counter2)) == 111){
            printf("%8s", "$ ");
        }

        //printing "& " if the current float is 222
        else if(*(((grid + Counter1 * cols) + Counter2)) == 222){
            printf("%8s", "& ");
        }

        //printing "! " if the current float is 333
        else if(*(((grid + Counter1 * cols) + Counter2)) == 333){
            printf("%8s", "! ");
        }

        //printing "* " if the current float is 999
        else if(*(((grid + Counter1 * cols) + Counter2)) == 999){
            printf("%8s", "* ");
        }

        //else statement for printing the positive/negative float values
        else{
        printf("%7.2f ", *((grid + Counter1 * cols) + Counter2));
        }
        Counter2++;
    }
    printf("\n");
    Counter1++;
    Counter2 = 0;
} 
}

//initializing the covered game function - fills the entire covered grid with "X"
void initializeCoveredGame (char *coveredGrid, int rows, int cols){
//counters to be used in loops
int Counter1 = 0;
int Counter2 = 0;

//Updating covered grid to an array of "X" which has the size rows x cols
while(Counter1 < rows){
    while(Counter2 <  cols){
            *(((coveredGrid + Counter1 * cols) + Counter2)) = 'X';
            Counter2++;
    }  
 Counter1++;
Counter2 = 0;
}
}

//displayed covered game function - display the covered board to user
void displayCoveredGame(char *coveredGrid, int rows, int cols, int lives, float score, int bombs, int specialChar){
int Counter1 = 0;
int Counter2 = 0;
int Counter3 = 0;

//printing the characters of the current covered grid array
while(Counter1 < rows){
    while(Counter2 <  cols){
        printf("%8c", *((coveredGrid + Counter1 * cols) + Counter2));
        Counter2++;
    }
    printf("\n");
    Counter1++;
    Counter2 = 0;
}
printf("\n");

//checking special char values to determine which surprise packs have been hit by the bomb
// "$" increments specialChar by 1, "&" increments specialChar by 200, "!" increments specialChar by 400
// Printing out only the number of "$" hit by the bomb
if(specialChar > 0 && specialChar <= 125){
    printf("Bang!! Found %d double range multipliers!!\n", specialChar);
}
else if(specialChar > 125 && specialChar <= 325 && specialChar != 200){
    printf("Bang!! Found %d double range multipliers!!\n", specialChar - 200);
}
else if(specialChar > 325 && specialChar <= 525 && specialChar != 400){
    printf("Bang!! Found %d double range multipliers!!\n", specialChar - 400);
}
else if(specialChar > 525 && specialChar <= 725 && specialChar != 600){
    printf("Bang!! Found %d double range multipliers!!\n", specialChar - 600);
}

//printing out the number of lives, score and bombs
if(score < 0){
    printf("Negative score. Lost one life. \n");
}
printf("Lives: %d \n", lives);
printf("Score: %.2f \n", score);
printf("Bombs: %d \n", bombs);
printf("\n");
}

//update covered game function - which updates the covered board every time a new bomb is placed
int updateCoveredGame(float *grid, char *coveredGrid, int rows, int cols, int bombLocationX, int bombLocationY, int specialChar){

//Difference variable which is the number of layers around the bomb to explode (a power of 2).
int difference;
if(specialChar == 0){
    difference = 1;
}
//Ensuring that the value of difference can be computed and the number isn't too large
if(specialChar > 5){
    int counterDifference;
    counterDifference = 0;
    difference = 1;
    while (counterDifference < 5){
         difference *= 2;
        counterDifference++;
    }
}
else{
    int counterDifference;
    counterDifference = 0;
    difference = 1;
    while (counterDifference < specialChar){
         difference *= 2;
        counterDifference++;
    }
}

//variables for to show number of layers around the explosion
int i;
int j;
specialChar = 0;

//initializing value i (lowest row value to be impacted by bomb)
if(bombLocationX - difference >= 0){
    i = bombLocationX - difference;
}
else{
    i = 0;
}

// initializing value j (lowest col value to be impacted by bomb)
if(bombLocationY - difference >= 0){
    j = bombLocationY - difference;
}
else{
    j = 0;
}
//iterating through the layers impacted by bomb and updating the covered board with corresponding characters
// based on the uncovered board values
for(i; i < rows && i <= bombLocationX +difference; i++){
    for(j; j < cols && j <= bombLocationY + difference; j++){

        //if uncovered board value is 111, updates the covered board value to '$'
        if(*((grid + i*cols) +j) == 111){
            *((coveredGrid + i*cols) +j) = '$';
            specialChar++;
            *((grid + i*cols) +j) = 0;
        }

        //else if uncovered board value is 999, updates the covered board value to '*' and increments specialchar by 1000
        else if(*((grid + i*cols) +j) == 999){
            *((coveredGrid + i*cols) +j) = '*';
            *((grid + i*cols) +j) = 0;
            specialChar = specialChar + 1000;
        }

        //else if uncovered board value is 222, updates the covered board value to '&' (life suprise pack) and increments specialchar by 200
        else if(*((grid + i*cols) +j) == 222){
            *((coveredGrid + i*cols) +j) = '&';
            *((grid + i*cols) +j) = 0;
            specialChar = specialChar + 200;
        }

        //else if uncovered board value is 333, updates the covered board value to '!' (double score suprise pack) and increments specialchar by 400
        else if(*((grid + i*cols) +j) == 333){
            *((coveredGrid + i*cols) +j) = '!';
            *((grid + i*cols) +j) = 0;
            specialChar = specialChar + 400;
        }

        //else if uncovered board value is positive, updates the covered board value to '+'
        else if(*((grid + i*cols) +j) > 0){
            *((coveredGrid + i*cols) +j) = '+';
            *((grid + i*cols) +j) = 0;
        }

        //else if uncovered board value is negative, updates the covered board value to '-'
        else if(*((grid + i*cols) +j) < 0){
            *((coveredGrid + i*cols) +j) = '-';
            *((grid + i*cols) +j) = 0;
        }
    }
    //Resetting the j value
    if(bombLocationY - difference >= 0){
    j = bombLocationY - difference;
    }
    else{
        j = 0;
    }
}
//returning the specialChar value
    return specialChar;
}

//Function to calculate the score of the game
float calculateScore(float *grid, char *coveredGrid, int rows, int cols, int bombLocationX, int bombLocationY, int specialChar, float score){
//Difference variable which is the number of layers around the bomb to explode
int difference;

//variables for to show number of layers around the explosion
if(specialChar == 0){
    difference = 1;
}
//Ensuring that the value of difference can be computed and the number isn't too large
if(specialChar > 5){
    int counterDifference;
    counterDifference = 0;
    difference = 1;
    while (counterDifference < 5){
         difference *= 2;
        counterDifference++;
    }
}
else{
    int counterDifference;
    counterDifference = 0;
    difference = 1;
    while (counterDifference < specialChar){
         difference *= 2;
        counterDifference++;
    }
}
int i;
int j;
specialChar = 0;

//initializing value i (lowest row value to be impacted by bomb)
if(bombLocationX - difference >= 0){
    i = bombLocationX - difference;
}
else{
    i = 0;
}

//initializing value j (lowest col value to be impacted by bomb)
if(bombLocationY - difference >= 0){
    j = bombLocationY - difference;
}
else{
    j = 0;
}

//for loop to update the score by iterating through all layers impacted by bomb
for(i; i < rows && i <= bombLocationX +difference; i++){
    for(j; j < cols && j <= bombLocationY + difference; j++){
        //no impact on score if any of the surprise packs are hit
        if(*((grid + i*cols) +j) == 111){
        }
        else if(*((grid + i*cols) +j) == 999){
        }
        else if(*((grid + i*cols) +j) == 222){
        }
        else if(*((grid + i*cols) +j) == 333){
        }
        //incrementing by positive score
        else if(*((grid + i*cols) +j) > 0){
            score = score + *((grid + i*cols) +j);
        }
        //incrementing by negative score
        else if(*((grid + i*cols) +j) < 0){
            score = score + *((grid + i*cols) +j);
        }
    }
    //resetting the j value 
    if(bombLocationY - difference >= 0){
    j = bombLocationY - difference;
    }
    else{
        j = 0;
    }
}
//returning the score
return score;
}

//exit game function to end the game and ask player if they want to quit or see top scores
void exitGame(char *playerName, float score, time_t startTime){
    //endtime variabele used to find out duration of game played
    time_t endTime;
    endTime = time(NULL);

    //variables used as user input
    int quitOrTopScores;
    int numberOfScores;
    
    //variable to ensure user enters a valid integer
    int checkForScan;

    //endtime which stores duration of the game 
    int finalTime = endTime - startTime;

    //opening log file and then calling logScore which stores the player name, score and duration in the log file
    FILE *logFile = fopen("ProjectParta.log", "a+");
    logScore(logFile, playerName,score,finalTime);

    // asking the player if the way to quit or see top scores
    printf("Enter 1 to see top scores or type anything else and press enter to exit the program: ");
    scanf("%d", &quitOrTopScores);

    //if statement for if the user wants to see top scores
    if(quitOrTopScores == 1){
        //asking user for the number of top scores
        printf("Enter the number of top scores you want to see: ");
        checkForScan = scanf("%d", &numberOfScores);
        
        //ensuring user inputs a valid integer
        if(checkForScan != 1){
            printf("Invalid input! Exiting the program.\n");
            exit(0);
        }
        checkForScan = 0;

        // displaying the topscores to the user
        displayTopScores(logFile, numberOfScores);

        //do while loop to keep prompting the user for if they want to quit or see more top scores
        do{
            //asking user if they want to see more top scores or quit
            printf("Enter 1 to see a different number of top scores or type anything else and press enter to exit the program: ");
             scanf("%d", &quitOrTopScores);

            //if statement for if the users wants to see more top scores
            if(quitOrTopScores == 1){
                //asking the user the number of top scores they want to see
                printf("Enter the number of top scores you want to see: ");
                checkForScan = scanf("%d", &numberOfScores);

                //ensuring the user inputs a valid integer
                if(checkForScan != 1){
                    printf("Invalid input! Exiting the program\n");
                    exit(0);
                }
                checkForScan = 0;

                //displaying the top scores to the user
                displayTopScores(logFile, numberOfScores);
            }

            //else statement to close the file and quit otherwise
            else {
                fclose(logFile);
                exit(0);
            }

        }while (quitOrTopScores == 1); //continuing the loop while the user enters 1 as an input
    }

    //else statement to close the file and quit otherwise
    else {
        fclose(logFile);
        exit(0);
    }
}

//log score function to log the score, player name and duration of the game (in seconds) to a log file.
void logScore(FILE *file, char *playerName, float score, int endTime){
fprintf(file, "The score was %.2f.", score);
fprintf(file, "\n");
fprintf(file, "The player's name was %s.", playerName);
fprintf(file, "\n");
fprintf(file, "The duration of the game was %d seconds.", endTime);
fprintf(file, "\n \n");
}


//Function to display the top scores to the user
void displayTopScores(FILE *file, int n){
//rewinding pointer to beginning of file
rewind(file);

//variable for number of lines
int numOFLines;
numOFLines = 0;

//initializing counters to be used in the loops
int counter = 0;
int counter2;
counter2 = 0;

//while loop to count the number of lines in the file
while(!feof(file)){
    counter = fgetc(file);
    if(counter == '\n'){
        numOFLines++;
    }
}

//finding out the number of scores in the file (as each entry has 4 lines)
int numOfScores = (int) (numOFLines/4);

//ensuring the number of top scores asked for is valid
if(n < 0){
    printf("Negative number of top scores is invalid. Quitting program. Please try again with a positive value.\n");
    exit(0);
}
if(n>numOfScores){
    printf("Number of top scores asked for is greater than number of top scores in file. Showing all of top scores in file instead. \n");
    n = numOfScores;
}

//creating arrays which will be used to store the index values of top scores, as well as the scores from the file and their corresponding index.
int topScoresIndex[n];
float scoresFromFile[numOfScores];
int scoresFromFileIndex [numOfScores];


//initializing the index array from 0 through numOfScores -1
for (int i = 0; i < numOfScores; i++){
    scoresFromFileIndex [i] = i;
}

//rewinding the pointer to the beginning of the file
rewind(file);

//storeline stores the line from the file
char storeLine [100];

//counters to be used in loops
int counter3;
int counter4;

//initializing counters to 0
counter3 = 0;
counter4 = 0;

//float rand to hold random value temporarily
float rand;

//char arrays to hold the values read from the file
char holdValue1[50];
char holdValue2[50];
char holdValue3[50];
char holdValue4[50];

//while loop to read every fourth line, which contains the score of each player
while(fgets(storeLine, sizeof storeLine, file) != NULL){
 
    //if statement to check every fourth line and sscanf reads and stores the corresponding values
    if((counter4 - 4 * (counter4/4) == 0)){
    sscanf(storeLine, "%s %s %s %f", holdValue1, holdValue2, holdValue3, &scoresFromFile[counter3]);
    
    counter3++;
    }
    counter4++;
}

//Calling selection sort to sort the scores from file and scores from file's index
selectionSort(scoresFromFile,scoresFromFileIndex, numOfScores);

//counter to be used in loop
int counter5 = 0;

//updating topScores index by the last values of the scoresFromFileIndex
for(int i = numOfScores-1; i > (numOfScores-n-1); i--){
    topScoresIndex[counter5] = scoresFromFileIndex [i];
    counter5++;
}

printf("\n");

//rewinding the file pointer to beginning of file
rewind(file);

//going through the document and getting the playername/duration/score if the index matches the entry and printing corresponding entry
for(int i = 0; i<n; i++){
    for(int j = 0; j < numOFLines; j++){
        //getting the four corresponding lines for the current entry
        fgets(holdValue1, sizeof storeLine, file);
        fgets(holdValue2, sizeof storeLine, file);
        fgets(holdValue3, sizeof storeLine, file);
        fgets(holdValue4, sizeof storeLine, file);

        //printing the entry if the j values matches the current top index
        if(topScoresIndex[i] == j){
            printf("The top score %d, followed by player name and duration:\n", i+1);
            printf("%s",holdValue1);
            printf("%s",holdValue2);
            printf("%s",holdValue3);
            printf("\n");
        }
    }
    //rewinding the pointer to the beginning of the file
    rewind(file);
}
}

// (From assignment 1) selection sort code, which was found online at https://www.geeksforgeeks.org/selection-sort/
//Takes two arrays, one of floats and one of ints, and makes the same changes in both arrays
void selectionSort(float arr[], int arrIndex[], int n) 
{ 
     int i, j, min_idx; 
    //for loops to iterate through the arrays and conduct selection sort on the float array
    for (i = 0; i < n-1; i++) 
    { 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 
  
        swapFloat(&arr[min_idx], &arr[i]);
        swapInteger(&arrIndex[min_idx], &arrIndex[i]); 
    }   
} 

//swap function to swap floats
void swapFloat(float *xp, float *yp) 
{ 
    float temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

//swap function to swap integers
void swapInteger(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 