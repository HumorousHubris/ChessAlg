//Liam Ellinger, Lab 501, R11500458

#include "project2.h"

mov chooseMove(position s, int n)
{
	set<mov> moves = legalMoves(s, 'W');
	for (auto m : moves)
	{
		if (win(doMove(m,s,'W'), 'B', n-1))
			return m;
	}
}

bool win(position s, color c, int n)
{
	if (checkMate(s, 'B'))
		return true;
	if (n == 0)
		return false;

	set<mov> wMoves = legalMoves(s, 'W');
	set<mov> bMoves = legalMoves(s, 'B');

	if (c == 'W')
	{
		for (auto m : wMoves)
		{
			position t = doMove(m, s, 'W');
			showBoard(t);
			if (win(t,'B',n-1))
				return true;
			return false;
		}
	}
	for (auto m : bMoves)
	{
		position t = doMove(m, s, 'B');
		showBoard(t);
		if (!win(t, 'W', n))
			return false;
	}
	return true;
}

void showBoard(position p)
{
	cout << "\n";
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << p[i][j] << "\t";
		}
		cout << "\n";
	}
}