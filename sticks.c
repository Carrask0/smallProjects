/*
 JORGE CARRASCO POLLO - 2021
 */

#include <stdio.h>
#include <string.h>

//SHOWS INTRODUCTORY TEXT
void init(void);

//BEGINS A NEW GAME
void newGame(void);

//SHOWS MENU AND RETURNS OPTION CHOSEN
int menu(void);

//CHECKS IF END GAME POSITION HAS BEEN REACHED
int checkEndGame(char (*)[]);

//GETS A MOVE FROM USER
void getMove(char*);

//CHECKS IF MOVE IS VALID
int checkMove(char*, char(*)[], int*);

//SHOWS STATE OF GAME
void showState(char (*)[]);

//UPDATES STATE
void transMove(char*, char(*)[]);

//DISPLAYS ERROR MESSAGES
void errorHandler(int);

//CHANGES TEXT COLORS
void changeColor(char*);

//CONVERTS CHAR TO INT
int transform(char);

/*-----------------------------------------------------------*/

int main()
{
    init();
    while(1)
    {
        switch(menu())
        {
            case 0:
                changeColor("yellow");
                printf("EXIT...\n");
                changeColor("def");
                return 0;
            case 1:
                newGame();
                break;
        }
    }
}

int menu()
{
    int opt;
    puts("");
    printf("-----------------------------------\n");
    printf("              MENU\n");
    printf("-----------------------------------\n");
    puts("");
    printf("1) NEW GAME\n");
    printf("0) EXIT\n");
    puts("");
    printf("SELECT OPTION: ");
    scanf(" %d", &opt);
    return opt;
}

void newGame()
{
    int error = 0;
    char move[50];
    char state[3][4] =
    {
        {'4', '3', '2', '1'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
    };
    
    while(!checkEndGame(state))
    {
        showState(state);
        do
        {
            errorHandler(error);
            getMove(move);
        }
        while(checkMove(move, state, &error));
        transMove(move, state);
    }
    showState(state);
    printf("CONGRATULATIONS!!\n");
}

int checkEndGame(char (*state)[4])
{
    if(state[2][0] == '4' && state[2][1] == '3' && state[2][2] == '2' && state[2][3] == '1')
    {
        return 1;
    }
    return 0;
}

void getMove(char *move)
{
    puts("");
    printf("INTRODUCE MOVE: ");
    fpurge(stdin);
    scanf(" %s", move);
}

int checkMove(char *move, char(*state)[4], int *error)
{
    int fromIndex, toIndex;
    
    //GETS FROM-INDEX
    for(int i = 3; i >= 0; i--)
    {
        fromIndex = 5;
        if(state[transform(move[0])][i] != ' ')
        {
            fromIndex = transform(state[transform(move[0])][i]);
            break;
        }
    }
    
    //GETS TO-INDEX
    for(int i = 3; i >= 0; i--)
    {
        toIndex = 5;
        if(state[transform(move[1])][i] != ' ')
        {
            toIndex = transform(state[transform(move[1])][i]);
            break;
        }
    }
    
    if (strlen(move) != 2) *error = -1;                                        //MOVE TOO LONG
    else if(move[0] != '0' && move[0] != '1' && move[0] != '2') *error= -2;    //MOVE NOT CORRECT NUMBERS
    else if(move[1] != '0' && move[1] != '1' && move[1] != '2') *error = -2;
    else if(move[0] == move[1]) *error = -3;                                   //SAME COLUMN
    else if(state[transform(move[0])][0] == ' ') *error = -4;                  //EMPTY COLUMN
    else if(fromIndex > toIndex) *error = -5;                                  //BIGGER NUMBER
    else *error = 0;
    return *error;
}

void showState(char (*state)[4])
{
    puts("");
    printf("  0  1  2 \n\n");
    printf("  %c  %c  %c \n"
           "  |  |  | \n"
           "  %c  %c  %c \n"
           "  |  |  | \n"
           "  %c  %c  %c \n"
           "  |  |  | \n"
           "  %c  %c  %c \n",
           state[0][3], state[1][3], state[2][3], state[0][2], state[1][2], state[2][2], state[0][1], state[1][1], state[2][1], state[0][0], state[1][0], state[2][0]);
}

void init(void)
{
    changeColor("blue");
    puts("");
    printf("WELCOME TO STICKS\n");
    printf("YOUR OBJECTIVE IS TO PLACE ALL NUMBERS ON THE LAST COLUMN SO AS THAT NO NUMBER IS PLACED ABOVE A LOWER VALUE NUMBER\nYOU CAN MOVE ONE NUMBER AT A TIME\n");
    printf("THE WAY YOU INTRODUCE A NUMBER IS BY INPUTING TWO NUMBERS TOGETHER, THE FIRST NUMBER BEING THE COLUMN YOU TAKE THE NUMBER FROM AND THE SECOND NUMBER BEING THE COLUMN YOU PUT THE NUMBER INTO\n");
    changeColor("def");
}

void transMove(char *move, char(*state)[4])
{
    int index;
    
    for(int i = 3; i >= 0; i--)
    {
        if(state[transform(move[0])][i] != ' ')
        {
            index = state[transform(move[0])][i];
            state[transform(move[0])][i] = ' ';
            
            for(int j = 3; j >= 0; j--)
            {
                if(state[transform(move[1])][j] != ' ')
                {
                    state[transform(move[1])][j + 1] = index;
                    break;
                }
                else if(j == 0)
                {
                    state[transform(move[1])][j] = index;
                }
            }
            break;
        }
    }
}

void errorHandler(int error)
{
    changeColor("red");
    if(error  == -1)
    {
        printf("MOVE WAS TOO LONG\n");
        printf("PLEASE INTRODUCE ONLY TWO NUMBERS");
    }
    if(error  == -2)
    {
        printf("NUMBERS MUST RANGE FROM 0 TO 2");
    }
    if(error  == -3)
    {
        printf("NUMBERS MUST NOT BE EQUAL");
    }
    if(error  == -4)
    {
        printf("ORIGIN COLUMN IS EMPTY");
    }
    if(error == -5)
    {
        printf("TRYING TO PUT A NUMBER ABOVE A SMALLER NUMBER");
    }
    changeColor("def");
}

void changeColor(char *color)
{
    char red[] = "red";
    char blue[] = "blue";
    char yellow[] = "yellow";
    char def[] = "def";

    if (strcmp(color, red) == 0)
    {
        printf("\e[1;91m");
    }
    else if (strcmp(color, blue) == 0)
    {
        printf("\e[1;94m");
    }
    else if (strcmp(color, def) == 0)
    {
        printf("\x1b[0m");
    }
    else if (strcmp(color, yellow) == 0)
    {
        printf("\033[0;33m");
    }
}

int transform(char move)
{
    return (int)move - 48;
}
