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
	if (x == y) { p->movecount = 4; }


	return item;
	//w miare randomowe xd
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
	cout<<"score: "<<score<<endl;
	cout<<"bar: "<< b->bar[enemy] <<endl;
	cout<<"out: "<< b->outside[enemy] <<endl;

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


void printBoard(board b)
{

	printInfo(b);


	//step 1
	for (int i = BSIZE / 2; i < BSIZE; i++)
	{
		cout << "   " << i + 1;
		if (i == BSIZE - HOMELEN - 1) cout << "   |GR2 |";
	}
	cout << "   | GR2 | POINTS: " << calculatePoints(b, 1) << endl;
	for (int i = 0;i < 33;i++)
	{
		cout << "=";
	}
	cout << "[BAR ]";
	for (int i = 0;i < 33;i++)
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

	//step 2
	for (int j = 0;j <= 8;j++) // 8 pionkow
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
				cout << "   | " << (b.bar[1] > 8 - j ? "B2 |" : "   |");

			}
			if (i == BSIZE - 1)
			{
				cout << "   |" << (b.outside[1] > 8 - j ? "B2 " : "   ") << (b.outside[1] > 2 * 8 - j + 1 ? "B2" : "  ") << "|";

			}

		}
		cout << endl;
	}

	for (int i = 0;i < 30;i++)
	{
		cout << " ";
	}
	cout << "   [ 25 ]";

	for (int i = 0;i < 30;i++)
	{
		cout << " ";
	}
	cout << "   [  0  ]" << endl;

	//step 3
	for (int j = 8;j >= 0;j--) // 8 pionkow
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
				cout << "   | " << (b.bar[0] > 8 - j ? "a1 |" : "   |");
			}
			if (i == 0)
			{
				cout << "   |" << (b.outside[0] > 8 - j ? "a1 " : "   ") << (b.outside[0] > 2 * 8 - j + 1 ? "a1" : "  ") << "|";

			}

		}
		cout << endl;
	}

	//step 4
	for (int i = BSIZE / 2 - 1; i >= 0; i--)
	{
		cout << "   " << (b.tab[i] < 0 ? "" : " ") << b.tab[i];
		if (i == HOMELEN) cout << "   | " << (b.bar[0] > 9 ? "" : "0") << b.bar[0] << " |";
		if (i == 0) cout << "   | " << (b.outside[0] > 9 ? "" : "0") << b.outside[0] << "  |";

	}
	cout << endl;
	for (int i = 0;i < 33;i++)
	{
		cout << "=";
	}
	cout << "[BAR ]";
	for (int i = 0;i < 33;i++)
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
		if (p->possiblemovesarr[j][0] == playerinput[0] && p->possiblemovesarr[j][1] == playerinput[1])
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
						if (1 + h - rollresult[k] == 0) { //mozliwe wejscie
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
			for (int h = (BSIZE - HOMELEN);h < BSIZE;h++) { //pozycje od 18 do 24 (dom gracza 2)
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
	int mandatorymoves[ARR][2]; //todofix
	int mvs = p->movecount;
	//cout <<"\tmvs:"<< mvs<<endl;
	if (rollresult == 0)
	{
		rollresult = p->roll[0];
	}

	if (p->id == 1) { //jesli jestesmy graczem 1
		if (br == 0) { //jesli nie jestesmy na barze
			if (rollresult != 0) {
				for (int h = BSIZE - 1;h >= 0;h--)
				{
					if (b.tab[h] > 0)
					{
						for (int k = 1;k <= mvs;k++) {
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
				for (int k = 1;k <= mvs;k++) {
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

						for (int k = 1;k <= mvs;k++) {
							if (h + rollresult * k <= BSIZE - 1) {
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
				for (int k = 1;k <= mvs;k++) {
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
				if (b.tab[rollresult - 1] <= 1)
				{
					possiblemoves[i][0] = BAR;
					possiblemoves[i][1] = rollresult;
					i++;
				}
			}
		}
	}



	int a = p->possiblemoves;
	if ((i + a) > ARR) { cout << "za duzo ruchow" << endl; }

	for (int l = 0; l < i;l++)
	{
		p->possiblemovesarr[l + a][0] = possiblemoves[l][0];
		p->possiblemovesarr[l + a][1] = possiblemoves[l][1];
		//cout << possiblemoves[l][0] << " " << possiblemoves[l][1] << endl;

	}
	//cout << i << endl;
	p->possiblemoves += i;

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


void getLegalMoves(int rollresult[2], player* p, board b)
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
				if (b.tab[h] > 0) { // jezeli jest pionek
					for (int k = 0;k < 2;k++) { // dla obu rollresult
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
				if (b.tab[h] < 0) { // jezeli jest pionek
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

	if (p->roll[0]==p->roll[1] || p->movecount>2) { getLegalDoubles(rollresult[0], p, b); }

	if (checkOutside(p, &b)) { getLegalOutsides(rollresult, p, b); }

	//return possiblemoves;
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
				char nick[ARR];
				//system("cls");
				printBoard(*b);
				int score = getWinnerScore(p, b);
				cout << "\tWygrana! " << "Pojedynek wygral gracz " << p->id << ". Wynik: " << score << endl;
				cout << "Podaj nick, ktory zostanie zapisany na liscie wynikow: ";

				cin >> nick;

				cout << nick << endl;

				saveLeaderboard(nick, score);
				//cout<< "wygral gracz " << p->id <<"\n\n\n\n\n\n\n\n\n\n"<<endl;

				//zapis do pliku

				//return 100; //zwyciestwo // wywolaj int main() i zakoncz gre
				main(); //todo todo todo GRATULACJE UZYTKOWNIKU WYGRALES IPHONE // todo todo todo naprawione w zasadzie xd


			}
		}
	}
}


int move(int rollresult[2], player* p, board* b, int playerinput[2], player* enemy)
{
	clearPossibleMoves(p);
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
					p->movecount -= 3;

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
					p->movecount -= 4;

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
					p->movecount -= 3;
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
					p->movecount -= 4;
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
		p->movecount-=2;
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


int replayMode(player* p1, player* p2, board* b, int n)
{
	loadGame(p1, p2, b, 1);

	FILE* file;


	fopen_s(&file, "replay.txt", "r");

	/*for (int i = 0;i < 3*n;i++)
	{*/
	int num = 0;
	int i = 0;
	int len = 0;

	int newrr[2];
	int newpi[2];
	player* newp1 = p1;
	player* newp2 = p2;

	while (!feof(file)) {
		int a;
		fscanf_s(file, "%d ", &a);
		len++;
	}
	fclose(file);

	fopen_s(&file, "replay.txt", "r");

	if (n < 0)
	{
		n = len;
	}

	//cout << n << endl;

	//cout << "historia: ";
	while (!feof(file) && i < n) { // cala historia
		int a;
		fscanf_s(file, "%d ", &a);
		//cout << i << "-";
		//cout << a << " ";

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

			move(newrr, newp1, b, newpi, newp2);
			num++;

		}

		i++;
		//}
	}
	//cout << endl << endl;
	//cout << num << endl;
	printBoard(*b);
	fclose(file);

	cout << "Dostepne komendy :   (NEXT)   (PREV)   (START)   (END)   (QUIT)" << endl;

	char pi[ARR];
	while (1)
	{
		
		cin >> pi;

		if (!strcmp(pi, "quit") || !strcmp(pi, "QUIT")) { exit(1); return -1; }
		else if (!strcmp(pi, "next") || !strcmp(pi, "NEXT")) { replayMode(p1, p2, b, n + 5);return 0; }
		else if (!strcmp(pi, "prev") || !strcmp(pi, "PREV")) { replayMode(p1, p2, b, n - 5);return 0; }
		else if (!strcmp(pi, "start") || !strcmp(pi, "START")) { replayMode(p1, p2, b, 0);return 0; }
		else if (!strcmp(pi, "end") || !strcmp(pi, "END")) { replayMode(p1, p2, b, -1);return 0; }

	}

	return 0;
}


void printHints(int rollresult[2], player* p, board* b)
{

	getLegalMoves(rollresult, p, *b);

	int a = p->possiblemoves;
	int c = p->mandatorymoves;
	if (b->bar[p->id - 1] > 0) { c = 0; }
	int ruchy[ARR][2];

	//if (a == 0 || p->movecount == 0) {
	//	//cout << "pusta tablica" << endl;
	//	//return 0;
	//}
	cout << "mozliwe ruchy: " << p->movecount << endl;

	for (int i = 0; i < a; i++)
	{
		ruchy[i][0] = p->possiblemovesarr[i][0];
		ruchy[i][1] = p->possiblemovesarr[i][1];

		cout << (ruchy[i][0] > 9 ? "" : " ")<< ruchy[i][0] << " " << (ruchy[i][1] > 9 ? "" : " ") << ruchy[i][1] << ";  ";
		if ( (i+1)%10 == 0)
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


int readinput(int rollresult[2], player* p, board* b, player* enemy, int a1, int a2)
{
	

	int i1 = 1;
	if (rollresult[0] == rollresult[1])
	{
		i1 = 0;
	}

	for (i1; i1 < 2; i1++)
	{
		rollInfo(p);
		printHints(rollresult,p,b);
		


		char playerinput[MAXARGLEN];
		int arg1, arg2;

		if (p->possiblemoves == 0 || p->movecount <= 0) {
			//cout << "pusta tablica" << endl;
			printBoard(*b);
			return 0;
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

		if (!strcmp(playerinput, "quit") || !strcmp(playerinput, "QUIT")) { exit(1); return -1; }
		else if (!strcmp(playerinput, "save") || !strcmp(playerinput, "SAVE")) { i1 = 5; saveGame(*p, *enemy, *b);readinput(rollresult, p, b, enemy, 0, 0); }
		else if (!strcmp(playerinput, "load") || !strcmp(playerinput, "LOAD")) { i1 = 5; loadGame(p, enemy, b, 0); readinput(rollresult, p, b, enemy, 0, 0); }
		else if (!strcmp(playerinput, "leaderboard") || !strcmp(playerinput, "LEADERBOARD")) { i1 = 5; loadLeaderboard(*b); readinput(rollresult, p, b, enemy, 0, 0); }
		else if (!strcmp(playerinput, "replay") || !strcmp(playerinput, "REPLAY")) {
			i1 = 5; (p->id == 1 ? replayMode(p, enemy, b, -1) : replayMode(enemy, p, b, -1));readinput(rollresult, p, b, enemy, 0, 0);
		}
		else if (!strcmp(playerinput, "move") || !strcmp(playerinput, "MOVE"))
		{
			if (!(a1 && a2)) { cin >> arg1 >> arg2; }

			//cout << playerinput << " - " << arg1 << " - " << arg2 << endl;
			int resultinput[2] = { arg1,arg2 };

			//kontrola ruchu

			if (!checkMandatoryMove(p, b, resultinput))
			{
				printBoard(*b);
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
				readinput(rr, p, b, enemy, 0, 0);
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
