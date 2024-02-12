#pragma warning(push)
#pragma warning(disable:6385)
#include <iostream>
#include<cstdlib>
#include<ctime>
#include "functions.h"

using namespace std;



int main()
{
    srand((unsigned)time(NULL)); //ustawianie seed dla wartosci z kostki

	board b;

	player p1, p2;
	p1.id = 1;
	p2.id = 2;

	//cloneHistory();
	
	
	printBoard(b);


	whoStarts(&p1, &b, &p2);

	while (b.outside[0] < MAXOUTSIDE && b.outside[1] < MAXOUTSIDE) //magiczna petla
	{

		int* p = roll(&p2);
		int rollresult[2] = { *(p + 0),*(p + 1) };
		

		


		if (readinput(rollresult, &p2, &b, &p1, 0, 0) == -1) { return 0; }
		b.round++;
		
		
		
		printBoard(b);

		//cout << "---------------------------------------------------" << endl;

		p = roll(&p1);
		rollresult[0] = *(p + 0);
		rollresult[1] = *(p + 1);
		
		

		if (readinput(rollresult, &p1, &b, &p2, 0, 0) == -1) { return 0; }
		b.round++;

		
		printBoard(b);
		//cout << "---------------------------------------------------" << endl;


	}	

	return 0;
}