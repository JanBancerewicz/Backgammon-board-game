#include <iostream>
#include "functions.h"
#include<cstdlib>
#include<ctime>

using namespace std;



void printLB()
{
	system("cls");
	cout << "============================\n";
	cout << "LEADERBOARD / HALL OF FAME:" << endl;
}


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


int* roll(player* p)
{
	int x = 1 + rand() % DICE;
	int y = 1 + rand() % DICE;
	int item[2];
	item[0] = x;
	item[1] = y;

	p->roll[0] = x;
	p->roll[1] = y;
	p->movecount = 2;
	if (x == y) { p->movecount += 2; } //dodatkowe ruchy dla dubletu

	return item;
}


void rollInfo(player* p)
{
	if (p->roll[0] != 0 && p->roll[1]) {
		cout << "\n\tGracz " << p->id << " wyrzucil [" << p->roll[0] << "] i [" << p->roll[1] << "]";
		if (p->roll[0] == p->roll[1])
		{
			cout << " i [" << p->roll[0] << "] i [" << p->roll[1] << "]";

		}
		cout << endl << endl;
	}
}


void clrPM(player* p)
{
	for (int i = 0; i < ARR; i++)
	{
		p->pmarr[i][0] = 0;
		p->pmarr[i][1] = 0;
	}
	p->possiblemoves = 0;

	for (int i = 0; i < ARR; i++)
	{
		p->mandatorymovesarr[i][0] = 0;
		p->mandatorymovesarr[i][1] = 0;
	}
	p->mandatorymoves = 0;
}


int calculatePoints(board b, int p)
{
	int points[2] = { 0,0 };

	for (int i = 0;i < BSIZE;i++)
	{
		if (b.tab[i] > 0)
		{
			points[0] += (i + 1) * b.tab[i];
		}
		else if (b.tab[i] < 0)
		{
			points[1] += (BSIZE - i) * abs(b.tab[i]);
		}
	}

	points[0] += (BAR)*b.bar[0];
	points[1] += (BAR)*b.bar[1];


	return (points[p]);

}


int getWinnerScore(player* p, board* b)
{
	int score = 1;

	int enemy = (p->id == 1 ? 1 : 0);

	if (b->bar[enemy] > 0)
	{
		score += 2;
		//cout<<"score += 2"<<endl;
	}

	if (b->outside[enemy] == 0)
	{
		score += 1;
		//cout << "score += 1 " << enemy << endl;

	}

	return score;
}


void printInfo(board b)
{
	//system("cls");
	
	cout << "BACKGAMMON.EXE \taplikacja konsolowa" << endl;
	cout << "Dostepne komendy:   ( MOVE {z} {do} )   ( SAVE )   ( LOAD )   ( REPLAY )   ( QUIT )   ( LEADERBOARD )" << endl;
	cout << " bar{" << b.bar[0] << " , " << b.bar[1] << " }";
	cout << " out{" << b.outside[0] << " , " << b.outside[1] << " }";
	cout << " round{ " << b.round << " }" << endl << endl;

}

void printBoard1(board b)
{
	//step 1
	for (int i = BSIZE / 2; i < BSIZE; i++)
	{
		cout << "   " << i + 1;
		if (i == BSIZE - HOMELEN - 1) cout << "   |GR2 |";
	}
	cout << "   | GR2 | POINTS: " << calculatePoints(b, 1) << endl;
	for (int i = 0;i < BRDWIDTH;i++)
	{
		cout << "=";
	}
	cout << "[BAR ]";
	for (int i = 0;i < BRDWIDTH;i++)
	{
		cout << "=";
	}
	cout << "[COURT]" << endl;


	for (int i = BSIZE / 2; i < BSIZE; i++)
	{
		cout << "   " << (b.tab[i] < 0 ? "" : " ") << b.tab[i];
		if (i == BSIZE - HOMELEN - 1) cout << "   | " << (b.bar[1] > 9 ? "" : "0") << b.bar[1] << " |";
		if (i == BSIZE - 1) cout << "   | " << (b.outside[1] > 9 ? "" : "0") << b.outside[1] << "  |";


	}
	cout << endl;
}

void printBoard2(board b)
{
	//step 2
	for (int j = 0;j <= BRDHEIGHT;j++) // 8 pionkow
	{

		for (int i = BSIZE / 2; i < BSIZE; i++)
		{

			if (b.tab[i] != 0)
			{
				cout << "   " << (b.tab[i] > j ? "a1" : (b.tab[i] < -j ? "B2" : ".."));
			}
			else
			{
				cout << "   ..";
			}

			if (i == BSIZE - HOMELEN - 1)
			{
				cout << "   | " << (b.bar[1] > BRDHEIGHT - j ? "B2 |" : "   |");

			}
			if (i == BSIZE - 1)
			{
				cout << "   |" << (b.outside[1] > BRDHEIGHT - j ? "B2 " : "   ") << (b.outside[1] > 2 * BRDHEIGHT - j + 1 ? "B2" : "  ") << "|";

			}

		}
		cout << endl;
	}

	for (int i = 0;i < BRDWIDTH;i++)
	{
		cout << " ";
	}
	cout << "[ 25 ]";

	for (int i = 0;i < BRDWIDTH;i++)
	{
		cout << " ";
	}
	cout << "[  0  ]" << endl;
}

void printBoard3(board b)
{
	//step 3
	for (int j = BRDHEIGHT;j >= 0;j--) // 8 pionkow
	{

		for (int i = BSIZE / 2 - 1; i >= 0; i--)
		{

			if (b.tab[i] != 0)
			{
				cout << "   " << (b.tab[i] > j ? "a1" : (b.tab[i] < -j ? "B2" : ".."));
			}
			else
			{
				cout << "   ..";
			}

			if (i == HOMELEN)
			{
				cout << "   | " << (b.bar[0] > BRDHEIGHT - j ? "a1 |" : "   |");
			}
			if (i == 0)
			{
				cout << "   |" << (b.outside[0] > BRDHEIGHT - j ? "a1 " : "   ") << (b.outside[0] > 2 * BRDHEIGHT - j + 1 ? "a1" : "  ") << "|";

			}

		}
		cout << endl;
	}
}

void printBoard4(board b)
{
	//step 4
	for (int i = BSIZE / 2 - 1; i >= 0; i--)
	{
		cout << "   " << (b.tab[i] < 0 ? "" : " ") << b.tab[i];
		if (i == HOMELEN) cout << "   | " << (b.bar[0] > 9 ? "" : "0") << b.bar[0] << " |";
		if (i == 0) cout << "   | " << (b.outside[0] > 9 ? "" : "0") << b.outside[0] << "  |";

	}
	cout << endl;
	for (int i = 0;i < BRDWIDTH;i++)
	{
		cout << "=";
	}
	cout << "[BAR ]";
	for (int i = 0;i < BRDWIDTH;i++)
	{
		cout << "=";
	}
	cout << "[COURT]" << endl;
	for (int i = BSIZE / 2 - 1; i >= 0; i--)
	{
		cout << "   " << (i < 9 ? "0" : "") << i + 1;
		if (i == HOMELEN) cout << "   |GR1 |";
		if (i == 0) cout << "   | GR1 | POINTS: " << calculatePoints(b, 0) << endl;
	}



	cout << endl;
}


void printBoard(board b)
{

	printInfo(b);

	printBoard1(b);
	printBoard2(b);
	printBoard3(b);
	printBoard4(b);

	//step 1

	//step 2

	//step 3

	//step 4
}


void loadLeaderboard(board b)
{
	FILE* file;

	fopen_s(&file, "leaderboard.txt", "r");

	char ns[ARRL][ARR];//nicks
	int sc[ARRL];//scores

	int i = 0;
	while (!feof(file) && i < ARRL) {
		char nick[ARR];
		int score;
		fscanf_s(file, "%s %d ", nick, ARR, &score);
		//cout << nick << ": " << score << endl;

		int j = 0;
		for (j;nick[j] != '\0';j++)
		{
			ns[i][j] = nick[j];
		}

		ns[i][j] = '\0';
		sc[i] = score;
		i++;
	}
	fclose(file);

	for (int k = 0; k < i; k++)
	{
		for (int l = 0; l < i - 1; l++)
		{
			if (sc[l] < sc[l + 1])
			{
				swap(sc[l], sc[l + 1]);
				swap(ns[l], ns[l + 1]);

			}
		}
	}
	printLB();

	for (int k = 0;k < i;k++)
	{
		cout << "\t" << ns[k] << ": " << sc[k] << endl;
	}

	cout << "\n\n\n\n\n";

	system("pause");
	printBoard(b);



}


void saveLeaderboard(char n[ARR], int p)
{
	FILE* f;

	fopen_s(&f, "leaderboard.txt", "r");

	char ns[ARRL][ARR]; //nicks
	int sc[ARRL]; //scores

	int i = 0;
	while (!feof(f) && i < ARRL) {
		char nk[ARR]; //nick
		int s; //score
		fscanf_s(f, "%s %d ", nk, ARR, &s);

		int j = 0;
		for (j;nk[j] != '\0';j++)
		{
			ns[i][j] = nk[j];
		}

		ns[i][j] = '\0';
		sc[i] = s;
		i++;
	}
	fclose(f);

	int found = 0;
	for (int l = 0;l < i;l++)
	{
		if (!strcmp(ns[l], n))
		{
			sc[l] += p;
			found = 1;
			break;
		}
	}

	if (!found)
	{
		int j = 0;
		for (j;n[j] != '\0';j++)
		{
			ns[i][j] = n[j];
		}

		ns[i][j] = '\0';
		sc[i] = p;
		i++;
	}

	fopen_s(&f, "leaderboard.txt", "w"); //zapis do pliku

	int j = 0;
	while (j < i) {

		fprintf_s(f, "%s %d ", ns[j], sc[j]);
		j++;
	}
	fclose(f);
}


int isLegalMove(int rollresult[2], player* p, board* b, int playerinput[2])
{

	for (int j = 0; j < p->possiblemoves; j++)
	{
		if (p->pmarr[j][0] == playerinput[0] && p->pmarr[j][1] == playerinput[1])
		{
			//cout << "legalny ruch" << endl;
			return 1;

		}
	}
	return 0;



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


void getLegalOutsides1(int rr[2], player* p, board b)
{
	//rr = rollresult
	int pm[ARR][2]; //possiblemoves
	int i = 0;
	int br = b.bar[(p->id == 1 ? 0 : 1)];

	for (int k = 0;k < 2;k++) { //dla obu kostek
		int moves = 0;
		for (int h = HOMELEN - 1;h >= 0;h--) { //pozycje od 6 do 1 (dom gracza 1)
			if (b.tab[h] > 0) { //jezeli jest pionek
				if (rr[k] != 0) {
					if (1 + h - rr[k] == 0) { //mozliwe wejscie
						pm[i][0] = h + 1;
						pm[i][1] = 0;
						i++;
					}
				}
			}
		}
		if (moves == 0)
		{
			for (int h = HOMELEN - 1;h >= 0 && !moves;h--) { //pozycje od 6 do 1 (dom gracza 1)
				if (b.tab[h] > 0) { //jezeli jest pionek
					if (rr[k] != 0) {
						if (h - rr[k] < 0) { //mozliwe wejscie
							pm[i][0] = h + 1;
							pm[i][1] = 0;
							i++;
							moves++;
						}
					}
				}
			}
		}
	}

	int a = p->possiblemoves;


	for (int l = 0; l < i;l++)
	{
		p->pmarr[l + a][0] = pm[l][0];
		p->pmarr[l + a][1] = pm[l][1];

	}
	p->possiblemoves += i;
}

void getLegalOutsides2(int rr[2], player* p, board b)
{
	//rr = rollresult
	int pm[ARR][2]; //possiblemoves
	int i = 0;
	int br = b.bar[(p->id == 1 ? 0 : 1)];

	for (int k = 0;k < 2;k++) {//dla obu kostek
		int moves = 0;
		for (int h = (BSIZE - HOMELEN);h < BSIZE;h++) { //pozycje od 18 do 24 (dom gracza 2)
			if (b.tab[h] < 0) { //jezeli jest pionek
				if (rr[k] != 0) {
					if (h + rr[k] == BSIZE) { //mozliwe wejscie
						pm[i][0] = h + 1;
						pm[i][1] = 0;
						i++;
						moves++;
					}
				}
			}
		}
		if (moves == 0)
		{
			for (int h = (BSIZE - HOMELEN);h < BSIZE && !moves;h++) { //pozycje od 18 do 24 (dom gracza 2)
				if (b.tab[h] < 0) { //jezeli jest pionek
					if (rr[k] != 0) {
						if (h + rr[k] > BSIZE - 1) { //mozliwe wejscie
							pm[i][0] = h + 1;
							pm[i][1] = 0;
							i++;
							moves++;

						}
					}
				}
			}

		}
	}

	int a = p->possiblemoves;


	for (int l = 0; l < i;l++)
	{
		p->pmarr[l + a][0] = pm[l][0];
		p->pmarr[l + a][1] = pm[l][1];

	}
	p->possiblemoves += i;
}


void getLegalOutsides(int rollresult[2], player* p, board b)
{


	if (p->id == 1) { //jesli jestesmy graczem 1

		getLegalOutsides1(rollresult, p, b);
	}
	else //jesli jestesmy graczem 2
	{
		getLegalOutsides2(rollresult, p, b);
	}

}


void getLegalDoubles1a(int rr, player* p, board b)
{
	int pm[ARR][2]; //possiblemoves
	int i = 0, m = 0;
	int br = b.bar[(p->id == 1 ? 0 : 1)];
	int mm[ARR][2]; //mandatorymoves
	int mvs = p->movecount;
	//int mvs = 4;

	if (rr == 0)
	{
		rr = p->roll[0];
	}


	for (int h = BSIZE - 1;h >= 0;h--)
	{
		if (b.tab[h] > 0)
		{
			for (int k = 1;k <= mvs;k++) {
				if (h - rr * k >= 0) {
					if (b.tab[h - rr * k] >= -1)
					{
						pm[i][0] = h + 1;
						pm[i][1] = h + 1 - rr * k;
						i++;
					}
					else { k = STOP;break; }
				}

			}
		}
	}

	int a = p->possiblemoves;

	for (int l = 0; l < i;l++)
	{
		p->pmarr[l + a][0] = pm[l][0];
		p->pmarr[l + a][1] = pm[l][1];
	}
	p->possiblemoves += i;

}

void getLegalDoubles2a(int rr, player* p, board b)
{
	int pm[ARR][2]; //possiblemoves
	int i = 0, m = 0;
	int br = b.bar[(p->id == 1 ? 0 : 1)];
	int mm[ARR][2]; //mandatorymoves
	int mvs = p->movecount;
	//int mvs = 4;

	if (rr == 0)
	{
		rr = p->roll[0];
	}

	if (rr != 0) {
		for (int h = 0;h < BSIZE;h++)
		{
			if (b.tab[h] < 0)
			{

				for (int k = 1;k <= mvs;k++) {
					if (h + rr * k <= BSIZE - 1) {
						if (b.tab[h + rr * k] <= 1)
						{
							pm[i][0] = h + 1;
							pm[i][1] = h + 1 + rr * k;
							i++;
						}
						else { k = STOP;break; }
					}
				}
			}
		}
	}


	int a = p->possiblemoves;

	for (int l = 0; l < i;l++)
	{
		p->pmarr[l + a][0] = pm[l][0];
		p->pmarr[l + a][1] = pm[l][1];
	}
	p->possiblemoves += i;

}

int getLegalDoubles1(int rr, player* p, board b)
{
	int pm[ARR][2]; //possiblemoves
	int i = 0, m = 0;
	int br = b.bar[(p->id == 1 ? 0 : 1)];
	int mm[ARR][2]; //mandatorymoves
	int mvs = p->movecount;
	//int mvs = 4;

	if (rr == 0)
	{
		rr = p->roll[0];
	}

	if (br == 0) { //jesli nie jestesmy na barze

		getLegalDoubles1a(rr, p, b);
		return 0;
	}
	else if (br == 1)//jesli jestesmy na barze
	{
		//if (rr != 0) {
		for (int k = 1;k <= mvs;k++) {
			if (b.tab[BSIZE - rr * k] >= -1)
			{
				pm[i][0] = BAR;
				pm[i][1] = BAR - rr * k;
				i++;
			}
			else { k = STOP;break; }
		}
		//}
	}
	else if (br >= 2)
	{
		//if (rr != 0) {
		if (b.tab[BSIZE - rr] >= -1)
		{
			pm[i][0] = BAR;
			pm[i][1] = BAR - rr;
			i++;
		}
		//}
	}


	int a = p->possiblemoves;

	for (int l = 0; l < i;l++)
	{
		p->pmarr[l + a][0] = pm[l][0];
		p->pmarr[l + a][1] = pm[l][1];
	}
	p->possiblemoves += i;
	return 0;
}

int getLegalDoubles2(int rr, player* p, board b)
{
	int pm[ARR][2]; //possiblemoves
	int i = 0, m = 0;
	int br = b.bar[(p->id == 1 ? 0 : 1)];
	int mm[ARR][2]; //mandatorymoves
	int mvs = p->movecount;
	//int mvs = 4;

	if (rr == 0)
	{
		rr = p->roll[0];
	}

	if (br == 0) { //jesli nie jestesmy na barze
		getLegalDoubles2a(rr, p, b);
		return 0;
	}
	else if (br == 1)//jesli jestesmy na barze
	{
		if (rr != 0) {
			for (int k = 1;k <= mvs;k++) {
				if (b.tab[rr * k - 1] <= 1)
				{
					pm[i][0] = BAR;
					pm[i][1] = rr * k;
					i++;
				}
				else { k = STOP;break; }
			}
		}
	}
	else if (br >= 2)
	{
		if (rr != 0) {
			if (b.tab[rr - 1] <= 1)
			{
				pm[i][0] = BAR;
				pm[i][1] = rr;
				i++;
			}
		}
	}


	int a = p->possiblemoves;

	for (int l = 0; l < i;l++)
	{
		p->pmarr[l + a][0] = pm[l][0];
		p->pmarr[l + a][1] = pm[l][1];
	}
	p->possiblemoves += i;
	return 0;
}


void getLegalDoubles(int rollresult, player* p, board b)
{


	if (p->id == 1) { //jesli jestesmy graczem 1
		getLegalDoubles1(rollresult, p, b);
	}
	else //jesli jestesmy graczem 2
	{
		getLegalDoubles2(rollresult, p, b);
	}

}


void insrt(int pm[ARR][2], int i, int mm[ARR][2], int m, int rr[2], player* p, board b)
{
	//insrt(pm, i, mm, m, rr, p, b);

	refactorMandatoryMoves(mm, m, p);


	for (int l = 0; l < i;l++)
	{
		p->pmarr[l][0] = pm[l][0];
		p->pmarr[l][1] = pm[l][1];
	}


	p->possiblemoves = i;

	if (checkDbl(rr)) { getLegalDoubles(rr[0], p, b); }

	if (checkOutside(p, &b)) { getLegalOutsides(rr, p, b); }


}


void refactorMandatoryMoves(int mmarr[ARR][2], int m, player* p)
{
	int mandatorymoves[ARR][2];
	int closest = 0, mm = 0;
	if (m > 0)
	{
		closest = mmarr[0][1];
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


void getLegalMoves1(int rr[2], player* p, board b)
{
	clrPM(p);

	int i = 0, m = 0;

	int pm[ARR][2];
	int mm[ARR][2];

	int br = b.bar[(p->id == 1 ? 0 : 1)];

	for (int k = 0;k < 2;k++) {
		if (rr[k] != 0) {
			if (b.tab[BSIZE - rr[k]] >= -1)
			{
				if (b.tab[BSIZE - rr[k]] == -1) //mandatory capture
				{
					mm[m][0] = BAR;
					mm[m][1] = BAR - rr[k];
					m++;
				}

				pm[i][0] = BAR;
				pm[i][1] = BAR - rr[k];
				i++;


				if (br == 1) {
					int j = (k ? 0 : 1);
					if (b.tab[BSIZE - rr[k] - rr[j]] >= -1)
					{
						if (rr[k] != 0 && rr[j] != 0) {
							if (b.tab[BSIZE - rr[k]] == -1 || b.tab[BSIZE - rr[k] - rr[j]] == -1) //mandatory capture
							{
								mm[m][0] = BAR;
								mm[m][1] = BAR - rr[k] - rr[j];
								m++;
							}

							pm[i][0] = BAR;
							pm[i][1] = BAR - rr[k] - rr[j];
							i++;
						}

						//sprawdza czy suma jest legalna tylko gdy 1 pionek na barze
					}
				}
			}
		}
	}

	insrt(pm, i, mm, m, rr, p, b);


}

void getLegalMoves2(int rr[2], player* p, board b)
{
	clrPM(p);

	int i = 0, m = 0;

	int pm[ARR][2];
	int mm[ARR][2];

	int br = b.bar[(p->id == 1 ? 0 : 1)];

	for (int k = 0;k < 2;k++) {
		if (rr[k] != 0) {

			if (b.tab[rr[k] - 1] <= 1)
			{
				if (b.tab[rr[k] - 1] == 1) //mandatory capture
				{
					mm[m][0] = BAR;
					mm[m][1] = rr[k];
					m++;
				}

				pm[i][0] = BAR;
				pm[i][1] = rr[k];
				i++;


				if (br == 1) {
					int j = (k ? 0 : 1);
					if (b.tab[rr[k] + rr[j] - 1] <= 1)
					{
						if (rr[k] != 0 && rr[j] != 0) {

							if (b.tab[rr[k] - 1] == 1 || b.tab[rr[k] + rr[j] - 1] == 1) //mandatory capture
							{
								mm[m][0] = BAR;
								mm[m][1] = rr[k] + rr[j];
								m++;
							}

							pm[i][0] = BAR;
							pm[i][1] = rr[k] + rr[j];
							i++;
						}

						//sprawdza czy suma jest legalna tylko gdy 1 pionek na barze
					}
				}
			}
		}
	}

	insrt(pm, i, mm, m, rr, p, b);

}

void getLegalMoves3(int rr[2], player* p, board b)
{
	clrPM(p);

	int i = 0, m = 0;

	int pm[ARR][2];
	int mm[ARR][2];

	int br = b.bar[(p->id == 1 ? 0 : 1)];

	for (int h = BSIZE - 1;h >= 0;h--)
	{
		if (b.tab[h] > 0) { // jezeli jest pionek
			for (int k = 0;k < 2;k++) { // dla obu rollresult
				if (rr[k] != 0) {
					if (h - rr[k] >= 0) {
						if (b.tab[h - rr[k]] >= -1)
						{
							if (b.tab[h - rr[k]] == -1) //mandatory capture
							{
								mm[m][0] = h + 1;
								mm[m][1] = h + 1 - rr[k];
								m++;
							}


							pm[i][0] = h + 1;
							pm[i][1] = h + 1 - rr[k];
							i++;

							if (br <= 1) {
								int j = (k ? 0 : 1);
								if (h - rr[k] - rr[j] >= 0) {
									if (b.tab[h - rr[k] - rr[j]] >= -1)
									{
										if (b.tab[h - rr[k]] == -1 || b.tab[h - rr[k] - rr[j]] == -1)
										{
											mm[m][0] = h + 1;
											mm[m][1] = h + 1 - rr[k] - rr[j];
											m++;
										}

										pm[i][0] = h + 1;
										pm[i][1] = h + 1 - rr[k] - rr[j];
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

	insrt(pm, i, mm, m, rr, p, b);

}

void getLegalMoves4(int r[2], player* p, board b)
{
	clrPM(p);

	//r = rollresult
	int i = 0, m = 0;

	int u[ARR][2]; //possiblemoves
	int n[ARR][2]; // mandatorymoves

	int br = b.bar[(p->id == 1 ? 0 : 1)];

	for (int h = 0;h < BSIZE;h++)
	{
		if (b.tab[h] < 0) { // jezeli jest pionek
			for (int k = 0;k < 2;k++) { // dla obu rollresult
				if (r[k] != 0) {
					if (h + r[k] <= BSIZE - 1) {
						if (b.tab[h + r[k]] <= 1)
						{
							if (b.tab[h + r[k]] == 1) //mandatory capture
							{
								n[m][0] = h + 1;
								n[m][1] = h + 1 + r[k];
								m++;
							}

							u[i][0] = h + 1;
							u[i][1] = h + 1 + r[k];
							i++;

							if (br <= 1) {
								int j = (k ? 0 : 1);
								if (h + r[k] + r[j] <= BSIZE - 1) {
									if (b.tab[h + r[k] + r[j]] <= 1)
									{
										if (b.tab[h + r[k]] == 1 || b.tab[h + r[k] + r[j]] == 1)
										{
											n[m][0] = h + 1;
											n[m][1] = h + 1 + r[k] + r[j];
											m++;
										}

										//if (r[k] != 0) {
										u[i][0] = h + 1;
										u[i][1] = h + 1 + r[k] + r[j];
										i++;
										//}

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

	insrt(u, i, n, m, r, p, b);

}


int getLegalMoves(int rr[2], player* p, board b)
{
	int br, i = 0, m = 0;
	short x = p->id;
	int pm[ARR][2];
	int mm[ARR][2];

	clrPM(p);


	if (rr[0] > rr[1])//defaultowo posortuje rollresult
	{
		br = rr[0];
		rr[0] = rr[1];
		rr[1] = br;
	}

	br = b.bar[(p->id == 1 ? 0 : 1)];

	if (br != 0) //jesli jestesmy na barze
	{
		switch (x)
		{
		case 1: //-5,0,0,0,0,2 pozytywne


			getLegalMoves1(rr, p, b);
			return 0;

			break;

		case 2: //-2,0,0,0,0,5

			getLegalMoves2(rr, p, b);
			return 0;



			break;
		}

	}
	else //jesli nie jestesmy na barze
	{
		switch (x)//-2,0,0,0,0,5,0,3,0,0,0,-5,5,0,0,0,-3,0,-5,0,0,0,0,2
		{
		case 1: //test dla g1 do tylu

			getLegalMoves3(rr, p, b);
			return 0;


			break;
		case 2:

			getLegalMoves4(rr, p, b);
			return 0;


			break;

		}
	}

	insrt(pm, i, mm, m, rr, p, b);
	return 0;

}

void checkWin(int rollresult[2], player* p, board* b, int playerinput[2])
{
	int legal = isLegalMove(rollresult, p, b, playerinput);
	int os = checkOutside(p, b);


	if (legal && os) //outside and wincondition
	{
		if (playerinput[1] == 0) { b->outside[p->id - 1]++; }
		if (b->outside[p->id - 1] == MAXOUTSIDE)
		{
			if (b->round != 1)
			{
				cloneHistory(*b); // klonuje historie po wygraniu gry
				char nick[ARR];
				//system("cls");
				printBoard(*b);
				int score = getWinnerScore(p, b);
				cout << "\tWygrana! " << "Pojedynek wygral gracz " << p->id << ". Wynik: " << score << endl;
				cout << "Podaj nick, ktory zostanie zapisany na liscie wynikow: ";

				cin >> nick;

				cout << nick << endl;

				saveLeaderboard(nick, score);

				//zapis do pliku
				main(); //GRATULACJE WYGRALES


			}
		}
	}
}


int move(int rollresult[2], player* p, board* b, int playerinput[2], player* enemy)
{
	clrPM(p);
	getLegalMoves(rollresult, p, *b);


	int legal = isLegalMove(rollresult, p, b, playerinput);
	int dublet = checkDbl(rollresult);
	int os = checkOutside(p, b);
	int diff = (playerinput[0] > playerinput[1] ? playerinput[0] - playerinput[1] : playerinput[1] - playerinput[0]);

	//cout <<"diff "<< diff << endl;

	if (legal)
	{
		if (p->id == 1)
		{
			//if (playerinput[0] == BAR) { diff = playerinput[1]; }
			//if (playerinput[1] == 0) { diff = BAR - playerinput[0]; }

			if (diff == 3 * rollresult[0] && dublet) //dublety
			{
				//cout << "rekurencja 3:)" << endl;
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
					//p->movecount -= 3;

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
				//cout << "rekurencja 4:)" << endl;
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
					//p->movecount -= 4;

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
				if (rollresult[0] == 0 && rollresult[1] == 0)
				{
					rollresult[0] = p->roll[0];
					rollresult[1] = p->roll[1];
					//cout << rollresult[0] << " && " << rollresult[1] << endl;

				}

				//cout << "rekurencja :)" << endl;
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
					checkWin(rollresult, p, b, playerinput);
					return 2;

				}
				else if (isLegalMove(rollresult, p, b, pi1))
				{

					move(rr1, p, b, pi1, enemy);

					move(rr2, p, b, pi2, enemy);
					checkWin(rollresult, p, b, playerinput);
					return 2;

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

					//p->points -= playerinput[1];

				}
				else
				{
					b->tab[playerinput[0] - 1]--;
					//p->points -= (diff + 1);
				}

				if (b->tab[playerinput[1] - 1] == -1) //zbijanie
				{
					b->tab[playerinput[1] - 1]++;

					b->bar[1]++;
					//enemy->points += (playerinput[1]);
				}
				b->tab[playerinput[1] - 1]++;

			}
		}
		else //player2
		{
			int newpi0 = playerinput[0];
			if (playerinput[0] == BAR) { diff = playerinput[1];newpi0 = 0; }
			if (playerinput[1] == 0) { diff = BAR - playerinput[0]; }

			if (diff == 3 * rollresult[0] && dublet) //dublety 2
			{
				//cout << "rekurencja 3:)" << endl;
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
					//p->movecount -= 3;

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
				//cout << "rekurencja 4:)" << endl;
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
					//p->movecount -= 4;

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
				if (rollresult[0] == 0 && rollresult[1] == 0)
				{
					rollresult[0] = p->roll[0];
					rollresult[1] = p->roll[1];
					cout << rollresult[0] << " && " << rollresult[1] << endl;

				}

				//cout << "rekurencja :)" << endl;
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
				//cout << "rekurencja :)" << endl;

				if (isLegalMove(rollresult, p, b, pi1))
				{

					move(rr1, p, b, pi1, enemy);


					move(rr2, p, b, pi2, enemy);
					checkWin(rollresult, p, b, playerinput);
					return 2;


				}
				else if (isLegalMove(rollresult, p, b, pi3))
				{
					//cout << "opcja2" << endl;


					move(rr2, p, b, pi3, enemy);


					move(rr1, p, b, pi4, enemy);
					checkWin(rollresult, p, b, playerinput);
					return 2;


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

					//p->points -= (BSIZE -playerinput[1]);
				}
				else
				{
					b->tab[playerinput[0] - 1]++;
					//p->points -= (diff + 1);
				}


				if (b->tab[playerinput[1] - 1] == 1) //zbijanie
				{
					b->tab[playerinput[1] - 1]--;

					b->bar[0]++;
					//enemy->points += (BSIZE - playerinput[1]);
				}
				b->tab[playerinput[1] - 1]--;

			}

		}


		if (diff == rollresult[0] || (os && diff < rollresult[0])) //obsluga polowicznych ruchow
		{
			p->movecount--;
			checkWin(rollresult, p, b, playerinput);
			return 0;
		}
		else if (diff == rollresult[1] || (os && diff < rollresult[1]))
		{
			p->movecount--;
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
		p->movecount -= 2;
		checkWin(rollresult, p, b, playerinput);
		return 2;
	}
	else
	{
		cout << "nielegalny ruch " << playerinput[0] << " " << playerinput[1] << endl;
		printHints(rollresult, p, b);
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
		b->customsave = 1;

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

	b->round = 1;

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


void cloneHistory(board b)
{
	if (b.customsave == 0)
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
	else
	{
		cout << "nie mozna zapisac historii wczytaniej gry jako powtorki" << endl;
	}
}


int replayModeMenu(player* p1, player* p2, board* b, int n)
{

	printBoard(*b);


	cout << "Dostepne komendy :   (NEXT)   (PREV)   (START)   (END)   (QUIT)" << endl;

	char pi[ARR];
	while (1)
	{
		//cout<<"gra here"<<endl;
		cin >> pi;

		if (!strcmp(pi, "quit") || !strcmp(pi, "QUIT")) { exit(1); return -1; }
		else if (!strcmp(pi, "next") || !strcmp(pi, "NEXT")) { replayMode(p1, p2, b, n + 5);return 0; }
		else if (!strcmp(pi, "prev") || !strcmp(pi, "PREV")) { replayMode(p1, p2, b, n - 5);return 0; }
		else if (!strcmp(pi, "start") || !strcmp(pi, "START")) { replayMode(p1, p2, b, 0);return 0; }
		else if (!strcmp(pi, "end") || !strcmp(pi, "END")) { replayMode(p1, p2, b, -1);return 0; }

	}

	return 0;
}


int replayLen()
{
	FILE* file;

	fopen_s(&file, "replay.txt", "r");

	int num = 0;
	while (!feof(file)) {
		int a;
		fscanf_s(file, "%d ", &a);
		num++;
	}
	fclose(file);

	return num;
}


int replayMode(player* p1, player* p2, board* b, int n)
{
	loadGame(p1, p2, b, 1);

	FILE* file;


	//fopen_s(&file, "replay.txt", "r");

	int num = 0;
	int i = 0;
	int len = replayLen();

	int newrr[2];
	int newpi[2];
	player* newp1 = p1;
	player* newp2 = p2;

	/*while (!feof(file)) {
		int a;
		fscanf_s(file, "%d ", &a);
		len++;
	}
	fclose(file);*/

	fopen_s(&file, "replay.txt", "r");

	if (n < 0)
	{
		n = len;
	}


	while (!feof(file) && i < n) {
		int a; // odczyt z pliku
		fscanf_s(file, "%d ", &a);

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
			newp1->movecount = 4;

			move(newrr, newp1, b, newpi, newp2);
			num++;

		}

		i++;
		//}
	}
	fclose(file);

	replayModeMenu(p1, p2, b, n);

	return 0;
}


void printHints(int rollresult[2], player* p, board* b)
{

	getLegalMoves(rollresult, p, *b);

	int a = p->possiblemoves;
	int c = p->mandatorymoves;
	if (b->bar[p->id - 1] > 0) { c = 0; }
	int ruchy[ARR][2];

	cout << "mozliwe ruchy: " << p->movecount << endl;

	for (int i = 0; i < a; i++)
	{
		ruchy[i][0] = p->pmarr[i][0];
		ruchy[i][1] = p->pmarr[i][1];

		cout << (ruchy[i][0] > 9 ? "" : " ") << ruchy[i][0] << " " << (ruchy[i][1] > 9 ? "" : " ") << ruchy[i][1] << ";  ";
		if ((i + 1) % 10 == 0)
		{
			cout << endl;
		}

	}
	cout << endl;
	//cout << "liczba ruchow: " << a <<" xd " <<c<< endl;

	for (int i = 0; i < c; i++)
	{
		cout << "Przymusowe bicie: " << p->mandatorymovesarr[i][0] << " " << p->mandatorymovesarr[i][1] << endl;

	}
}


int valCheck(int v, int rr[2], player* p, board* b, player* e, int ri[2])
{
	char pr[]= "wykonano polowiczny ruch "; //propmt

	printBoard(*b);

	if (v != -1)
	{
		saveHistory(ri, *p, b, rr);
	}

	if (v == 0)
	{
		cout << pr << rr[1] << "\n"; //rekurencja :)
		int r[2] = { 0,rr[1] };
		readinput(r, p, b, e, 0, 0);
	}
	if (v == 1)
	{
		cout << pr << rr[0] << "\n"; //rekurencja :)
		int r[2] = { 0,rr[0] };
		readinput(r, p, b, e, 0, 0);
	}
	if (v == 2)
	{
		cout << "wykonano ruch\n";
	}
	if (v == 3)
	{
		cout << pr <<"dubletowy " << rr[1] << "\n"; //rekurencja :)
		int r[2] = { 0,rr[1] };
		//i1 = 5;
		readinput(r, p, b, e, 0, 0);
	}
	if (v == 4)
	{
		//cout << "wykonano ruch dubletowy\n";
		//i1 = 5;
		
		return 0;


	}
	if (v == -1)
	{
		cout << "prosze sprobowac ponownie\n";
		if (checkDbl(rr))
		{
			//i1 = 5;
		}
		readinput(rr, p, b, e, 0, 0);

	}
}

int cinCheck(char pi[MAXARGLEN], int rr[2], player* p, board* b, player* e)
{
	if (!strcmp(pi, "quit")) {return 1; }
	else if (!strcmp(pi, "save")){
		
		saveGame(*p, *e, *b);
		return 2;
	}
	else if (!strcmp(pi, "load")) {
		
		loadGame(p, e, b, 0);
		return 3;
	}
	else if (!strcmp(pi, "leaderboard")) {
		
		loadLeaderboard(*b);
		return 4;
	}
	else if (!strcmp(pi, "replay")) {
		
		(p->id == 1 ? replayMode(p, e, b, -1) : replayMode(e, p, b, -1));
		return 5;
	}
	else if (!strcmp(pi, "move") || !strcmp(pi, "MOVE")){
		return 6;
	}
	return 0;
}

int isEmpty(player* p, board* b, int rr[2])
{
	rollInfo(p);
	printHints(rr, p, b);

	if (p->possiblemoves == 0 || p->movecount <= 0) {
		
		printBoard(*b);
		return 1;
	}
	return 0;

}



int readinput(int rr[2], player* p, board* b, player* e, int a1, int a2)
{
	//getLegalMoves(rollresult, p, *b);
	//rr = rollresult;
	//e = enemy;

	int i1 = 1;
	if (rr[0] == rr[1])
	{
		i1 = 0;
	}

	for (i1; i1 < 2; i1++)
	{
		
		char pi[MAXARGLEN];
		int arg1, arg2;

		if (isEmpty(p,b, rr))
			return 0;

		if (a1 && a2)
		{
			pi[0] = 'm';
			pi[1] = 'o';
			pi[2] = 'v';
			pi[3] = 'e';
			pi[4] = '\0';
			arg1 = a1;
			arg2 = a2;
		}
		else { cin >> pi; }
		
		//checking 
		int x=cinCheck(pi, rr, p, b,e);

		if (x==1) { exit(1); return -1; }
		if (x == 2) {
			AGAIN
		}
		if (x == 3)
		{
			AGAIN
		}
		if (x == 4)
		{
			AGAIN
		}
		if (x == 5)
		{
			AGAIN
		}
		if (x == 6)
		{
			if (!(a1 && a2)) { cin >> arg1 >> arg2; }

			//cout << pi << " - " << arg1 << " - " << arg2 << endl;
			int ri[2] = { arg1,arg2 };
			//ri=resultinput

			//kontrola ruchu
			

			if (!checkMandatoryMove(p, b, ri))
			{
				PROMPT
				if (checkDbl(rr)) { i1 = 5; }
				readinput(rr, p, b, e, 0, 0);
				return 0;
			}

			//kontekst menu

			valCheck(move(rr, p, b, ri, e), rr, p, b, e, ri);


		}
	}
	//return 0;


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
		cout << "\n\tGracz 1 zaczyna\n" << endl;
		p1->id = 1;
		p2->id = 2;
		p1->roll[0] = x;
		p1->roll[1] = y;

		if (readinput(item, p1, b, p2, 0, 0) == -1) { return -1; }
		b->round++;

		return 0;
	}
	else
	{
		cout << "\n\tGracz 2 zaczyna\n" << endl;
		p1->id = 2;
		p2->id = 1;
		p1->roll[0] = x;
		p1->roll[1] = y;

		if (readinput(item, p1, b, p2, 0, 0) == -1) { return -1; }
		b->round++;

		return 1;
	}

}
