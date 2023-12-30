#pragma once


#define MAXARGLEN 40
#define ARRL 40
#define ARR 200
#define BSIZE 24
#define STOP 5
#define BAR 25
#define MAXOUTSIDE 15
#define DICE 6
#define HOMELEN 6


struct player
{

	//char* name;
	int roll[2] = { 0,0 };
	short int id = 0;
	/*int pawns= MAXOUTSIDE;*/
	int possiblemoves = 0;
	int possiblemovesarr[ARR][2];
	int mandatorymoves = 0;
	int mandatorymovesarr[ARR][2];
};


struct board
{
	int tab[BSIZE] = { -2,0,0,0,0,5,0,3,0,0,0,-5,5,0,0,0,-3,0,-5,0,0,0,0,2 };
	int bar[2] = { 0,0 };
	int outside[2] = { 0,0 };
	int round = 1;
};

int main();

int checkDbl(int rollresult[2]);

int replayMode(player* p1, player* p2, board* b, int n);

int checkMandatoryMove(player* p, board* b, int playerinput[2]);

int* roll(player* p);

void rollInfo(player* p);

void clearPossibleMoves(player* p);

int calculatePoints(board b, int p);

int getWinnerScore(player* p, board* b);
 
void printInfo(board b);

void printBoard(board b);

void loadLeaderboard(board b);

void saveLeaderboard(char n[ARR], int p);

int isLegalMove(int rollresult[2], player* p, board* b, int playerinput[2]);

int checkOutside(player* p, board* b);

void getLegalOutsides(int rollresult[2], player* p, board b);

void getLegalDoubles(int rollresult, player* p, board b);

void refactorMandatoryMoves(int mmarr[ARR][2], int m, player* p);

void getLegalMoves(int rollresult[2], player* p, board b);

void checkWin(int rollresult[2], player* p, board* b, int playerinput[2]);

int move(int rollresult[2], player* p, board* b, int playerinput[2], player* enemy);

void saveGame(player p1, player p2, board b);

void loadGame(player* p1, player* p2, board* b, int mode);

void saveHistory(int playerinput[2], player p, board* b, int rollresult[2]);

void cloneHistory();

int replayMode(player* p1, player* p2, board* b, int n);

int readinput(int rollresult[2], player* p, board* b, player* enemy, int a1, int a2);

int whoStarts(player* p1, board* b, player* p2);
