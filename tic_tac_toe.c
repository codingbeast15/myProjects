#include <stdio.h>
#include <stdlib.h>  //for mwmory allocation and process control
#include <ctype.h>  //classify and transform individual characters
#include <time.h>  //defines 4 variable types, 2 macro and various functions for manupulating date and time

char board[3][3];
const char PLAYER='X';
const char COMPUTER='O';

//The Board I am creating is a 2D character array
void resetBoard();
void printBoard();
int checkFreeSpaces(); //if the spaces becomes 0 then the game is over
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main(){
    char winner=' ';
//if winner is empty space then there is no winner
//if PLAYER wins then its X and if COMPUTER wins the its O
    char response;
    do{  //by this the player can prompt to play again
        winner=' ';
        response=' ';
        resetBoard();
        while(winner==' ' && checkFreeSpaces()!=0){
            printBoard();
            playerMove();
            winner=checkWinner();
            if(winner!=' ' || checkFreeSpaces()==0){ //if winner!=' ' then there is a winner
                break; //if the checkfreespaces==0 then i am breaking out of this while loop
            }
            computerMove();
            winner=checkWinner();
            if(winner!=' ' || checkFreeSpaces()==0){ //if winner!=' ' then there is a winner
                break; //if the checkfreespaces==0 then i am breaking out of this while loop
            }
        }
        printBoard();
        printWinner(winner);
        printf("\nWould you like to play again?? (Y/N): ");
        scanf("%c");//clearing the buffer by accepting a character just in case there is a new line character within buffer
        scanf("%c",&response); //accept Y or N after clearing the buffer
        response=toupper(response); /*even if user types lower case character I will still count them
                so converting the whatever characters are input into uppercase characters*/
    }
    while(response=='Y');
    printf("THANKS FOR PLAYING!!");
    return 0;
}

void resetBoard(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            board[i][j]=' '; //when I'll call this function this will give me empty spaces i.e. effectively clearing the board 
        }
    }
}
void printBoard(){
    printf(" %c | %c | %c ",board[0][0],board[0][1],board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ",board[1][0],board[1][1],board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ",board[2][0],board[2][1],board[2][2]);
    printf("\n");           //This will create the Board diagram to play
}
int checkFreeSpaces(){
    int freeSpaces=9;
    for(int i =0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j]!=' '){ //when a player makes a move when one space will decrease
                freeSpaces--; //so I am decrementing the freeSpace by 1
            }
        }
    }
    return freeSpaces; //if I return 0 then there will be no spaces to move by the player
}
void playerMove(){
    int x;
    int y;
    do{
        printf("Enter the row number (1-3): ");
        scanf("%d",&x);
        x--;  /*as I know an array starts with 0 but the user won't know that
                so I am decrementing x by 1 so now it has values from 0 to 2*/ 
        printf("Enter the column number (1-3): ");
        scanf("%d",&y);
        y--;
        if(board[x][y]!=' '){ //it means that particular space is currently occupied by another character
            printf("Invalid Move");
        }else{
            board[x][y]=PLAYER; //setting the sequiel to PLAYER character if the place is empty
            break;
        }
    }
    while(board[x][y]!=' '); //if the space is occupies then it will again go go through this loop
}
void computerMove(){ //creates a seed based on current time as it will generate randomlly
    srand(time(0));
    int x;
    int y;
    if(checkFreeSpaces()>0){ //checks any free spaces available
        do{ //if there are free spaces then it will generate random numbers
            x=rand()%3;
            y=rand()%3;
        }
        while(board[x][y]!=' '); //it will generate random numbers until there are free spaces
        board[x][y]=COMPUTER; //when it finds open spaces setting this sequel to the COMPUTER 
    }else{   //when there no spaces available
        printWinner(' '); //there is no winner i.e. the game is a TIE
    }
}
char checkWinner(){ /*I have to check all winning conditions:
Vertically(Columns) Horizontally(Rows) Diagonally(both left and right type)*/
    //checking Horizontally(Rows)
    for(int i=0; i<3; i++){ //this loop will go throgh all the horizontal ways possible
        if(board[i][0]==board[i][1] && board[i][0]==board[i][2]){
    //I am checking if the Row characters are equal in a horizontal way
        return board[i][0]; //return whatever character is within this spot
        }
    }
    //checking Vertically(Columns)
    for(int i=0; i<3; i++){ //this loop will go throgh all the vertical ways possible
        if(board[0][i]==board[1][i] && board[0][i]==board[2][i]){
    //I am checking if column characters are equal in a vertical way
        return board[0][i]; //return whatever character is within this spot
        }
    }
    //checking Diagonally(Right)
    if(board[0][0]==board[1][1] && board[0][0]==board[2][2]){
    //I am checking if the characters are equal in a right diagonal way
        return board[0][0]; //return whatever character is within this spot
    }
    //checking Diagonally(Left)
    if(board[0][2]==board[1][1] && board[0][3]==board[2][0]){
    //I am checking if the characters are equal in a left diagonal way
        return board[0][2]; //return whatever character is within this spot
    }
    return ' '; //I am returning an empty character if currently there is no winner
}
void printWinner(char winner){
    if(winner==PLAYER){
        printf("YOU WIN!!");
    }else if(winner==COMPUTER){
        printf("YOU LOSE!!");
    }else{
        printf("IT'S A TIE!!");
    }
}