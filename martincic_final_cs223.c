/* -----------------------------------------------
 Submitted By: John Martincic
 Homework Number: Final_Project
 Credit to:
 
 Mark Sterling --> Allowing me to bouce ideas off of him
 Leo Ghelarducci --> Answering all my questions with the best qestions
 
 Submitted On: December 6, 2016

 By submitting this program with my name,
 I affirm that the creation and modification
 of this program is primarily my own work.
 ------------------------------------------------ */
 /* -----------------------------------------------
 This program will:
 1) Emulate a car racing game
 2) Read a document containing the cars
    2a) Has: Name, type, number, and color
 3) Allow user to pick which car
    3a) Cars cannot be same number
 4) Use RNG for movement
    4a) Cannot be more than 10 spaces
    4b) Track max length is 90 spaces
 5) User Inputs
    5a) car.txt
    5b) Auto/Manual Race
    5c) stop or do another race
 6) Auto mode
    6a) Runs with 4 cars
    6b) Displays locations in relation to other racers
    6c) User provides input for next "roll"
 7) Manual Mode
    7a) 2 Players pick cars
    7b) same as auto mode
 8) Record to file
    8a) Name of file --> Player raceresults.txt
    8b) Name of driver and position
 ------------------------------------------------ */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

//Defining of constants
#define TRACKLENGTH 90
#define MAXMOVE 10
#define MINMOVE 0
#define MAXCHAR 100
#define AUTOCARS 4
#define MANUALCARS 2
#define MINCARS 0
#define CARLIST 4

//Prototyping of structure for car info
struct carStruct
{
    char driverName[MAXCHAR];
    char carType[MAXCHAR];
    int carNumber;
    char carColor[MAXCHAR];
    int distance;
    int place;
}cars[AUTOCARS];

//Prototypes
int fileCheck();
void autoRace();
void manualRace();
int race(struct carStruct[], int racers);
int rngFunc(int x);
void display(int x, struct carStruct[], int i);
void results (struct carStruct[], int racers);
void organizeRacers(struct carStruct[], int racer, int raceStep);
void printResults(struct carStruct[], int racers);


//Main Function for the calling of all other functions
int main(VOID)
{
    int menu, check;
    printf("John Martincic\n");

    //Calls function to check for location of files
    check = fileCheck();
    //Missing file error
    if (check == 1)
    {
        printf("The file car.txt was not found\nPlease check for file and try again\n");
    }
    //File not missing
    else if(check == 0)
    {
        printf("Hello,");
        //do loop for menu display and selection
        do
        {
            printf(" please enter your choice of race. \n");
            printf("1\tAuto Race (1 Player)\n");
            printf("2\tManual Race (2 Player)\n");
            printf("3\tQuit\n");
            scanf("%d", &menu);
            //Switch statement for selection of races
            switch(menu)
            {
                case 1:
                    autoRace();
                    break;
                case 2:
                    manualRace();
                    break;
                case 3:
                    printf("Thank You for playing!\n");
                    break;
                default:
                    printf("That was an invalid entry, please try again\n");
                    break;
            }
        }
        //Will always come back to menu until exit choice is picked
        while(menu != 3);
    }

    return 0;
}

//Function to check for locations of text file
int fileCheck()
{
    //Opens car list for reading
    FILE *cartxt;
    cartxt=fopen("car.txt", "r");

    //If no File is found, this happens
    if (cartxt == NULL)
    {
        return 1;
    }
    //If file found, this happens
    else
    {
        fclose(cartxt);
        return 0;
    }
}

//Function for the auto race
void autoRace()
{
    int i;
    int racers = AUTOCARS;

    //opens car list for reading
    FILE *cartxt;
    cartxt=fopen("car.txt", "r");

    //For loop for populating structure
    for(i=0; i<CARLIST; i++)
    {
        fscanf(cartxt, "%s %s %d %s", cars[i].driverName, cars[i].carType, &cars[i].carNumber, cars[i].carColor);
    }
    //Closes car list file
    fclose(cartxt);
    //Clears the console screen
    system("cls");

    printf("Auto Mode (1 Player) Selected\n");
    //Runs the race than sets result
    race(cars, AUTOCARS);
    //Performs bubble-sort on equation, making sure data is listed in correct order
    results(cars, AUTOCARS);
    //Prints results to file
    printResults(cars, AUTOCARS);
}

//Function for the manual race
void manualRace()
{
    int i, k, l, trap, car, selection;
    int j=0, racers=MANUALCARS;

    //Opens car list for reading
    FILE *cartxt;
    cartxt=fopen("car.txt", "r");


    //For loop for populating structure
    for(i=0; i<CARLIST; i++)
    {
        fscanf(cartxt, "%s %s %d %s", cars[i].driverName, cars[i].carType, &cars[i].carNumber, cars[i].carColor);
    }

    //Clears console screen
    system("cls");


    printf("Manual Mode (2 Player) Selected\n");

    //Do loop for selection of cars
    do
    {
        //Do loop for trapping until proper selection is made
        do
        {
            //Trapping Counter
            trap = 0;
            //For player number
            l=j+1;
            printf("\nPlayer %d, Please select your car.\n\n", l);
            //For loop for printing structure
            for(i=0; i<CARLIST; i++)
            {
                k=i+1;
                printf("%d\t%s %s %d %s\n", k, cars[i].driverName, cars[i].carType, cars[i].carNumber, cars[i].carColor);
            }
            printf("\n");
            //Player's choice, used for switch statement
            scanf("%d", &car);
            //For assigning proper strut to player
            switch(car)
            {
                case 1:
                    printf("You have selected car #%d, the %s %s driven by %s\n", cars[0].carNumber, cars[0].carColor, cars[0].carType, cars[0].driverName);
                    break;
                case 2:
                    printf("You have selected car #%d, the %s %s driven by %s\n", cars[1].carNumber, cars[1].carColor, cars[1].carType, cars[1].driverName);
                    break;
                case 3:
                    printf("You have selected car #%d, the %s %s driven by %s\n", cars[2].carNumber, cars[2].carColor, cars[2].carType, cars[2].driverName);
                    break;
                case 4:
                    printf("You have selected car #%d, the %s %s driven by %s\n", cars[3].carNumber, cars[3].carColor, cars[3].carType, cars[3].driverName);
                    break;
                default:
                    printf("You have selected an incorrect option, please try again.\n");
                    break;
            }
            selection = car-1;
            //Copies players choice of car to the player strut
            cars[j] = cars[selection];
            //If player 2 selects same car as player 1, set trap to redo selection
            if(cars[1].carNumber == cars[0].carNumber && cars[1].carNumber != 0)
            {
                printf("You cannot have the same car as Player 1, please try again.\n");
                trap = 0;
            }
            //If default case is triggered, set trap to redo selection
            else if(car > 4)
            {
                trap = 0;
            }
            //P1 and P2 cars different --> Leave function
            else
            {
                trap = 1;
            }
        }
        //Used to keep player in loop if bad selection
        while(trap != 1);

        //Counter for player car selection loop
        j++;
    }
    //Repeats for proper number of players
    while(j<MANUALCARS);
    //Closes cartxt after reading it
    fclose(cartxt);
    //Runs the race than sets result
    race(cars, j);
    //Performs bubble-sort on equation, making sure data is listed in correct order
    results(cars, racers);
    //Prints results to file
    printResults(cars, racers);
}

//Function for running the race
int race(struct carStruct cars[], int racers)
{
    int i, raceStep = 1, racer, distance;
    int players = AUTOCARS;
    //If 2 player mode, do this
    if(racers == MANUALCARS)
    {
        players = MANUALCARS;
    }
    //Asks user to hit a key to start the race
    printf("Press any key to begin\n\n");
    getch();

    //Resets cars to start line
    for(i=0;i<players;i++)
    {
        cars[i].distance = 0;
        cars[i].place = 0;
    }

    //Manual mode
    if(players != AUTOCARS)
    {
        //Runs until both have crossed finish line
        do
        {
            //Labels the window to show how many steps have occured
            printf("Race Step: %d\n", raceStep);
            //Randomly decides who moves
            racer = rngFunc(players)-1;
            //Randomly figures out how far to move
            cars[racer].distance = cars[racer].distance + rngFunc(MAXMOVE);
            //Resets them to start
            organizeRacers(cars, racer, raceStep);
            //moves the car and updates it on screen
            for (i=0; i<players; i++)
            {
                distance = cars[i].distance;
                display(distance, cars, i);
            }
            raceStep++;
            //Forces player to click button to advance the race
            if (players = MANUALCARS)
            {
                printf("Press [ENTER] to continue\n");
                getchar();
                //Clears Screen
                system("cls");
            }
            printf("\n\n\n");
        }
        while ((cars[0].distance<TRACKLENGTH)||(cars[1].distance<TRACKLENGTH));
    }
    else
    {
        while ((cars[0].distance<TRACKLENGTH)||(cars[1].distance<TRACKLENGTH)||(cars[2].distance<TRACKLENGTH)||(cars[3].distance<TRACKLENGTH))
		{
			//Labels the window to show how many steps have occured
            printf("Race Step: %d\n", raceStep);
            //Randomly decides who moves
            racer = rngFunc(players)-1;
            //Randomly figures out how far to move
            cars[racer].distance = cars[racer].distance + rngFunc(MAXMOVE);
            //Resets them to start
            organizeRacers(cars, racer, raceStep);
            //moves the car and updates it on screen
            for (i=0; i<players; i++)
            {
                distance = cars[i].distance;
                display(distance, cars, i);
            }
            raceStep++;

            Sleep(200);
            //clears screen
            system("cls");

            printf("\n\n\n");
		}
		return players;
    }


}

//Function for RNG Movement
int rngFunc(int x)
{
    //initializes variable for movement
    int randNum;

    //sets seed for random function
    srand(time(NULL));

    //sets randNum to be in boundaries
    randNum=(rand()%x)+1;

    //returns randNum from func
    return randNum;
}

//Prints the race to the console
void display(int distance, struct carStruct displayArray[], int i)
{
    int j = 0;
    //Sets the distance to max if it exceeds max
    if (distance > TRACKLENGTH)
    {
        distance = TRACKLENGTH;
    }
    //Prints car number out for labeling of line
    printf("#%d", displayArray[i].carNumber);
    //Draws stars for the location on track
    for (j = 0; j< distance; j++)
    {
        printf("*");
    }
    printf("\n");
}

//Moves data from cars to results array
void results (struct carStruct cars[], int racers)
{
    int i=0, j=0;
    struct carStruct results;
    //Nested for loop to be sure all data is moved over
    for (i = 0; i < racers; i++)
    {
        for (j = i + 1; j < racers; j++)
        {
            //main bubble-sort equation
            if (cars[i].place > cars[j].place)
            {
                results =  cars[i];
                cars[i] = cars[j];
                cars[j] = results;
            }
        }
    }
}


//Organizes racers according to place
void organizeRacers(struct carStruct organizeArray[], int racer, int raceStep)
{
    //Runs for any racer that passed the finish line
    if(organizeArray[racer].distance >= TRACKLENGTH)
    {
        //Runs if there is a 0 (blank data) in its place
        if(organizeArray[racer].place == 0)
        {
            //Sets the place to the race step number to ensure its on start
            organizeArray[racer].place = raceStep;
        }
    }
}

//Prints result to file
void printResults(struct carStruct cars[], int racers)
{
    int i;
    //Opens the file for writing
    FILE *raceResults;
    raceResults = fopen("raceresults.txt", "w");
    //For loop populates file with data
    for(i=0; i<racers; i++)
    {
        printf("%s is #%d\n", cars[i].driverName, i+1);
        fprintf(raceResults, "%s #%d\n", cars[i].driverName, i+1);
    }
	//Closes file
    fclose(raceResults);
}
