//Liam Ellinger, Lab 501, R11500458
#include "project2.h"
//WK7eWb1aWk6hBK8hBp7gBp7h is spec'd puzzle string
/*Tested with these puzzle strings:
Br1hBK5eWr6fWp6hWK7f
BK1cBr2gBp3bWK3eWr7d
WK5aWk5bBK5dBQ4c
Wp3cBp4cWr4dWK5fBK8c
*/


/*int main()
{
	position p = readPosition("WK1eWr3cBp4cBp7bBp7eBp6eBp7fBp6fBp7gBp6gBp7hBp6hBK8hBp3b");
	set<struct mov> moves = legalMoves(p, 'W');
	showBoard(p);

	if (isOccupied(6, 3, 'J', p))
		cout << "7e is occupied";
	for (auto f : moves)
		cout << "(" << f.src << "," << f.dst << ")\n";
	system("pause");
}*/
//mate in 1 :Br8aBK8hBp7hWb5dBp3aWK3gWb2f works

/*int main()
{
	position test = readPosition("WK1h   Bk3f  Wp4h  BK5h  Wb6e  WQ6f  Br8h");

	struct mov result = chooseMove(test, 2);
	cout << "(" << result.src << "," << result.dst << ")\n";
	system("pause");
	return 0;
}
*/
int main()
{
	position p = readPosition("WK1h   Bk3f  Wp4h  BK5h  Wb6e  WQ6f  Br8h");
	set<struct mov> moves = legalMoves(p, 'W');
	for (auto f : moves)
	{
		cout << f.src << " , " << f.dst << "\n";
	}
	if (gameOver(p, 'B'))
		cout << "blacks in checkmate\n";
	struct mov m = chooseMove(p, 3);
	cout << "move is: " << m.src << "," << m.dst << "\n";
	//mov m = { "1h", "2b" };
	//position test = doMove(m, p, 'W');
	showBoard(p);
	system("pause");
	return 0;
}
/*
//Name= Elham Hojati
//Lab501 or Lab503


//_________________________________________________________________________
//function for printing a position
void printmove(mov mv) {

	string s = mv.src;
	string d = mv.dst;

	cout << "mov = (" << s << "," << d << ") " << "  " << endl;

}

//_________________________________________________________________________

//_________________________________________________________________________
//function for comparing two moves
bool compare_moves(mov mv1, mov mv2) {
	bool result;
	string s1, d1, s2, d2;

	s1 = mv1.src;
	d1 = mv1.dst;
	s2 = mv2.src;
	d2 = mv2.dst;
	//cout << s1 << s2 << d1 << d2 << endl;
	if (s1 == s2 && d1 == d2)
		result = true;
	else
		result = false;
	return result;
}
//_________________________________________________________________________

//_________________________________________________________________________
//function for returning the correct answer for the testcase
mov answer_chooseMove(string s)
{
	mov m;
	if (s == "  WK1h   Bk3f  Wp4h  BK5h  Wb6e  WQ6f  Br8h   ")
	{


		m.src = "6f";
		m.dst = "7g";

	}

	return m;
}
//_________________________________________________________________________

//_________________________________________________________________________
//main function 
int main()

{
	int passed = 0;

	vector<string> testcases;
	testcases.push_back("  WK1h   Bk3f  Wp4h  BK5h  Wb6e  WQ6f  Br8h   ");  //general testcase

	mov mv1, mv2;

	for (int i = 0; i < (signed)testcases.size(); ++i) {
		if (i == 0) {
			mv1 = chooseMove(readPosition(testcases[i]), 2);
			mv2 = answer_chooseMove(testcases[i]);
		}



		cout << "The result of the chooseMove funcion:  ";
		printmove(mv1);
		cout << "The correct move:   ";
		printmove(mv2);


		if (compare_moves(mv1, mv2)) {
			passed = passed + 1;
			cout << "test case " << i + 1 << " has been passed." << endl;
		}
		else {
			cout << "test case " << i + 1 << " has been  failed.!!!!!!!" << endl;
		}
		cout << "_________________________" << endl;
	}

	cout << "number of passed cases:" << passed << endl;

	system("pause");
	return 0;

}

//_______________________________________________________________________

*/
