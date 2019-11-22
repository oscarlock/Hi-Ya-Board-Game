/*
~~~~~~~ RULES ~~~~~~~

This AI board game is a game that I created that has the objective of confronting the king to win.
Included in the engine are four pieces that can be moved to try to and defeat the built in AI.

"J" -  The Ninja can move in diagonals. At any moment in time in can move forward in a diagonal movement, but only backwards diagonally to confront a piece.

"j" -  The mini ninja follows the same rules except that it can only move one square per turn.  It contains the same rules that it can move backward in order to confront a piece.

"S" -  The Samurai can move forward at any point and time.  The Samurai can move perpindicular if it is to confront a piece. The Samurai cannot move backwards.

"s" -  The mini samurai has all the same movements as the Samurai except that it can only move one space whether it be forward or perpindicular.

When Samurais or Ninjas are confronted they are demoted to a mini samurai or mini ninja.

When mini samurais or mini ninjas are confronted they are removed from the board.

Rather than landing on the same board placement as the opponents piece to attack/confront the piece you must land in front of the oppoosing piece in the Y axis.

ex   | J | If the Samurai lands in front of the Ninja it will demote to a mini Ninja.  | j |
     | S |  																		   | S |

The Objective is to confront the king.

ex   | K |  This position would give the player with the Samurai a win.
     | S |

*/


/*

~~~~~~ To BEGIN ~~~~~~

1. In order to play and compile the file save this file onto your desktop as "HiYaLock.cpp".

2. Next open your terminal/command prompt and enter into the Desktop directory using the command "cd Desktop"

3. If the file is in your desktop drive enter the command "g++ HiYaLock.cpp -O3" in order to compile the file.

4. Finally enter the command "./a.out"
*/


#include<iostream>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <time.h>
void BoardIn();
void BoardState();
void PlayerMove(int *move);
void validMove(int *move, int Turn, int *Challenger);
void moveGeneration(int Turn, int depth);
int opposedPiece(int Turn, int piece);
void MiniMax(int *move);
int Min(int depth, int alpha, int beta);
int Max(int depth, int alpha, int beta);
int Eval();
void Retract(int *move, int Challenger, int Turn);

//#define MAXDEPTH 8
time_t start;
int board[8][7];
int GenMoves[25][400];
int MoveNum[25];
int CKFlag = 0;
int HKFlag = 0;
int count=0;
int inv;
int MAXDEPTH;

int main(){     
	int lap;
	int Turn = 0;
	int depth = 0;
	int move[4] = {0};
	printf("\n\n\n\n\n\n");
	printf("\n          Welcome, to Hi-Ya!\n");
	printf(" *~*You shall be playing Au|Gusto!*~*\n\n");
	printf("Who would like to play the first move?\n");
	printf("    0 for Au|Gusto - 1 for Human\n\n\n\n\n");
	scanf("%d",&Turn);
	BoardIn();
	while(1){
		BoardState();
		if(Turn == 1){
		printf(" Turn = Human\n");
		}
		if(Turn == 0){printf(" Turn = Au|Gusto");}
		moveGeneration(Turn, depth);
		int i;
    if(Turn == 1){ 
		for(i=0;i< MoveNum[0]*4;i+=2){
			if(i%4==0){printf(" ");}
			 inv = 0;
			printf("%c", GenMoves[0][i]+65);
			 switch(GenMoves[0][i+1]) {
        				case 0:
        				inv = 7;
        				break;
        				case 1:
        				inv = 6;
        				break;
        				case 2:
        				inv = 5;
        				break;
        				case 3:
        				inv = 4;
        				break;
        				case 4:
        				inv = 3;
        				break;
        				case 5:
        				inv = 2;
        				break;
        				case 6:
        				inv = 1;
        				break;
        				case 7:
        				inv = 0;
        				break;
       						}
			printf("%c",char(inv+49));
		}
  }
		printf("\n");
		if(Turn){
			PlayerMove(move); 
			validMove(move, Turn, &lap);
      if(board[0][3] == 0)
        { BoardState();
          printf("Well Played Human, You One\n");
          printf("Game Over\n");
            exit(0);}}
			else{MiniMax(move);
      			if(board[7][3] == 0)
                { BoardState();
                  printf("Well Played CPU, You One\n");
                  printf("Game Over\n");
            exit(0);}}
			Turn = !Turn;
		}
	}
	void MiniMax(int *move)
	{       
		int bestScore = -9999;
		int bestMove[4] = {0};
		int invertBest[4] = {0};
		int KingMe[4] = {0};
		int y,score;
		int Challenger = 0;
		MAXDEPTH = 0;
		start = time(0);
		while(time(0) - start <= 5){
			printf("Depth = %i\n", MAXDEPTH);
		moveGeneration(0,0);
		for(y = 0;y<MoveNum[0]*4;y+=4)
			{   Challenger = 0;
				move[0] = GenMoves[0][y];
				move[1] = GenMoves[0][y+1];
				move[2] = GenMoves[0][y+2];
				move[3] = GenMoves[0][y+3];
				validMove(move, 0, &Challenger);
				score = Min(1, -9999,9999);
				if(move[2] == 3 && move[3] == 6 ){
					KingMe[0] = GenMoves[0][y];
					KingMe[1] = GenMoves[0][y+1];
					KingMe[2] = GenMoves[0][y+2];
					KingMe[3] = GenMoves[0][y+3];
				}
				if(score > bestScore){  
					bestScore = score;
					bestMove[0] = move[0];
					bestMove[1] = move[1];
					bestMove[2] = move[2];
					bestMove[3] = move[3];   
				}
				Retract(move, Challenger, 0);

			}
			MAXDEPTH++;
		}

			//if(board[bestMove[3]+1][bestMove[2]] < 0) {printf("Hi-Ya!\n");}
			if(KingMe[2] == 3 && KingMe[3] == 6)
				{validMove(KingMe, 0, &Challenger);
								switch(KingMe[0]) {
				case 0:
				invertBest[0]=6;
				break;
				case 1:
				invertBest[0]=5;
				break;
				case 2:
				invertBest[0]=4;
				break;
				case 3:
				invertBest[0]=3;
				break;
				case 4:
				invertBest[0]=2;
				break;
				case 5:
				invertBest[0]=1;
				break;
				case 6:
				invertBest[0]=0;
				break;
				
			}
			switch(KingMe[2]) {
				case 0:
				invertBest[2]=6;
				break;
				case 1:
				invertBest[2]=5;
				break;
				case 2:
				invertBest[2]=4;
				break;
				case 3:
				invertBest[2]=3;
				break;
				case 4:
				invertBest[2]=2;
				break;
				case 5:
				invertBest[2]=1;
				break;
				case 6:
				invertBest[2]=0;
				break;
				
			}
			switch(KingMe[1]) {
				case 0:
				invertBest[1]=7;
				break;
				case 1:
				invertBest[1]=6;
				break;
				case 2:
				invertBest[1]=5;
				break;
				case 3:
				invertBest[1]=4;
				break;
				case 4:
				invertBest[1]=3;
				break;
				case 5:
				invertBest[1]=2;
				break;
				case 6:
				invertBest[1]=1;
				break;
				case 7:
				invertBest[1]=0;
				break;
				
			}
			switch(KingMe[3]) {
				case 0:
				invertBest[3]=7;
				break;
				case 1:
				invertBest[3]=6;
				break;
				case 2:
				invertBest[3]=5;
				break;
				case 3:
				invertBest[3]=4;
				break;
				case 4:
				invertBest[3]=3;
				break;
				case 5:
				invertBest[3]=2;
				break;
				case 6:
				invertBest[3]=1;
				break;
				case 7:
				invertBest[3]=0;
				break;
				
			}
			
			printf(" Au|Gusto: %c%c%c%c ", KingMe[0]+65,invertBest[1]+49,KingMe[2]+65,invertBest[3]+49);
			printf("*%c%c%c%c* \n", invertBest[0]+65,KingMe[1]+49,invertBest[2]+65,KingMe[3]+49);
				}
			//else if()
					

			else{
							switch(bestMove[0]) {
				case 0:
				invertBest[0]=6;
				break;
				case 1:
				invertBest[0]=5;
				break;
				case 2:
				invertBest[0]=4;
				break;
				case 3:
				invertBest[0]=3;
				break;
				case 4:
				invertBest[0]=2;
				break;
				case 5:
				invertBest[0]=1;
				break;
				case 6:
				invertBest[0]=0;
				break;
				
			}
			switch(bestMove[2]) {
				case 0:
				invertBest[2]=6;
				break;
				case 1:
				invertBest[2]=5;
				break;
				case 2:
				invertBest[2]=4;
				break;
				case 3:
				invertBest[2]=3;
				break;
				case 4:
				invertBest[2]=2;
				break;
				case 5:
				invertBest[2]=1;
				break;
				case 6:
				invertBest[2]=0;
				break;
				
			}
			switch(bestMove[1]) {
				case 0:
				invertBest[1]=7;
				break;
				case 1:
				invertBest[1]=6;
				break;
				case 2:
				invertBest[1]=5;
				break;
				case 3:
				invertBest[1]=4;
				break;
				case 4:
				invertBest[1]=3;
				break;
				case 5:
				invertBest[1]=2;
				break;
				case 6:
				invertBest[1]=1;
				break;
				case 7:
				invertBest[1]=0;
				break;
				
			}
			switch(bestMove[3]) {
				case 0:
				invertBest[3]=7;
				break;
				case 1:
				invertBest[3]=6;
				break;
				case 2:
				invertBest[3]=5;
				break;
				case 3:
				invertBest[3]=4;
				break;
				case 4:
				invertBest[3]=3;
				break;
				case 5:
				invertBest[3]=2;
				break;
				case 6:
				invertBest[3]=1;
				break;
				case 7:
				invertBest[3]=0;
				break;
				
			}
			if(board[bestMove[3]+1][bestMove[2]] < 0) {printf("Hi-Ya!\n");}
      validMove(bestMove, 0, &Challenger);
      		printf(" Au|Gusto: %c%c%c%c ", bestMove[0]+65,invertBest[1]+49,bestMove[2]+65,invertBest[3]+49);
			printf("*%c%c%c%c* \n", invertBest[0]+65,bestMove[1]+49,invertBest[2]+65,bestMove[3]+49);
  }
			//printf("\n States Evaluated: %i\n\n",count);
			//count = 0;

		}
	void Retract(int *move, int Challenger, int Turn)
	{   board[move[1]][move[0]] = board[move[3]][move[2]];
		board[move[3]][move[2]] = 0;
		if(Turn && Challenger !=0){
			board[move[3]-1][move[2]] = Challenger;}
			else if(!Turn && Challenger != 0){
				board[move[3]+1][move[2]] = Challenger;
			}
		}

		int Min(int depth, int alpha, int beta){
			//count++;
			if(time(0)-start > 5){return -9999;}
			if(depth > MAXDEPTH){ 
				return Eval();
			}
			moveGeneration(1,depth);
			//if(CKFlag){return 1000;}
			//else if(HKFlag){return -1000;}
			//else if(MoveNum[depth] == 0){return 1000;}


				int i,score;
				int Challenger = 0;
				int bestScore = 9999;
				int move[4]= {0};
				for(i=0;i<MoveNum[depth]*4;i+=4){

				  move[0] = GenMoves[depth][i];
				  move[1] = GenMoves[depth][i+1];
				  move[2] = GenMoves[depth][i+2];
				  move[3] = GenMoves[depth][i+3];
				  validMove(move,1,&Challenger);
				 // if(Challenger == -500){ CKFlag=1;}
				  //else if(Challenger == 500){ HKFlag=1;}
				  score = Max(depth+1, alpha, bestScore);
				  if(score < bestScore){
					bestScore = score;
				}
				Retract(move, Challenger, 1);
				//CKFlag=0;
				//HKFlag=0;
				Challenger = 0;
				if(score <= alpha){return bestScore;}
			}
			return bestScore;
		}
	

	int Max(int depth, int alpha, int beta){
	//printf("Searching at depth: %i\n", depth);
	 // count++;
	  if(time(0)-start > 5){return 9999;}
	  if(depth > MAXDEPTH){ 
		return Eval();
	}
	moveGeneration(0,depth);
	//if(CKFlag){return 1000;}
	//else if(HKFlag){return -1000;}
	//else if(MoveNum[depth]==0){return -1000;}
	
		int i,score;
		int Challenger = 0;
		int bestScore = -9999;
		int move[4]= {0};
		for(i=0;i<MoveNum[depth]*4;i+=4){

		  move[0] = GenMoves[depth][i];
		  move[1] = GenMoves[depth][i+1];
		  move[2] = GenMoves[depth][i+2];
		  move[3] = GenMoves[depth][i+3];
		  validMove(move,0,&Challenger);
			//if(Challenger==-500){ CKFlag=1;}
			//else if(Challenger == 500){ HKFlag=1;}

		  score = Min(depth+1,bestScore,beta);
		  if(score > bestScore){
			bestScore = score;
		}
		Retract(move, Challenger, 0);
		Challenger = 0;
		//CKFlag=0;
		//HKFlag=0;
		if(score>=beta){return bestScore;}
	}
	return bestScore;
}


int Eval(){
	int i,j;
	int hold = 0;
	for(int i=0;i<8;i++){
		for(int j=0;j<7;j++){
			hold += board[i][j];
		}


	}
	//Offensive Moves
	//Ninja
if(board[3][0] == 22 && board[4][1] == 0 && board[5][2] == 0 && board[6][3] == 0){hold += 55;}
if(board[3][6] == 22 &&board[4][5] == 0 && board[5][4] == 0 && board[6][3] == 0){hold += 55;}
if(board[4][1] == 22 && board[5][2] == 0 && board[6][3] == 0){hold += 45;}
if(board[4][5] == 22 && board[5][4] == 0 && board[6][3] == 0){hold += 45;}
if(board[5][2] == 22 && board[6][3] == 0){hold += 30;}
if(board[5][4] == 22 && board[6][3] == 0){hold += 30;}
if(board[7][2] == 22 && board[6][3] == 0){hold += 30;}
if(board[7][4] == 22 && board[6][3] == 0){hold += 30;}
	//Samurai

if(board[6][0] == 15 && board[6][1] == 0 && board[6][2] == 0 && board[6][3] == 0){hold += 45;}
if(board[6][6] == 15 && board[6][5] == 0 && board[6][4] == 0 && board[6][3] == 0) {hold += 45;}
if(board[6][1] == 15 && board[6][2] == 0 && board[6][3] == 0){hold += 40;}
if(board[6][5] == 15 && board[6][4] == 0 && board[6][3] == 0) {hold += 40;}
if(board[6][1] == 15 && board[6][2] == 0 && board[6][3] == 0){hold += 35;}
if(board[6][5] == 15 && board[6][4] == 0 && board[6][3] == 0) {hold += 35;}
if(board[6][2] == 15 && board[6][3] == 0){hold += 40;}
if(board[6][4] == 15 && board[6][3] == 0) {hold += 40;}
if(board[1][3] == 15 && board[2][3] == 0 && board[3][3] == 0 && board[4][3] == 0 && board[5][3] == 0 && board[6][3] == 0){hold += 60;}
if(board[2][3] == 15 && board[3][3] == 0 && board[4][3] == 0 && board[5][3] == 0 && board[6][3] == 0){hold += 55;}
if(board[3][3] == 15 && board[4][3] == 0 && board[5][3] == 0 && board[6][3] == 0){hold += 50;}
if(board[4][3] == 15 && board[5][3] == 0 && board[6][3] == 0){hold += 45;}
if(board[5][3] == 15 && board[6][3] == 0){hold += 40;}

//Mini Ninja
if(board[5][2] == 2 && board[6][3] == 0){hold += 70;}
if(board[5][4] == 2 && board[6][3] == 0){hold += 70;}
if(board[7][2] == 2 && board[6][3] == 0){hold += 70;}
if(board[7][4] == 2 && board[6][3] == 0){hold += 70;}

//Mini Samurai
if(board[6][2] == 1 && board[6][3] == 0){hold += 70;}
if(board[6][4] == 1 && board[6][3] == 0){hold += 70;}
if(board[5][3] == 1 && board[6][3] == 0){hold += 70;}

//All In One Case - Offense - Defense
if(board[6][3] == 15 || 22 || 1 || 2){hold += 500;}
if(board[1][3] == -15 || -22 || -1 || -2){hold -= 1000;}
if(board[1][3] != -15 || -22 || -1 || -2){hold += 500;}

//Defensive Case
	//Ninja
if(board[4][0] == -22 && board[3][1] == 0 && board[2][2] == 0 && board[1][3] == 0){hold -= 175;}
if(board[4][6] == -22 &&board[3][5] == 0 && board[2][4] == 0 && board[1][3] == 0){hold -= 175;}
if(board[3][1] == -22 && board[2][2] == 0 && board[1][3] == 0){hold -= 155;}
if(board[3][5] == -22 && board[2][4] == 0 && board[1][3] == 0){hold -= 155;}
if(board[2][2] == -22 && board[1][3] == 0){hold -= 100;}
if(board[2][4] == -22 && board[1][3] == 0){hold -= 100;}

	//Samurai

if(board[1][0] == -15 && board[1][1] == 0 && board[1][2] == 0 && board[1][3] == 0){hold -= 175;}
if(board[1][6] == -15 && board[1][5] == 0 && board[1][4] == 0 && board[1][3] == 0) {hold -= 175;}
if(board[1][1] == -15 && board[1][2] == 0 && board[1][3] == 0){hold -= 165;}
if(board[1][5] == -15 && board[1][4] == 0 && board[1][3] == 0) {hold -= 165;}
if(board[1][1] == -15 && board[1][2] == 0 && board[1][3] == 0){hold -= 165;}
if(board[1][5] == -15 && board[1][4] == 0 && board[1][3] == 0) {hold -= 165;}
if(board[1][2] == -15 && board[1][3] == 0){hold -= 155;}
if(board[1][4] == -15 && board[1][3] == 0) {hold -= 155;}
if(board[6][3] == -15 && board[5][3] == 0 && board[4][3] == 0 && board[3][3] == 0 && board[2][3] == 0 && board[1][3] == 0){hold -= 165;}
if(board[5][3] == -15 && board[4][3] == 0 && board[3][3] == 0 && board[2][3] == 0 && board[1][3] == 0){hold -=155;}
if(board[4][3] == -15 && board[3][3] == 0 && board[2][3] == 0 && board[1][3] == 0){hold -= 1155;}
if(board[3][3] == -15 && board[2][3] == 0 && board[1][3] == 0){hold -= 155;}
if(board[2][3] == -15 && board[1][3] == 0){hold -= 155;}

//Mini Ninja
if(board[2][2] == -2 && board[1][3] == 0){hold -= 150;}
if(board[2][4] == -2 && board[1][3] == 0){hold -= 150;}
if(board[0][2] == -2 && board[1][3] == 0){hold -= 150;}
if(board[0][4] == -2 && board[1][3] == 0){hold -= 150;}
if(board[3][1] == -2 && board[1][3] == 0 && board[2][2] == 0){hold -= 150;}
if(board[3][5] == -2 && board[1][3] == 0 && board[2][4] == 0){hold -= 150;}

//Mini Samurai
if(board[1][2] == -1 && board[1][3] == 0){hold -= 150;}
if(board[1][4] == -1 && board[1][3] == 0){hold -= 150;}
if(board[2][3] == -1 && board[1][3] == 0){hold -= 150;}


	return hold;
}


void BoardIn(){
	int i, j;
	for(i = 0; i<8; i++){
		for(j = 0;j<7;j++){
			board[i][j] = 0;
		}
	}


								//CPU board pieces - 0

								board[0][3] = 1500; //King
								board[1][0] = 22; //Ninja
								board[1][1] = 22; //
								board[1][2] = 22; //
								board[1][4] = 15; //Samurai
								board[1][5] = 15; //
								board[1][6] = 15; //
								
								board[2][0] = 1; //Mini Samurai
								board[2][1] = 1; //
								board[2][2] = 1; //
								board[2][4] = 2; //Mini Ninja
								board[2][5] = 2; //
								board[2][6] = 2; //

								
								//Human board pieces - 1
								
								board[7][3] = -1500; //King
								board[6][0] = -15; //Samurai
								board[6][1] = -15; //
								board[6][2] = -15; //
								board[6][4] = -22; //Ninja
								board[6][5] = -22; //
								board[6][6] = -22; //

								board[5][0] = -2; //Mini Ninja
								board[5][1] = -2; //
								board[5][2] = -2; //
								board[5][4] = -1; //Mini Samurai
								board[5][5] = -1; //
								board[5][6] = -1; //



							}

							void BoardState(){
								int i,j;
								for(i = 0; i<8; i++){
									printf("%i ", 8 - i);
									for(j = 0; j<7; j++){
										if((i%2 == 0 && j%2==0) || (i%2==1 && j%2==1)){printf("\x1b[48;5;130m");}
										switch(board[i][j]) {
											case 1500:
											printf(" \x1b[38;5;197;1mK \x1b[0m");
											break;
											case 22:
											printf(" \x1b[38;5;197;1mJ \x1b[0m");
											break;
											case 15:
											printf(" \x1b[38;5;197;1mS \x1b[0m");
											break;
											case 2:
											printf(" \x1b[38;5;197;1mj \x1b[0m");
											break;
											case 1:
											printf(" \x1b[38;5;197;1ms \x1b[0m");
											break;
											case -1:
											printf(" \x1b[70;1ms \x1b[0m");
											break;
											case -2:
											printf(" \x1b[70;1mj \x1b[0m");
											break;
											case -15:
											printf(" \x1b[70;1mS \x1b[0m");
											break;
											case -22:
											printf(" \x1b[70;1mJ \x1b[0m");
											break;
											case -1500:
											printf(" \x1b[70;1mK \x1b[0m");
											break;
											default:
											printf("   \x1b[0m");
										}
									}
									printf("\n");
								}
								printf("  ");
								for(i = 0; i <7; i++) {
									char c = 'A';
									printf(" %c ", c +i);
								}
								printf("\n");
							}



							void PlayerMove(int *move){
								char hold[5] = {' '};
								int rain[5] = {0};
								/*move[0]= ' ';
								move[1]= ' ';
								move[2]= ' ';
								move[3]= ' ';*/
								int valid = 0;
								while(valid !=1){
									scanf("%4s", hold);
							        switch(hold[1]) {
        									case 49:
        									//hold[1] = 49;
        									rain[1] = 7;
        									break;
        									case 50:
        									rain[1] = 6;
        									break;
        									case 51:
        									rain[1] = 5;
        									break;
        									case 52:
        									rain[1] = 4;
        									break;
        									case 53:
        									rain[1] = 3;
        									break;
        									case 54:
        									rain[1] = 2;
        									break;
        									case 55:
        									rain[1] = 1;
        									break;
        									case 56:
        									rain[1] = 0;
        									break;
       										}
       										    switch(hold[3]) {
        									case 49:
        									rain[3] = 7;
        									break;
        									case 50:
        									rain[3] = 6;
        									break;
        									case 51:
        									rain[3] = 5;
        									break;
        									case 52:
        									rain[3] = 4;
        									break;
        									case 53:
        									rain[3] = 3;
        									break;
        									case 54:
        									rain[3] = 2;
        									break;
        									case 55:
        									rain[3] = 1;
        									break;
        									case 56:
        									rain[3] = 0;
        									break;
       										}

									if(hold[0] >= 'A' && hold[0] <= 'G') {
										move[0] = (int)hold[0]-65;}
										else{   
											move[0] = (int)hold[0]-97;
										}
										move[1] = rain[1];
										if(move[2] >= 'A' && move[2] <= 'G') {
											move[2] = (int)hold[2]- 65;}
											else{
												move[2] = (int)hold[2]-97;}
												move[3] = rain[3];


										//move[0] = (int)hold[0]-65;
										//move[1] = (int)hold[1]-49;
										//move[2] = (int)hold[2]-65;
										//move[3] = (int)hold[3]-49;
												int y = 0;
												while(y<MoveNum[0]*4){
								   /* if(((move[0] >= 'A' && move[0] <= 'G') && (move[1] >= '1' && move[1] <= '8') && (move[2] >= 'A' && move[2] <= 'G') && (move[3] >= '1' && move[3] <= '8')))
										{valid = 1;}*/
												  if(GenMoves[0][y] == move[0] && GenMoves[0][y+1] == move[1] && GenMoves[0][y+2] == move[2] && GenMoves[0][y+3] == move[3])  
													{valid = 1;}
												y+=4;
											}
											if(!valid) {printf("Move input is incorrect.\n");
											valid = 0;}
										}
										
									}



									void validMove(int *move, int Turn, int *Challenger){
									/*if(move[0] >= 'A' && move[0] <= 'G') {
									move[0] -= 65;}
									else{   
										move[0] -= 97;
									}
									move[1] -= 49;
									if(move[2] >= 'A' && move[2] <= 'G') {
										move[2] -= 65;}
										else{
											move[2] -= 97;}
											move[3] -= 49;*/
										

										board[(int)move[3]][(int)move[2]] = board[(int)move[1]][(int)move[0]];
										board[(int)move[1]][(int)move[0]] = 0;

										if(Turn && (int)move[3] > 0 &&
											opposedPiece(Turn, board[(int)move[3]-1][(int)move[2]]))

											{switch(board[(int)move[3]-1][(int)move[2]]){
												case 1500:
												board[(int)move[3]-1][(int)move[2]] = 0;
													//printf("With the Super Hi-Ya!\n");
													//printf("Well Done Human, the game is over.\n");
												*Challenger =1500;
													//exit(0);
												break;
												case 22:
												board[(int)move[3]-1][(int)move[2]] = 2;
													//printf("Hi-Ya!\n");
												*Challenger =22;
												break;
												case 15:
												board[(int)move[3]-1][(int)move[2]] = 1;
												*Challenger =15;
													//printf("Hi-Ya!\n");
												break;
												case 2:
												board[(int)move[3]-1][(int)move[2]] = 0;
												*Challenger =2;
													//printf("Hi-Ya!\n");
												break;
												case 1:
												board[(int)move[3]-1][(int)move[2]] = 0;
												*Challenger =1;
													//printf("Hi-Ya!\n");
												break;
												default:
												*Challenger = 0;
											}}
											else if (!Turn && (int)move[3] < 7 && 
												opposedPiece(Turn,board[(int)move[3]+1][(int)move[2]])){
												switch(board[(int)move[3]+1][(int)move[2]])
											{
												case -1500:
												board[(int)move[3]+1][(int)move[2]] = 0;
													//printf("With the Super Hi-Ya!\n");
													//printf("Well Done CPU, the game is over. \n");
												*Challenger =-1500;
													//exit(0);
												break;
												case -22:
												board[(int)move[3]+1][(int)move[2]] = -2;
													//printf("Hi-Ya!\n");
												*Challenger =-22;
												break;
												case -15:
												board[(int)move[3]+1][(int)move[2]] = -1;
													//printf("Hi-Ya!\n");
												*Challenger =-15;
												break;
												case -2:
												board[(int)move[3]+1][(int)move[2]] = 0;
													//printf("Hi-Ya!\n");
												*Challenger =-2;
												break;
												case -1:
												board[(int)move[3]+1][(int)move[2]] = 0;
													//printf("Hi-Ya!\n");
												*Challenger =-1;
												break;
												default:
												*Challenger = 0;


											}
										}
									}

									int opposedPiece(int Turn, int piece) {
										if((Turn && piece > 0) || (!Turn && piece < 0)){
											return 1;
										}
										return 0;
									}

									void moveGeneration( int Turn, int depth)
									{
										//int m1,m2,m3,m4; // move values
										//int mX, mY; //value differences m5 = 
											//int i,j;
										int g = 0;
										if(Turn == 0){  
											for(int i = 0; i<8; i++){
												for(int j = 0;j<7;j++){

													if(board[i][j] > 0)
													{  
														switch(board[i][j]){
															case 0:
															break;
															case 1500:
															break;
															case 22:
															{
																int Ji = 1;
																int Jj = 1;
																   // printf("Ninja moves\n");

																while((i + Ji >= 0 && i+Ji <= 7) && (j +Jj >= 0 && j+Jj <6) && (board[i+Ji][j+Jj] == 0) && (board[i+Ji][j+Jj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
																		{//printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+Jj+65),char(i+Ji+49));
																	GenMoves[depth][g*4] = j;
																	GenMoves[depth][g*4+1] = i;
																	GenMoves[depth][g*4+2] = j+Jj;
																	GenMoves[depth][g*4+3] = i+Ji;
																	g++;    
																	Jj++;
																	Ji++;
																}
																Ji = 1;
																Jj = -1;

																while((i + Ji >= 0 && i+Ji <= 7) && (j +Jj >= 0 && j+Jj <=6) && (board[i+Ji][j+Jj] == 0) && (board[i+Ji][j+Jj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
																	{ //printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+Jj+65),char(i+Ji+49));
																GenMoves[depth][g*4] = j;
																GenMoves[depth][g*4+1] = i;
																GenMoves[depth][g*4+2] = j+Jj;
																GenMoves[depth][g*4+3] = i+Ji;
																g++;  
																Jj--;
																Ji++;
															}
															Ji = -1;
															Jj = 1;
															while((i + Ji >= 0 && i+Ji <= 7) && (j +Jj >= 0 && j+Jj <=6) && (board[i+Ji][j+Jj] == 0) && (board[i+Ji][j+Jj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
															{
																if(board[i+Ji+1][j+Jj] == 0)
																	{ }
															else if(board[i+Ji+1][j+Jj] < 0)// (1||2||3||4||5))
																{//printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+Jj+65),char(i+Ji+49));
															GenMoves[depth][g*4] = j;
															GenMoves[depth][g*4+1] = i;
															GenMoves[depth][g*4+2] = j+Jj;
															GenMoves[depth][g*4+3] = i+Ji;
															g++;  
														}
														Ji--;
														Jj++;
													}
													Ji = -1;
													Jj= -1;
													while((i + Ji >= 0 && i+Ji <= 7) && (j +Jj >= 0 && j+Jj <=6) && (board[i+Ji][j+Jj] == 0) && (board[i+Ji][j+Jj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
													{
														if(board[i+Ji+1][j+Jj] ==0)
															{ }
															else if(board[i+Ji+1][j+Jj] < 0)// (1||2||3||4||5))
																{ //printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+Jj+65),char(i+Ji+49));
															GenMoves[depth][g*4] = j;
															GenMoves[depth][g*4+1] = i;
															GenMoves[depth][g*4+2] = j+Jj;
															GenMoves[depth][g*4+3] = i+Ji;
															g++;  }
															Ji--;
															Jj--;
														}
														//printf("\n");
														break;
													}
													case 15:
													{
														int Si = 1;
														int Sj = 0;
													   // printf("Samurai Moves\n");

														while((i + Si >= 0 && i + Si <= 7) &&(j +Sj <= 6 && j + Sj >= 0) && (board[i+Si][j] == 0) && (board[i+Si][j] != 1||2||3||4||5||-1||-2||-3||-4||-5))
															{ //printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+65),char(i+Si+49));
														GenMoves[depth][g*4] = j;
														GenMoves[depth][g*4+1] = i;
														GenMoves[depth][g*4+2] = j;
														GenMoves[depth][g*4+3] = i+Si;
														g++;  

														Si++;      
													}
													Sj = -1;
													Si =0;

													while((i + Si >= 0 && i + Si <= 7) &&(j +Sj <= 6 && j + Sj >= 0) && (board[i][j+Sj] == 0) && (board[i][j+Sj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
													{ 
														if(board[i+1][j+Sj] == 0)
															{ }
														else if(board[i+1][j+Sj] < 0)// (1||2||3||4||5))
															{//printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+Sj+65),char(i+49));
														GenMoves[depth][g*4] = j;
														GenMoves[depth][g*4+1] = i;
														GenMoves[depth][g*4+2] = j+Sj;
														GenMoves[depth][g*4+3] = i;
														g++;  
													}
													Sj--;

												}

												Sj = 1;
												while((i + Si >= 0 && i + Si <= 7) &&(j +Sj <= 6 && j + Sj >= 0) && (board[i][j+Sj] == 0) && (board[i][j+Sj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
												{
													if(board[i+1][j+Sj] == 0)
														{ }
														else if(board[i+1][j+Sj] < 0)// (1||2||3||4||5))
															{//printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+Sj+65),char(i+49));

														GenMoves[depth][g*4] = j;
														GenMoves[depth][g*4+1] = i;
														GenMoves[depth][g*4+2] = j+Sj;
														GenMoves[depth][g*4+3] = i;
														g++;}
														Sj++;
													}
													//printf("\n");
													break;
												}

												case 2:
												{
													int mJi = 1;
													int mJj = 1;
													//printf("Mini Ninja Moves\n");
													if((i + mJi >= 0 && i+mJi <= 7) && (j +mJj >= 0 && j+mJj <=6) && (board[i+mJi][j+mJj] == 0) && (board[i+mJi][j+mJj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
														{               //printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+mJj+65),char(i+mJi+49));
													GenMoves[depth][g*4] = j;
													GenMoves[depth][g*4+1] = i;
													GenMoves[depth][g*4+2] = j+mJj;
													GenMoves[depth][g*4+3] = i+mJi;
													g++;
												}
												mJi = 1;
												mJj = -1;

												if((i + mJi >= 0 && i+mJi <= 7) && (j +mJj >= 0 && j+mJj <=6) && (board[i+mJi][j+mJj] == 0) && (board[i+mJi][j+mJj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
													{ //printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+mJj+65),char(i+mJi+49));
												GenMoves[depth][g*4] = j;
												GenMoves[depth][g*4+1] = i;
												GenMoves[depth][g*4+2] = j+mJj;
												GenMoves[depth][g*4+3] = i+mJi;
												g++;
											}
											mJi = -1;
											mJj = 1;
											if((i + mJi >= 0 && i+mJi <= 7) && (j +mJj >= 0 && j+mJj <=6) && (board[i+mJi][j+mJj] == 0) && (board[i+mJi][j+mJj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
											{
												if(board[i+mJi+1][j+mJj] == 0)
													{ }
												else if(board[i+mJi+1][j+mJj] < 0)// (1||2||3||4||5))
													{//printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+mJj+65),char(i+mJi+49));
												GenMoves[depth][g*4] = j;
												GenMoves[depth][g*4+1] = i;
												GenMoves[depth][g*4+2] = j+mJj;
												GenMoves[depth][g*4+3] = i+mJi;
												g++;
											}
										}
										mJi = -1;
										mJj= -1;
										if((i + mJi >= 0 && i+mJi <= 7) && (j +mJj >= 0 && j+mJj <=6) && (board[i+mJi][j+mJj] == 0) && (board[i+mJi][j+mJj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
										{
											if(board[i+mJi+1][j+mJj] ==0)
												{ }
												else if(board[i+mJi+1][j+mJj] < 0)// (1||2||3||4||5))
													{//printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+mJj+65),char(i+mJi+49));
												GenMoves[depth][g*4] = j;
												GenMoves[depth][g*4+1] = i;
												GenMoves[depth][g*4+2] = j+mJj;
												GenMoves[depth][g*4+3] = i+mJi;
												g++;
											}
										}   

											//printf("\n");
										break;
									}

									case 1:
									{
										int mSi = 1;
										int mSj = 0;
											//printf("Mini Samurai Moves\n");

										if((i + mSi >= 0 && i+mSi <= 7) && (j +mSj >= 0 && j+mSj <=6) && (board[i+mSi][j] == 0) && (board[i+mSi][j] != 1||2||3||4||5||-1||-2||-3||-4||-5))
												{ //printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+65),char(i+mSi+49)); 
											GenMoves[depth][g*4] = j;
											GenMoves[depth][g*4+1] = i;
											GenMoves[depth][g*4+2] = j;
											GenMoves[depth][g*4+3] = i+mSi;
											g++;
										}

										mSj = -1;
										mSi = 0;
										if((i + mSi >= 0 && i+mSi <= 7) && (j +mSj >= 0 && j+mSj <=6) && (board[i][j+mSj] == 0) && (board[i][j+mSj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
										{ 
											if(board[i+1][j+mSj] == 0)
												{ }
												else if(board[i+1][j+mSj] < 0)// (1||2||3||4||5))
													{//printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+mSj+65),char(i+49));
												GenMoves[depth][g*4] = j;
												GenMoves[depth][g*4+1] = i;
												GenMoves[depth][g*4+2] = j+mSj;
												GenMoves[depth][g*4+3] = i;
												g++;
											}

										}

										mSj = 1;

										if((i + mSi >= 0 && i+mSi <= 7) && (j +mSj >= 0 && j+mSj <=6) && (board[i][j+mSj] == 0) && (board[i][j+mSj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
										{
											if(board[i+1][j+mSj] == 0)
												{ }
												else if(board[i+1][j+mSj] < 0)// (1||2||3||4||5))
													{//printf("%c%c%c%c ",char(j+65) ,char(i+49), char(j+mSj+65),char(i+49));
												GenMoves[depth][g*4] = j;
												GenMoves[depth][g*4+1] = i;
												GenMoves[depth][g*4+2] = j+mSj;
												GenMoves[depth][g*4+3] = i;
												g++;
											}

										}
											//printf("\n");
										break;
									}
								}
							}
						}
					}
				}
				

				if(Turn == 1){
					for(int a = 0; a<=7; a++){
						for(int b = 0; b<=6;b++){ 
							if(board[a][b] < 0){
								switch(board[a][b]){
									case 0:
									break;
									case -1500:
									break;
									case -22:
									{
										int Ji = -1;
										int Jj = -1;
											//printf("Ninja moves\n");

										while((a + Ji >= 0 && a+Ji <= 7) &&(b +Jj >= 0 && b+Jj <= 6) && (board[a+Ji][b+Jj] == 0) && (board[a+Ji][b+Jj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
												{ //printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+Jj+65),char(a+Ji+49));
											GenMoves[depth][g*4] = b;
											GenMoves[depth][g*4+1] = a;
											GenMoves[depth][g*4+2] = b+Jj;
											GenMoves[depth][g*4+3] = a+Ji;
											g++;
											Jj--;
											Ji--;
										}
										Ji = -1;
										Jj = 1;

										while((a + Ji >= 0 && a+Ji <= 7) &&(b +Jj >= 0 && b+Jj <= 6) && (board[a+Ji][b+Jj] == 0) && (board[a+Ji][b+Jj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
											{ //printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+Jj+65),char(a+Ji+49));
										GenMoves[depth][g*4] = b;
										GenMoves[depth][g*4+1] = a;
										GenMoves[depth][g*4+2] = b+Jj;
										GenMoves[depth][g*4+3] = a+Ji;
										g++;
										Jj++;
										Ji--;
									}
									Ji = 1;
									Jj = -1;
									while((a + Ji >= 0 && a+Ji <= 7) &&(b +Jj >= 0 && b+Jj <= 6) && (board[a+Ji][b+Jj] == 0) && (board[a+Ji][b+Jj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
									{
										if(board[a+Ji-1][b+Jj] == 0)
											{ }
													else if(board[a+Ji-1][b+Jj] > 0)// ((-1)||(-2)||(-3)||(-4)||(-5)))
													 {//printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+Jj+65),char(a+Ji+49));
												 GenMoves[depth][g*4] = b;
												 GenMoves[depth][g*4+1] = a;
												 GenMoves[depth][g*4+2] = b+Jj;
												 GenMoves[depth][g*4+3] = a+Ji;
												 g++;
											 }
											 Ji++;
											 Jj--;
										 }
										 Ji = 1;
										 Jj= 1;
										 while((a + Ji >= 0 && a+Ji <= 7) &&(b +Jj >= 0 && b+Jj <= 6) && (board[a+Ji][b+Jj] == 0) && (board[a+Ji][b+Jj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
										 {
											if(board[a+Ji-1][b+Jj] == 0)
												{ }
										else if(board[a+Ji-1][b+Jj] > 0)// ((-1)||(-2)||(-3)||(-4)||(-5)))
											{//printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+Jj+65),char(a+Ji+49));
										GenMoves[depth][g*4] = b;
										GenMoves[depth][g*4+1] = a;
										GenMoves[depth][g*4+2] = b+Jj;
										GenMoves[depth][g*4+3] = a+Ji;
										g++;
									}
									Ji++;
									Jj++;
								}
									//printf("\n");
								break;
							}
							case -15:
							{
								int Si = -1;
								int Sj = 0;
									//printf("Samurai Moves\n");
								while((a + Si >= 0 && a + Si <=7) &&(b +Sj >= 0 && b + Sj <= 6) && (board[a+Si][b] == 0) && (board[a+Si][b] != 1||2||3||4||5||-1||-2||-3||-4||-5))

										{ //printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+65),char(a+Si+49));
									GenMoves[depth][g*4] = b;
									GenMoves[depth][g*4+1] = a;
									GenMoves[depth][g*4+2] = b;
									GenMoves[depth][g*4+3] = a+Si;
									g++;
									Si--;
								}

								Sj = 1;
								Si = 0;
								while((a + Si >= 0 && a + Si <=7) &&(b +Sj >= 0 && b + Sj <= 6) && (board[a][b+Sj] == 0) && (board[a][b+Sj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
								{ 
									if(board[a-1][b+Sj] == 0)
										{ }
									else if(board[a-1][b+Sj] > 0)// 1||2||3||4||5)
										{//printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+Sj+65),char(a+49));
									GenMoves[depth][g*4] = b;
									GenMoves[depth][g*4+1] = a;
									GenMoves[depth][g*4+2] = b+Sj;
									GenMoves[depth][g*4+3] = a+Si;
									g++;
								}
								Sj++;

							}
							Si = 0;
							Sj = -1;
							while((a + Si >= 0 && a + Si <=7) &&(b +Sj >= 0 && b + Sj <= 6) && (board[a][b+Sj] == 0) && (board[a][b+Sj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
							{
								if(board[a-1][b+Sj] == 0)
									{ }
									else if(board[a-1][b+Sj] > 0)// 1||2||3||4||5)
										{//printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+Sj+65),char(a+49));
									GenMoves[depth][g*4] = b;
									GenMoves[depth][g*4+1] = a;
									GenMoves[depth][g*4+2] = b+Sj;
									GenMoves[depth][g*4+3] = a;
									g++;
								}

								Sj--;
							}
								//printf("\n");
							break;
						}
						case -2:
						{
							int mJi = -1;
							int mJj = -1;
								//printf("Mini Ninja Moves\n");
							if((a + mJi >= 0 && a+mJi <= 7) && (b +mJj >= 0 && b+mJj <=6) && (board[a+mJi][b+mJj] == 0) && (board[a+mJi][b+mJj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
									{// printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+mJj+65),char(a+mJi+49));
								GenMoves[depth][g*4] = b;
								GenMoves[depth][g*4+1] = a;
								GenMoves[depth][g*4+2] = b+mJj;
								GenMoves[depth][g*4+3] = a+mJi;
								g++;
							}
							mJi = -1;
							mJj = 1;

							if((a + mJi >= 0 && a+mJi <= 7) && (b +mJj >= 0 && b+mJj <=6) && (board[a+mJi][b+mJj] == 0) && (board[a+mJi][b+mJj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
								{// printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+mJj+65),char(a+mJi+49));
							GenMoves[depth][g*4] = b;
							GenMoves[depth][g*4+1] = a;
							GenMoves[depth][g*4+2] = b+mJj;
							GenMoves[depth][g*4+3] = a+mJi;
							g++;

						}
						mJi = 1;
						mJj = -1;
						if((a + mJi >= 0 && a+mJi <= 7) && (b +mJj >= 0 && b+mJj <=6) && (board[a+mJi][b+mJj] == 0) && (board[a+mJi][b+mJj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
						{
							if(board[a+mJi-1][b+mJj] == 0)
								{ }
							else if(board[a+mJi-1][b+mJj] > 0)// == 1||2||3||4||5)
								{//printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+mJj+65),char(a+mJi+49));
							GenMoves[depth][g*4] = b;
							GenMoves[depth][g*4+1] = a;
							GenMoves[depth][g*4+2] = b+mJj;
							GenMoves[depth][g*4+3] = a+mJi;
							g++;
						}
					}
					mJi = 1;
					mJj= 1;
					if((a + mJi >= 0 && a+mJi <= 7) && (b +mJj >= 0 && b+mJj <=6) && (board[a+mJi][b+mJj] == 0) && (board[a+mJi][b+mJj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
					{
						if(board[a+mJi-1][b+mJj] ==0)
							{ }
							else if(board[a+mJi-1][b+mJj] > 0)//== 1||2||3||4||5)
								{// printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+mJj+65),char(a+mJi+49));
							GenMoves[depth][g*4] = b;
							GenMoves[depth][g*4+1] = a;
							GenMoves[depth][g*4+2] = b+mJj;
							GenMoves[depth][g*4+3] = a+mJi;
							g++;
						}
					}   

						//printf("\n");
					break;
				}
				case -1:
				{
					int mSi = -1;
					int mSj = 0;
						//printf("Mini Samurai Moves\n");

					if((a + mSi >= 0 && a+mSi <= 7) && (b +mSj >= 0 && b+mSj <=6) && (board[a+mSi][b] == 0) && (board[a+mSi][b] != 1||2||3||4||5||-1||-2||-3||-4||-5))
			   // if( j+Jj == 8)
							{ //printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+65),char(a+mSi+49));
						GenMoves[depth][g*4] = b;
						GenMoves[depth][g*4+1] = a;
						GenMoves[depth][g*4+2] = b;
						GenMoves[depth][g*4+3] = a+mSi;
						g++;
					}
					mSi = 0;
					mSj = 1;

					if((a + mSi >= 0 && a+mSi <= 7) && (b +mSj >= 0 && b+mSj <=6) && (board[a][b+mSj] == 0) && (board[a][b+mSj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
					{ 
						if(board[a-1][b+mSj] == 0)
							{ }
						else if(board[a-1][b+mSj] > 0) //== 1||2||3||4||5)
							{//printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+mSj+65),char(a+49));
						GenMoves[depth][g*4] = b;
						GenMoves[depth][g*4+1] = a;
						GenMoves[depth][g*4+2] = b+mSj;
						GenMoves[depth][g*4+3] = a;
						g++;
					}
				}

				mSj = -1;


				if((a + mSi >= 0 && a+mSi <= 7) && (b +mSj >= 0 && b+mSj <=6) && (board[a][b+mSj] == 0) && (board[a][b+mSj] != 1||2||3||4||5||-1||-2||-3||-4||-5))
				{
					if(board[a-1][b+mSj] == 0)
						{ }
						else if(board[a-1][b+mSj] > 0)// == 1||2||3||4||5)
							{//printf("%c%c%c%c ",char(b+65) ,char(a+49), char(b+mSj+65),char(a+49));
						GenMoves[depth][g*4] = b;
						GenMoves[depth][g*4+1] = a;
						GenMoves[depth][g*4+2] = b+mSj;
						GenMoves[depth][g*4+3] = a;
						g++;
					}
				}
					//printf("\n");
				break;
			}
		}
			//MoveNum[depth] = g;
			//depth++;
	}

}
}
	//MoveNum[depth] = g;
}
MoveNum[depth] = g;
}



