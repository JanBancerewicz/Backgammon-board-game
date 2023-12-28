#pragma warning(push)
#pragma warning(disable:6385)
#include <iostream>
//#include<stdlib.h>
#include<cstdlib>
#include<ctime>
//#include "conio.h"
#define MAXARGLEN 20
#define ARR 200
#define BSIZE 24
#define STOP 5
#define BAR 25
#define MAXOUTSIDE 15
#define DICE 6
#define HOMELEN 6


using namespace std;


//int readinput(int rollresult[2], player* p, board* b, player* enemy, int a1, int a2);


struct player
{
	//int ruch[2];
	//char* name;
	short int id=0;
	int pawns= MAXOUTSIDE;
	int score;
	int points = 167;
	int possiblemoves=0;
	int possiblemovesarr[ARR][2];
	int mandatorymoves=0;
	int mandatorymovesarr[ARR][2];
};


struct board
{
	int tab[BSIZE] = {-2,0,0,0,0,5,0,3,0,0,0,-5,5,0,0,0,-3,0,-5,0,0,0,0,2};
	int bar[2] = {0,0};
	int outside[2] = {0,0};
	int round = 1;
};


int main();
void loadHistory(player* p1, player* p2, board* b, int n);


int checkDbl(int rollresult[2])
{
	if (rollresult[0] == rollresult[1])
	{
		return 1;
	}
	else
	{
		return 0;

	}
}


int checkMandatoryMove(player* p, board* b, int playerinput[2])
{
	int i = 0, a = p->mandatorymoves;
	int possiblemoves[ARR][2];

	if (a == 0)
	{
		return 1;
	}

	if (b->bar[p->id - 1] != 0)
	{
		return 1;
	}
	else
	{
		for (int i = 0;i < a;i++)
		{
			if (playerinput[0] == p->mandatorymovesarr[i][0] && playerinput[1] == p->mandatorymovesarr[i][1])
			{
				return 1;
			}
		}
	}

	return 0;
}


int* roll(player p)
{
	int x = 1 + rand() % DICE;
	int y = 1 + rand() % DICE;
	int item[2];
	item[0] = x;
	item[1] = y;

	cout << "\n\tGracz " << p.id << " wyrzucil [" << x << "] i [" << y << "]";
	if (x == y)
	{
		cout << " i [" << x << "] i [" << y << "]";

	}
	cout << endl << endl;

	return item;
	//w miare randomowe xd
}


void clearPossibleMoves(player* p)
{
	for (int i = 0; i < ARR; i++)
	{
		p->possiblemovesarr[i][0] = 0;
		p->possiblemovesarr[i][1] = 0;
	}
	p->possiblemoves = 0;

	for (int i = 0; i < ARR; i++)
	{
		p->mandatorymovesarr[i][0] = 0;
		p->mandatorymovesarr[i][1] = 0;
	}
	p->mandatorymoves = 0;
}


void printBoard(board b)
{
	for (int i = 0; i < BSIZE; i++)
	{
		cout << (i < 9 ? "0" : "") << i+1 << " ";
	}cout << endl;
	for (int i = 0; i < BSIZE; i++)
	{
		cout <<(b.tab[i] < 0 ? "" : " ") << b.tab[i] << " ";
	}
	cout << " bar{" << b.bar[0] << " , " << b.bar[1] << " }";
	cout << " out{" << b.outside[0] << " , " << b.outside[1] << " }";
	cout << " round{ " << b.round <<" }" << endl;
	
	cout << endl;
}


int isLegalMove(int rollresult[2], player* p, board* b, int playerinput[2])
{
	//if (p->mandatorymoves)
	//{
	//	for (int j = 0; j < p->mandatorymoves; j++)
	//	{
	//		if (p->mandatorymovesarr[j][0] == playerinput[0] && p->mandatorymovesarr[j][1] == playerinput[1])
	//		{
	//			//cout << "legalny ruch" << endl;
	//			return 1;

	//		}
	//	}
	//	return 0;
	//}
	//else
	//{
		for (int j = 0; j < p->possiblemoves; j++)
		{
			if (p->possiblemovesarr[j][0] == playerinput[0] && p->possiblemovesarr[j][1] == playerinput[1])
			{
				//cout << "legalny ruch" << endl;
				return 1;

			}
		}
		return 0;
	//}

	
}


int checkOutside(player* p, board* b)
{
	if (b->bar[(p->id - 1)]) { return 0; }

	if (p->id == 1)
	{
		for (int i = HOMELEN;i < BSIZE;i++)
		{
			if (b->tab[i] > 0)
			{
				return 0;
			}
		}
		return 1;
	}
	else
	{
		for (int i = 0;i < (BSIZE - HOMELEN);i++)
		{
			if (b->tab[i] < 0)
			{
				return 0;
			}
		}
		return 1;
	}
	
}


void getLegalOutsides(int rollresult[2], player* p, board b)
{
	int possiblemoves[ARR][2];
	int i = 0;
	int br = b.bar[(p->id == 1 ? 0 : 1)];
	//int dublet = checkDbl(rollresult);

	

	if (p->id == 1) { //jesli jestesmy graczem 1
		for (int k = 0;k < 2;k++) {
			int moves = 0;
			for (int h = 5;h >= 0;h--) { //pozycje od 6 do 1 (dom gracza 1)
				if (b.tab[h] > 0) { //jezeli jest pionek
					if (rollresult[k] != 0) {
						if (1+h - rollresult[k] == 0) { //mozliwe wejscie
							possiblemoves[i][0] = h + 1;
							possiblemoves[i][1] = 0;
							i++;
						}
						/*else {
							int j = (k ? 0 : 1);
							if (h - rollresult[k] - rollresult[j] < 0) {
								possiblemoves[i][0] = h + 1;
								possiblemoves[i][1] = 0;
								i++;
							}
						}*/
					}
				}
			}
			if (moves == 0)
			{
				for (int h = 5;h >= 0 && !moves;h--) { //pozycje od 6 do 1 (dom gracza 1)
					if (b.tab[h] > 0) { //jezeli jest pionek
						if (rollresult[k] != 0) {
							if (h - rollresult[k] < 0) { //mozliwe wejscie
								possiblemoves[i][0] = h + 1;
								possiblemoves[i][1] = 0;
								i++;
								moves++;
							}
						}
					}
				}
			}
		}

	}
	else //jesli jestesmy graczem 2
	{
		for (int k = 0;k < 2;k++) {
			int moves = 0;
			for (int h = (BSIZE - HOMELEN);h < BSIZE ;h++) { //pozycje od 18 do 24 (dom gracza 2)
				if (b.tab[h] < 0) { //jezeli jest pionek
					if (rollresult[k] != 0) {
						if (h + rollresult[k] == BSIZE) { //mozliwe wejscie
							possiblemoves[i][0] = h + 1;
							possiblemoves[i][1] = 0;
							i++;
							moves++;
						}
						/*else {
							int j = (k ? 0 : 1);
							if (h + rollresult[k] + rollresult[j] > 23) {
								possiblemoves[i][0] = h + 1;
								possiblemoves[i][1] = 0;
								i++;
							}
						}*/
					}
				}
			}
			if (moves == 0)
			{
				for (int h = (BSIZE - HOMELEN);h < BSIZE && !moves;h++) { //pozycje od 18 do 24 (dom gracza 2)
					if (b.tab[h] < 0) { //jezeli jest pionek
						if (rollresult[k] != 0) {
							if (h + rollresult[k] > BSIZE - 1) { //mozliwe wejscie
								possiblemoves[i][0] = h + 1;
								possiblemoves[i][1] = 0;
								i++;
								moves++;

							}
						}
					}
				}
			
			}
		}
	}



	int a = p->possiblemoves;
	//if ((i + a) > ARR) { cout << "za duzo ruchow" << endl; }

	//cout << "i: " << i << endl;


	for (int l = 0; l < i;l++)
	{
		p->possiblemovesarr[l + a][0] = possiblemoves[l][0];
		p->possiblemovesarr[l + a][1] = possiblemoves[l][1];
		//cout << possiblemoves[l][0] << " " << possiblemoves[l][1] << endl;

	}
	//cout << i << endl;
	p->possiblemoves += i;
}


void getLegalDoubles(int rollresult, player* p, board b)
{
	int possiblemoves[ARR][2];
	int i = 0, m = 0;
	int br = b.bar[(p->id == 1 ? 0 : 1)];
	int mandatorymoves[ARR][2];


	if (p->id == 1) { //jesli jestesmy graczem 1
		if (br == 0) { //jesli nie jestesmy na barze
			if (rollresult != 0) {
				for (int h = BSIZE-1;h >= 0;h--)
				{
					if (b.tab[h] > 0)
					{
						for (int k = 1;k <= 4;k++) {
							if (h - rollresult * k >= 0) {
								if (b.tab[h - rollresult * k] >= -1)
								{
									if (b.tab[h - rollresult * k] == -1)
									{
										mandatorymoves[i][0] = h + 1;
										mandatorymoves[i][1] = h + 1 - rollresult * k;
										m++;
									}

									possiblemoves[i][0] = h + 1;
									possiblemoves[i][1] = h + 1 - rollresult * k;
									i++;
								}
								else { k = STOP;break; }
							}

						}
					}
				}
			}
		}
		else if (br == 1)//jesli jestesmy na barze
		{
			if (rollresult != 0) {
				for (int k = 1;k <= 4;k++) {
					if (b.tab[BSIZE - rollresult * k] >= -1)
					{
						possiblemoves[i][0] = BAR;
						possiblemoves[i][1] = BAR - rollresult * k;
						i++;
					}
					else { k = STOP;break; }
				}
			}
		}
		else if (br >= 2)
		{
			if (rollresult != 0) {
				if (b.tab[BSIZE - rollresult] >= -1)
				{
					possiblemoves[i][0] = BAR;
					possiblemoves[i][1] = BAR - rollresult;
					i++;
				}
			}
		}
	}
	else //jesli jestesmy graczem 2
	{
		if (br == 0) { //jesli nie jestesmy na barze
			if (rollresult != 0) {
				for (int h = 0;h < BSIZE;h++)
				{
					if (b.tab[h] < 0)
					{

						for (int k = 1;k <= 4;k++) {
							if (h + rollresult * k <= BSIZE-1) {
								if (b.tab[h + rollresult * k] <= 1)
								{
									possiblemoves[i][0] = h + 1;
									possiblemoves[i][1] = h + 1 + rollresult * k;
									i++;
								}
								else { k = STOP;break; }
							}

						}
					}
				}
			}
		}
		else if (br == 1)//jesli jestesmy na barze
		{
			if (rollresult != 0) {
				for (int k = 1;k <= 4;k++) {
					if (b.tab[rollresult * k - 1] <= 1)
					{
						possiblemoves[i][0] = BAR;
						possiblemoves[i][1] = rollresult * k;
						i++;
					}
					else { k = STOP;break; }
				}
			}
		}
		else if (br >= 2)
		{
			if (rollresult != 0) {
				if (b.tab[rollresult -1] <= 1)
				{
					possiblemoves[i][0] = BAR;
					possiblemoves[i][1] = rollresult;
					i++;
				}
			}
		}
	}



	int a= p->possiblemoves;
	if ((i+a)>ARR) { cout << "za duzo ruchow" << endl; }

	for (int l = 0; l < i;l++)
	{
		p->possiblemovesarr[l+a][0] = possiblemoves[l][0];
		p->possiblemovesarr[l+a][1] = possiblemoves[l][1];
		//cout << possiblemoves[l][0] << " " << possiblemoves[l][1] << endl;
		
	}
	//cout << i << endl;
	p->possiblemoves += i;

}


void refactorMandatoryMoves(int mmarr[ARR][2],int m, player* p)
{
	int mandatorymoves[ARR][2];
	int closest = 0, mm = 0;
	if (m > 0)
	{
		closest= mmarr[0][1];
		if (p->id == 1)
		{
			for (int i = 0; i < m;i++)
			{
				if (mmarr[i][1] > closest) { closest = mmarr[i][1]; }
			}
		}
		else
		{
			for (int i = 0; i < m;i++)
			{
				if (mmarr[i][1] < closest) { closest = mmarr[i][1]; }
			}
		}
		
		//cout << "elo: " << closest << endl;


		for (int i = 0; i < m;i++)
		{
			if (mmarr[i][1] == closest)
			{
				p->mandatorymovesarr[mm][0] = mmarr[i][0];
				p->mandatorymovesarr[mm][1] = mmarr[i][1];
				//cout << "mm: " << p->mandatorymovesarr[mm][0] << " " << p->mandatorymovesarr[mm][1] << endl;
				mm++;
			}
		}
		p->mandatorymoves = mm;

	}
}


void getLegalMoves(int rollresult[2], player* p, board b) // zwraca [x][2] arr
{
	int br, i = 0, m = 0;
	short x = p->id;
	int possiblemoves[ARR][2];
	int mandatorymoves[ARR][2];

	clearPossibleMoves(p);


	if (rollresult[0] > rollresult[1])//defaultowo posortuje rollresult
	{
		br = rollresult[0];
		rollresult[0] = rollresult[1];
		rollresult[1] = br;
	}

	br = b.bar[(p->id == 1 ? 0 : 1)];

	if (br != 0) //jesli jestesmy na barze
	{
		switch (x)
		{
		case 1: //-5,0,0,0,0,2 pozytywne

			for (int k = 0;k < 2;k++) {
				if (rollresult[k] != 0) {
					if (b.tab[BSIZE - rollresult[k]] >= -1)
					{
						if (b.tab[BSIZE - rollresult[k]] == -1) //mandatory capture
						{
							mandatorymoves[m][0] = BAR;
							mandatorymoves[m][1] = BAR - rollresult[k];
							m++;
						}

						possiblemoves[i][0] = BAR;
						possiblemoves[i][1] = BAR - rollresult[k];
						i++;
						

						if (br == 1) {
							int j = (k ? 0 : 1);
							if (b.tab[BSIZE - rollresult[k] - rollresult[j]] >= -1)
							{
								if (rollresult[k] != 0 && rollresult[j] != 0) {
									if (b.tab[BSIZE - rollresult[k]] == -1 || b.tab[BSIZE - rollresult[k] - rollresult[j]] == -1) //mandatory capture
									{
										mandatorymoves[m][0] = BAR;
										mandatorymoves[m][1] = BAR - rollresult[k] - rollresult[j];
										m++;
									}

									possiblemoves[i][0] = BAR;
									possiblemoves[i][1] = BAR - rollresult[k] - rollresult[j];
									i++;
								}

								//sprawdza czy suma jest legalna tylko gdy 1 pionek na barze
							}
						}
					}
				}
			}

			break;

		case 2: //-2,0,0,0,0,5

			for (int k = 0;k < 2;k++) {
				if (rollresult[k] != 0) {

					if (b.tab[rollresult[k] - 1] <= 1)
					{
						if (b.tab[rollresult[k] - 1] == 1) //mandatory capture
						{
							mandatorymoves[m][0] = BAR;
							mandatorymoves[m][1] = rollresult[k];
							m++;
						}
						
						possiblemoves[i][0] = BAR;
						possiblemoves[i][1] = rollresult[k];
						i++;
						

						if (br == 1) {
							int j = (k ? 0 : 1);
							if (b.tab[rollresult[k] + rollresult[j] - 1] <= 1)
							{
								if (rollresult[k] != 0 && rollresult[j] != 0) {
									
									if (b.tab[rollresult[k] - 1] == 1 || b.tab[rollresult[k] + rollresult[j] - 1] == 1) //mandatory capture
									{
										mandatorymoves[m][0] = BAR;
										mandatorymoves[m][1] = rollresult[k] + rollresult[j];
										m++;
									}
					
									possiblemoves[i][0] = BAR;
									possiblemoves[i][1] = rollresult[k] + rollresult[j];
									i++;
								}

								//sprawdza czy suma jest legalna tylko gdy 1 pionek na barze
							}
						}
					}
				}
			}

			break;
		}

	}
	else //jesli nie jestesmy na barze
	{
		switch (x)//-2,0,0,0,0,5,0,3,0,0,0,-5,5,0,0,0,-3,0,-5,0,0,0,0,2
		{
		case 1: //test dla g1 do tylu

			for (int h = BSIZE - 1;h >= 0;h--)
			{
				if (b.tab[h] > 0){ // jezeli jest pionek
					for (int k = 0;k < 2;k++){ // dla obu rollresult
						if (rollresult[k] != 0) {
							if (h - rollresult[k] >= 0) {
								if (b.tab[h - rollresult[k]] >= -1)
								{
									if (b.tab[h - rollresult[k]] == -1) //mandatory capture
									{
										mandatorymoves[m][0] = h + 1;
										mandatorymoves[m][1] = h + 1 - rollresult[k];
										m++;
									}


									possiblemoves[i][0] = h + 1;
									possiblemoves[i][1] = h + 1 - rollresult[k];
									i++;

									if (br <= 1) {
										int j = (k ? 0 : 1);
										if (h - rollresult[k] - rollresult[j] >= 0) {
											if (b.tab[h - rollresult[k] - rollresult[j]] >= -1)
											{
												if (b.tab[h - rollresult[k]] == -1 || b.tab[h - rollresult[k] - rollresult[j]] == -1)
												{
													mandatorymoves[m][0] = h + 1;
													mandatorymoves[m][1] = h + 1 - rollresult[k] - rollresult[j];
													m++;
												}
												
												possiblemoves[i][0] = h + 1;
												possiblemoves[i][1] = h + 1 - rollresult[k] - rollresult[j];
												i++;
												

												//sprawdza czy suma jest legalna
											}
										}
									}
								}
							}
						}
					}
				}
			}
			break;
		case 2:
			for (int h = 0;h < BSIZE;h++)
			{
				if (b.tab[h] < 0){ // jezeli jest pionek
					for (int k = 0;k < 2;k++) { // dla obu rollresult
						if (rollresult[k] != 0) {
							if (h + rollresult[k] <= BSIZE - 1) {
								if (b.tab[h + rollresult[k]] <= 1)
								{
									if (b.tab[h + rollresult[k]] == 1) //mandatory capture
									{
										mandatorymoves[m][0] = h + 1;
										mandatorymoves[m][1] = h + 1 + rollresult[k];
										m++;
									}

									possiblemoves[i][0] = h + 1;
									possiblemoves[i][1] = h + 1 + rollresult[k];
									i++;

									if (br <= 1) {
										int j = (k ? 0 : 1);
										if (h + rollresult[k] + rollresult[j] <= BSIZE - 1) {
											if (b.tab[h + rollresult[k] + rollresult[j]] <= 1)
											{
												if (b.tab[h + rollresult[k]] == 1 || b.tab[h + rollresult[k] + rollresult[j]] == 1)
												{
													mandatorymoves[m][0] = h + 1;
													mandatorymoves[m][1] = h + 1 + rollresult[k] + rollresult[j];
													m++;
												}

												if (rollresult[k] != 0) {
													possiblemoves[i][0] = h + 1;
													possiblemoves[i][1] = h + 1 + rollresult[k] + rollresult[j];
													i++;
												}

												//sprawdza czy suma jest legalna
											}
										}
									}
								}
							}
						}
					}
				}
			}
			break;

		}
	}

	refactorMandatoryMoves(mandatorymoves, m, p);


	for (int l = 0; l < i;l++)
	{
		p->possiblemovesarr[l][0] = possiblemoves[l][0];
		p->possiblemovesarr[l][1] = possiblemoves[l][1];
	}


	p->possiblemoves = i;

	if (checkDbl(rollresult)) { getLegalDoubles(rollresult[0], p, b); }

	if (checkOutside(p, &b)) { getLegalOutsides(rollresult, p, b); }

	//return possiblemoves;
}


int checkWin(int rollresult[2], player* p, board* b, int playerinput[2])
{
	int legal = isLegalMove(rollresult, p, b, playerinput);
	int dublet = checkDbl(rollresult);
	int os = checkOutside(p, b);
	int diff = playerinput[1] - playerinput[0];

	if (legal && os) //outside and wincondition
	{
		if (playerinput[1] == 0) { b->outside[p->id - 1]++; }
		if (b->outside[p->id - 1] == MAXOUTSIDE)
		{
			cout << "wygrana" << endl;
			//return 100; //zwyciestwo // wywolaj int main() i zakoncz gre
			main(); //todo todo todo GRATULACJE UZYTKOWNIKU WYGRALES IPHONE
			//cin >> os;
			return 1;
		}
	}

	return 0;
}


int move(int rollresult[2], player* p, board* b, int playerinput[2], player* enemy)
{
	clearPossibleMoves(p);
	getLegalMoves(rollresult, p, *b);
	

	int legal = isLegalMove(rollresult, p, b, playerinput);
	int dublet = checkDbl(rollresult);
	int os = checkOutside(p,b);
	int diff = (playerinput[0] > playerinput[1] ? playerinput[0] - playerinput[1] : playerinput[1] - playerinput[0]);
	
	//cout <<"diff "<< diff << endl;
	
	if (legal)
	{
		if (p->id == 1)
		{
			//if (playerinput[0] == BAR) { diff = playerinput[1]; }
			//if (playerinput[1] == 0) { diff = BAR - playerinput[0]; }

			//todo possible bug z wchodzeniem na outside przy komendzie 18 0 i dublu (chyba nielegalne) jest git

			if (diff == 3 * rollresult[0] && dublet) //dublety
			{
				cout << "rekurencja 3:)" << endl;
				int rr1[2] = { 0,rollresult[0] };

				int pi1[2] = { playerinput[0], playerinput[0] - rollresult[0] };
				int pi2[2] = { pi1[1], pi1[1] - rollresult[0] };
				int pi3[2] = { pi2[1], pi2[1] - rollresult[0] };
				
					
				if (isLegalMove(rollresult, p, b, pi1))
				{
					//cout << "opcja1" << endl;
					move(rr1, p, b, pi1, enemy);
					move(rr1, p, b, pi2, enemy);
					move(rr1, p, b, pi3, enemy);

					checkWin(rollresult, p, b, playerinput);
					return 3;
				}
				else
				{
					cout << "rekurencja 3 nie dziala" << endl;
				}
			}
			else if (diff == 4 * rollresult[0] && dublet)
			{
				cout << "rekurencja 4:)" << endl;
				int rr1[2] = { 0,rollresult[0] };

				int pi1[2] = { playerinput[0], playerinput[0] - rollresult[0] };
				int pi2[2] = { pi1[1], pi1[1] - rollresult[0] };
				int pi3[2] = { pi2[1], pi2[1] - rollresult[0] };
				int pi4[2] = { pi3[1], pi3[1] - rollresult[0] };

				if (isLegalMove(rollresult, p, b, pi1))
				{
					//cout << "opcja1" << endl;
					move(rr1, p, b, pi1, enemy);
					move(rr1, p, b, pi2, enemy);
					move(rr1, p, b, pi3, enemy);
					move(rr1, p, b, pi4, enemy);

					checkWin(rollresult, p, b, playerinput);
					return 4;
				}
				else
				{
					cout << "rekurencja 4 nie dziala" << endl;
				}
			}
			else if (diff > rollresult[0] && diff > rollresult[1])
			{
				cout << "rekurencja :)" << endl;
				int rr1[2] = { 0,rollresult[0] };
				int rr2[2] = { 0,rollresult[1] };
				int pi1[2] = { playerinput[0], playerinput[0] - rollresult[0] };
				int pi2[2] = { playerinput[0] - rollresult[0], playerinput[1] };
				int pi3[2] = { playerinput[0], playerinput[0] - rollresult[1] };
				int pi4[2] = { playerinput[0] - rollresult[1], playerinput[1] };

				/*cout << pi1[0] << " " << pi1[1] << endl;
				cout << pi2[0] << " " << pi2[1] << endl;
				cout << pi3[0] << " " << pi3[1] << endl;
				cout << pi4[0] << " " << pi4[1] << endl;
				cout << "rekurencja :)" << endl;*/


				
				if (isLegalMove(rollresult, p, b, pi3))
				{
					//cout << "opcja2" << endl;
					
					move(rr2, p, b, pi3, enemy);

					move(rr1, p, b, pi4, enemy);

				}
				else if (isLegalMove(rollresult, p, b, pi1))
				{

					move(rr1, p, b, pi1, enemy);

					move(rr2, p, b, pi2, enemy);

				}
				else
				{
					cout << "rekurencja nie dziala" << endl;
					
				}

			}
			else
			{
				

				//if (playerinput[0] == 0) { b->outside[0]++; }
				if (playerinput[0] == BAR) //move z paska
				{
					b->bar[0]--;
					
					p->points -= playerinput[1];
					
				}
				else
				{
					b->tab[playerinput[0] - 1]--;
					p->points -= (diff + 1);
				}

				if (b->tab[playerinput[1] - 1] == -1) //zbijanie
				{
					b->tab[playerinput[1] - 1]++;
					
					b->bar[1]++;
					enemy->points += (playerinput[1]);
				}
				b->tab[playerinput[1] - 1]++;

			}
		}
		else //player2
		{
			int newpi0 = playerinput[0];
			if (playerinput[0] == BAR) { diff = playerinput[1];newpi0 = 0; }
			if (playerinput[1] == 0) { diff = BAR - playerinput[0];}

			if (diff == 3 * rollresult[0] && dublet) //dublety 2
			{
				cout << "rekurencja 3:)" << endl;
				int rr1[2] = { 0,rollresult[0] };

				int pi1[2] = { playerinput[0], newpi0 + rollresult[0] };
				int pi2[2] = { pi1[1], pi1[1] + rollresult[0] };
				int pi3[2] = { pi2[1], pi2[1] + rollresult[0] };
				//int pi4[2] = { pi3[1], pi3[1] + rollresult[0] };

				if (isLegalMove(rollresult, p, b, pi1))
				{
					//cout << "opcja1" << endl;
					move(rr1, p, b, pi1, enemy);
					move(rr1, p, b, pi2, enemy);
					move(rr1, p, b, pi3, enemy);

					checkWin(rollresult, p, b, playerinput);
					return 3;
				}
				else
				{
					cout << "rekurencja 3 nie dziala" << endl;
				}
			}
			else if (diff == 4 * rollresult[0] && dublet)
			{
				cout << "rekurencja 4:)" << endl;
				int rr1[2] = { 0,rollresult[0] };

				int pi1[2] = { playerinput[0], newpi0 + rollresult[0] };
				int pi2[2] = { pi1[1], pi1[1] + rollresult[0] };
				int pi3[2] = { pi2[1], pi2[1] + rollresult[0] };
				int pi4[2] = { pi3[1], pi3[1] + rollresult[0] };

				if (isLegalMove(rollresult, p, b, pi1))
				{
					//cout << "opcja1" << endl;
					move(rr1, p, b, pi1, enemy);
					move(rr1, p, b, pi2, enemy);
					move(rr1, p, b, pi3, enemy);
					move(rr1, p, b, pi4, enemy);

					checkWin(rollresult, p, b, playerinput);
					return 4;
				}
				else
				{
					cout << "rekurencja 4 nie dziala" << endl;
				}
			}
			else if (diff > rollresult[0] && diff > rollresult[1])
			{
				cout << "rekurencja :)" << endl;
				int rr1[2] = { 0,rollresult[0] };
				int rr2[2] = { 0,rollresult[1] };
				int pi1[2] = { playerinput[0], newpi0 + rollresult[0] };
				int pi2[2] = { newpi0 + rollresult[0], playerinput[1] };
				int pi3[2] = { playerinput[0], newpi0 + rollresult[1] };
				int pi4[2] = { newpi0 + rollresult[1], playerinput[1] };

				/*cout << pi1[0] << " " << pi1[1] << endl;
				cout << pi2[0] << " " << pi2[1] << endl;
				cout << pi3[0] << " " << pi3[1] << endl;
				cout << pi4[0] << " " << pi4[1] << endl;*/
				cout << "rekurencja :)" << endl;

				if (isLegalMove(rollresult, p, b, pi1))
				{
					
					move(rr1, p, b, pi1, enemy);
					

					move(rr2, p, b, pi2, enemy);
					

				}
				else if (isLegalMove(rollresult, p, b, pi3))
				{
					//cout << "opcja2" << endl;
					

					move(rr2, p, b, pi3, enemy);
					

					move(rr1, p, b, pi4, enemy);
					

				}
				else
				{
					cout << "rekurencja nie dziala" << endl;
					
				}

			}
			else
			{
				
				//if (playerinput[0] == BSIZE) { b->outside[1]++; }

				if (playerinput[0] == BAR) //move z paska
				{
					b->bar[1]--;
					
					p->points -= (BSIZE -playerinput[1]);
				}
				else
				{
					b->tab[playerinput[0] - 1]++;
					p->points -= (diff + 1);
				}


				if (b->tab[playerinput[1] - 1] == 1) //zbijanie
				{
					b->tab[playerinput[1] - 1]--;
					
					b->bar[0]++;
					enemy->points += (BSIZE - playerinput[1]);
				}
				b->tab[playerinput[1] - 1]--;
		
			}

		}


		if (diff == rollresult[0] || (os && diff < rollresult[0])) //obsluga polowicznych ruchow
		{
			checkWin(rollresult, p, b, playerinput);
			return 0;
		}
		else if (diff == rollresult[1] || (os && diff < rollresult[1]))
		{
			checkWin(rollresult, p, b, playerinput);
			return 1;
		}
		//else if (os && diff< rollresult[0])
		//{
		//	return 0;
		//}
		//else if (os && diff < rollresult[1])
		//{
		//	return 1;
		//}

		checkWin(rollresult, p, b, playerinput);
		return 2;
	}
	else
	{
		cout << "nielegalny ruch "<<playerinput[0]<<" "<<playerinput[1] << endl;
		return -1;

	}
}


void saveGame(player p1, player p2, board b)
{
	
	FILE* file;
	
	fopen_s(&file, "save.txt", "w");
	
	for (int i = 0;i < BSIZE;i++)
	{
		fprintf_s(file, "%d ", b.tab[i]);

	}
	for (int i = 0;i < 2;i++)
	{
		fprintf_s(file, "%d ", b.bar[i]);

	}
	for (int i = 0;i < 2;i++)
	{
		fprintf_s(file, "%d ", b.outside[i]);

	}
	fclose(file);
}


void loadGame(player* p1, player* p2, board* b, int mode)
{
	
	FILE* file;

	if (mode)
	{
		fopen_s(&file, "savedefault.txt", "r");
	}
	else
	{
		fopen_s(&file, "save.txt", "r");
	}
	
	//fopen_s(&file, "save.txt", "r");
	
	for (int i = 0;i < BSIZE;i++)
	{
		fscanf_s(file, "%d ", &b->tab[i]);
	}
	for (int i = 0;i < 2;i++)
	{
		fscanf_s(file, "%d ", &b->bar[i]);

	}
	for (int i = 0;i < 2;i++)
	{
		fscanf_s(file, "%d ", &b->outside[i]);

	}

	fclose(file);
	printBoard(*b);
}


void saveHistory(int playerinput[2], player p, board* b, int rollresult[2])
{

	FILE* file;

	if (b->round == 1) // resetuje historie w pierwszej turze
	{
		fopen_s(&file, "history.txt", "w");
		fclose(file);
		b->round++;
	}

	fopen_s(&file, "history.txt", "a");


	fprintf_s(file, "%d ", p.id);

	for (int i = 0;i < 2;i++)
	{
		fprintf_s(file, "%d ", playerinput[i]);

	}
	for (int i = 0;i < 2;i++)
	{
		fprintf_s(file, "%d ", rollresult[i]);

	}
	/*for (int i = 0;i < 2;i++)
	{
		fprintf_s(file, "%d ", b.outside[i]);

	}*/
	fclose(file);
}


void cloneHistory()
{

	FILE* file;
	FILE* file2;

	fopen_s(&file, "history.txt", "r");
	fopen_s(&file2, "replay.txt", "w");

	int num = 0;
	while (!feof(file)) {
		int a;
		fscanf_s(file, "%d ", &a);
		//cout << a << endl;
		fprintf_s(file2, "%d ", a);

		num++;
	}
	fclose(file);
	fclose(file2);
}


int readinput(int rollresult[2], player* p, board* b, player* enemy,int a1,int a2)
{

	/*int a = (p->mandatorymoves ? p->mandatorymoves : p->possiblemoves);
	int ruchy[ARR][2];

	for (int i = 0; i < a; i++)
	{
		ruchy[i][0] = (p->mandatorymoves ? p->mandatorymovesarr[i][0] : p->possiblemovesarr[i][0]);
		ruchy[i][1] = (p->mandatorymoves ? p->mandatorymovesarr[i][1] : p->possiblemovesarr[i][1]);

		cout << ruchy[i][0] << " " << ruchy[i][1] << endl;

	}*/
	

	int i1 = 1;
	if (rollresult[0] == rollresult[1])
	{
		i1 = 0;
	}
	
	for (i1; i1 < 2; i1++)
	{
		//cout<<"\t"<<i1 << endl;
		

		char playerinput[MAXARGLEN];
		int arg1, arg2;

		
		getLegalMoves(rollresult, p, *b);

		int a = p->possiblemoves;
		int c = p->mandatorymoves;
		if (b->bar[p->id - 1] > 0) { c = 0; }
		int ruchy[ARR][2];

		if (a == 0) { cout << "pusta tablica" << endl; return 0; }

		for (int i = 0; i < a; i++)
		{
			ruchy[i][0] = p->possiblemovesarr[i][0];
			ruchy[i][1] = p->possiblemovesarr[i][1];

			cout << ruchy[i][0] << " " << ruchy[i][1] << endl;

		}

		for (int i = 0; i < c; i++)
		{
			cout << "mm: " << p->mandatorymovesarr[i][0] << " " << p->mandatorymovesarr[i][1] << endl;

		}
		
		if (a1 && a2)
		{
			playerinput[0] = 'm';
			playerinput[1] = 'o';
			playerinput[2] = 'v';
			playerinput[3] = 'e';
			playerinput[4] = '\0';
			arg1 = a1;
			arg2 = a2;
		}
		else { cin >> playerinput; }

		if (!strcmp(playerinput, "quit") || !strcmp(playerinput, "QUIT")) { return -1; }
		else if (!strcmp(playerinput, "save") || !strcmp(playerinput, "SAVE")) { i1 = 5; saveGame(*p, *enemy, *b);readinput(rollresult, p, b, enemy, 0, 0); }
		else if (!strcmp(playerinput, "load") || !strcmp(playerinput, "LOAD")) { i1 = 5; loadGame(p, enemy, b,0); readinput(rollresult, p, b, enemy, 0, 0); }
		else if (!strcmp(playerinput, "replay") || !strcmp(playerinput, "REPLAY")) { i1 = 5; (p->id == 1 ? loadHistory(p, enemy, b, 0) : loadHistory(enemy, p, b, 0)); } //todo dziala
		else if (!strcmp(playerinput, "move") || !strcmp(playerinput, "MOVE"))
		{
			if (!(a1 && a2)) { cin >> arg1 >> arg2; }
				
			//cout << playerinput << " - " << arg1 << " - " << arg2 << endl;
			int resultinput[2] = { arg1,arg2 };

			//kontrola ruchu

			if (!checkMandatoryMove(p, b, resultinput))
			{
				cout << "prosze wykonac obowiazkowe bicie" << endl;
				if (checkDbl(rollresult)) { i1 = STOP; }
				readinput(rollresult, p, b, enemy, 0, 0);
				return 0;
			}

			int val = move(rollresult, p, b, resultinput, enemy);

			printBoard(*b);

			if (val != -1)
			{
				saveHistory(resultinput, *p, b, rollresult);
			}

			if (val == 0)
			{
				cout << "wykonano polowiczny ruch " << rollresult[1] << endl; //rekurencja :)
				int rr[2] = { 0,rollresult[1] };
				readinput(rr, p, b, enemy,0,0);
			}
			else if (val == 1)
			{
				cout << "wykonano polowiczny ruch " << rollresult[0] << endl; //rekurencja :)
				int rr[2] = { 0,rollresult[0] };
				readinput(rr, p, b, enemy, 0, 0);
			}
			else if (val == 2)
			{
				cout << "wykonano ruch" << endl;
			}
			else if (val == 3)
			{
				cout << "wykonano polowiczny ruch dubletowy " << rollresult[1] << endl; //rekurencja :)
				int rr[2] = { 0,rollresult[1] };
				i1 = 5;
				readinput(rr, p, b, enemy, 0, 0);
				
				break;
			}
			else if (val == 4)
			{
				cout << "wykonano ruch dubletowy" << endl;
				i1 = 5;
				//clearPossibleMoves(p);
				return 0;
				
				
			}
			else if (val == -1)
			{
				cout << "prosze sprobowac ponownie" << endl;
				if (checkDbl(rollresult)) { i1 = STOP; }
				readinput(rollresult, p, b, enemy, 0, 0);
				
			}
			else if (val == 100)
			{
				cout << "wygrana" << endl;
				main(); //todo wywolanie maina podczas wygranej
				return -1;
			}
			

			//cout<<i1<<endl;

		}
	}

}


void loadHistory(player* p1, player* p2, board* b, int n)
{
	loadGame(p1, p2, b, 1);

	FILE* file;


	fopen_s(&file, "replay.txt", "r");

	/*for (int i = 0;i < 3*n;i++)
	{*/
	int num = 0;
	int i = 0;

	int newrr[2];
	int newpi[2];
	player* newp1 = p1;
	player* newp2 = p2;

	cout << "historia: ";
	while (!feof(file)) { // cala historia
		int a;
		fscanf_s(file, "%d ", &a);
		cout << i << "-";
		cout << a << " ";

		if (i % 5 == 0)
		{
			if (a == 1) { newp1 = p1; newp2 = p2; }
			else { newp1 = p2; newp2 = p1; }
		}
		else if (i % 5 == 1)
		{
			newpi[0] = a;
		}
		else if (i % 5 == 2)
		{
			newpi[1] = a;
		}
		else if (i % 5 == 3)
		{
			newrr[0] = a;
		}
		else if (i % 5 == 4)
		{
			newrr[1] = a;
			//cout << endl;
			//readinput(newrr, newp1, b, newp2, newpi[0], newpi[1]); //na movach zrob
			move(newrr, newp1, b, newpi, newp2);
			num++;
			
		}


		//readinput(newrr, newp1, b, newp2, 0, 0);

		i++;
		//}
	}
	cout << endl<<endl;
	//cout << num << endl;
	printBoard(*b);


	fclose(file);
}


int whoStarts(player* p1, board* b, player* p2)
{
	int x = 0, y = 0;
	int item[2];

	while (x == y) {
		x = 1 + rand() % DICE;
		y = 1 + rand() % DICE;
		item[0] = x;
		item[1] = y;

		cout << "\n\tGracz 1 wyrzucil [" << x << "] \tGracz 2 wyrzucil [" << y << "]" << endl << endl;
	}

	if (x > y)
	{
		cout << "\n\tGracz 1 zaczyna" << endl;
		p1->id = 1;
		p2->id = 2;

		if(readinput(item, p1, b, p2, 0, 0) == -1) { return -1; }
		b->round++;

		return 0;
	}
	else
	{
		cout << "\n\tGracz 2 zaczyna" << endl;
		p1->id = 2;
		p2->id = 1;
		if(readinput(item, p1, b, p2, 0, 0) == -1) { return -1; }
		b->round++;

		return 1;
	}

}


int main()
{
    srand((unsigned)time(NULL)); //ustawianie seed dla wartosci z kostki

	board b;

	player p1, p2;
	p1.id = 1;
	p2.id = 2;

	

	//int debugroll[2] = { 1,3 };
	//int debuginput[2] = { 24,23 };

	//cloneHistory();

	//loadHistory(&p1,&p2,&b,5); //todo utworzenie replay.txt i zapisanie kopii historii
	
	printBoard(b);

	//readinput(debugroll, &p1, &b, &p2, 24, 23); // todo wykonanie testowego ruchu dziala

	//whoStarts(&p1, &b, &p2); // wykonanie pierwszego ruchu //todo naprawienie buga

	
	//todo naprawienie buga z zapisem gry
	
	while (b.outside[0] < MAXOUTSIDE && b.outside[1] < MAXOUTSIDE) //magiczna petla
	{

		int* p = roll(p2);
		int rollresult[2] = { *(p + 0),*(p + 1) };
		//int rollresult[2] = { 1,3 };



		if (readinput(rollresult, &p2, &b, &p1, 0, 0) == -1) { return 0; }
		b.round++;
		
		//----------------------------------------------
		cout << "---------------------------------------------------" << endl;

		p = roll(p1);
		rollresult[0] = *(p + 0);
		rollresult[1] = *(p + 1);
		//int rollresult[2] = { 1,3 };
		;

		if (readinput(rollresult, &p1, &b, &p2, 0, 0) == -1) { return 0; }
		b.round++;

		cout << "---------------------------------------------------" << endl;


	}	

	cout<<"\nkoniec gry\n"<<endl;

	return 0;
}