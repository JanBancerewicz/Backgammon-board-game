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
#define BRDWIDTH 33
#define BRDHEIGHT 8
#define AGAIN i1 = 5;readinput(rr, p, b, e, 0, 0);
#define PROMPT printBoard(*b);cout << "prosze wykonac obowiazkowe bicie\n";
#define ILLEGAL cout << "nielegalny ruch " << y[0] << " " << y[1] << endl;printHints(r, p, b);
#define HINTSIZE 10


struct player
{
	int movecount = 2;
	
	int roll[2] = { 0,0 };
	short int id = 0;
	int possiblemoves = 0;
	int pmarr[ARR][2]; //possiblemoves array
	int mandatorymoves = 0;
	int mandatorymovesarr[ARR][2];
};


struct board
{
	int tab[BSIZE] = { -2,0,0,0,0,5,0,3,0,0,0,-5,5,0,0,0,-3,0,-5,0,0,0,0,2 };
	int bar[2] = { 0,0 };
	int outside[2] = { 0,0 };
	int round = 1;
	int customsave = 0;
};

int main();

void printLB();

int checkDbl(int rollresult[2]);

int replayMode(player* p1, player* p2, board* b, int n);

int checkMandatoryMove(player* p, board* b, int playerinput[2]);

int* roll(player* p);

void rollInfo(player* p);

void clrPM(player* p);

int calculatePoints(board b, int p);

int getWinnerScore(player* p, board* b);
 
void printInfo(board b);
void printBoard1(board b);
void printBoard2(board b);
void printBoard3(board b);
void printBoard4(board b);

void printBoard(board b);

void loadLeaderboard(board b);

void saveLeaderboard(char n[ARR], int p);

int isLegalMove(int rollresult[2], player* p, board* b, int playerinput[2]);

int checkOutside(player* p, board* b);

void getLegalOutsides1(int rollresult[2], player* p, board b);
void getLegalOutsides2(int rollresult[2], player* p, board b);

void getLegalOutsides(int rollresult[2], player* p, board b);

int getLegalDoubles1(int rr, player* p, board b);
int getLegalDoubles2(int rr, player* p, board b);
void getLegalDoubles1a(int rr, player* p, board b);
void getLegalDoubles2a(int rr, player* p, board b);

void getLegalDoubles(int rollresult, player* p, board b);


void refactorMandatoryMoves(int mmarr[ARR][2], int m, player* p);

void insrt(int pm[ARR][2], int i, int mm[ARR][2], int m, int rr[2], player* p, board b);


void getLegalMoves1(int rr[2], player* p, board b);
void getLegalMoves2(int rr[2], player* p, board b);
void getLegalMoves3(int rr[2], player* p, board b);
void getLegalMoves4(int rr[2], player* p, board b);

int getLegalMoves(int rollresult[2], player* p, board b);

void checkWin(int rollresult[2], player* p, board* b, int playerinput[2]);

void moveDef1(board* b, int y[2]);
void moveDef2(board* b, int y[2]);
int moveDb1(int r[2], player* p, board* b, int y[2], player* e);
int moveDb2(int r[2], player* p, board* b, int y[2], player* e);
int moveTri1(int r[2], player* p, board* b, int y[2], player* e);
int moveTri2(int r[2], player* p, board* b, int y[2], player* e);
int moveQd1(int r[2], player* p, board* b, int y[2], player* e);
int moveQd2(int r[2], player* p, board* b, int y[2], player* e);
int moveAction1(int r[2], player* p, board* b, int y[2], player* e);
int moveAction2(int r[2], player* p, board* b, int y[2], player* e);

int move(int rollresult[2], player* p, board* b, int playerinput[2], player* enemy);

void saveGame(player p1, player p2, board b);

void loadGame(player* p1, player* p2, board* b, int mode);

void saveHistory(int playerinput[2], player p, board* b, int rollresult[2]);

void cloneHistory(board b);

int replayLen();
int replayModeMenu(player* p1, player* p2, board* b, int n);

int replayMode(player* p1, player* p2, board* b, int n);

int cinCheck(char pi[MAXARGLEN], int rr[2], player* p, board* b, player* e);

int isEmpty(player* p, board* b, int rr[2]);

int valCheck(int v, int rr[2], player* p, board* b, player* e, int ri[2]);

void printHints(int rollresult[2], player* p, board* b);

int readinput(int rollresult[2], player* p, board* b, player* enemy, int a1, int a2);

int whoStarts(player* p1, board* b, player* p2);
