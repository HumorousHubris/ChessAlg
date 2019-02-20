/*Liam Ellinger, R11500458
Lab Section 501 */

#include "project2.h"

bool operator <(const struct mov& lhs, const struct mov& rhs)
{
	return tie(lhs.src, lhs.dst) < tie(rhs.src, rhs.dst);
}

//simple chess main func
set<struct mov> attacks(position p, color c)
{													
	set<struct mov> result;
	set <struct mov> toAdd;
	
	for (int i = 0; i<8;i++)//i is rank
	{
		for (int j = 0; j < 8; j++)//j is file
		{
			string piece = p[i][j];
			if (isOccupied(i,j,c, p)  && piece[0] == c)
			{
				char aPiece = piece[1];

				if (aPiece == 'K')//king
				{
					toAdd = kingAttacks(i, j, c, p);
					result = getUnion(result, toAdd);
				}
				
				if (aPiece == 'Q')//queen
				{
					toAdd = queenAttacks(i, j, c, p);
					result = getUnion(result, toAdd);
				}
				
				if (aPiece == 'r')//rook
				{
					toAdd = rookAttacks(i, j, c, p);
					result = getUnion(result, toAdd);
				}

				if (aPiece == 'b')//bishop
				{
					toAdd = bishopAttacks(i, j, c, p);
					result = getUnion(result, toAdd);
				}
				
				if (aPiece == 'k')//knight
				{
					toAdd = knightAttacks(i, j, c, p);
					result = getUnion(result, toAdd);
				}
				
				if (aPiece == 'p')//pawn
				{
					toAdd = pawnAttacks(i, j, c, p);
					result = getUnion(result, toAdd);
				}
			}
		}
	}
	return result;
}

set<struct mov> getUnion(set<struct mov> a, set<struct mov> b)
{
	set<struct mov> result;
	result.insert(a.begin(), a.end());
	result.insert(b.begin(), b.end());
	return result;
}

set<struct mov> queenAttacks(int r, int f, color c, position p)
{
	set <struct mov> result = rookAttacks(r, f, c, p);
	result = getUnion(result, bishopAttacks(r,f,c,p));
	return result;
}

set<struct mov> kingAttacks(int r, int f, color c, position p)
{
	set<struct mov> result;
	struct mov toAdd;
	for (int i = r-1;i<=r+1;i++)
	{
		for (int j = f - 1;j <= f + 1;j++)
		{
			if ((r != i || j != f) && !(i < 0 || j < 0) && !(i > 7 ||  j > 7) &&!isSameColorOccupied(i, j, c, p))
			{
				toAdd = makeMove(r, f, i, j);
				result.insert(moveFormat(toAdd));
			}
		}
	}
	return result;
}

set<struct mov> bishopAttacks(int r, int f, color c, position p)
{
	set<struct mov> result;
	struct mov toAdd;

	for (int i = -1; i < 2; i += 2)
	{
		for (int j = -1; j < 2; j += 2)
		{
			for (int k = 1; k < 8; k++)
			{
				int rOffset = k * i;
				int fOffset = k * j; 

				if (r + rOffset > 7 || f + fOffset > 7 || f + fOffset < 0 || r+rOffset < 0)//checks if we have reached an edge of the board
					break;
					
				if (!isSameColorOccupied(r + rOffset, f + fOffset, c, p))
				{
					toAdd = moveFormat(makeMove(r, f, r + rOffset, f + fOffset));
					result.insert(toAdd);
				}
				if (isOccupied(r + rOffset, f + fOffset, c, p)) // stops movement if there is a piece in the way (only breaks 3rd for loop)
					break;
			}
		}
	}
	return result;
}

set <struct mov> knightAttacks(int r, int f, color c, position p)
{
	set <struct mov> result;
	struct mov toAdd;

	for (int i = 1; i < 3; i++)
	{
		for (int j = 2; j > 0;j--)
		{
			for (int k = -1; k < 2; k+=2)
			{
				for (int h = -1; h < 2; h += 2)
				{
					int rOffset = r + i * k;
					int fOffset = f + j * h;

					if (rOffset >= 0 && fOffset >= 0 && rOffset < 8 && fOffset < 8 && (i*k + j * h) % 2 != 0&&!isSameColorOccupied(rOffset, fOffset, c, p))
					{
						toAdd = moveFormat(makeMove(r, f, rOffset, fOffset));
						result.insert(toAdd);
					}
				}
			}
		}
	}
	return result;
}

set<struct mov>rookAttacks(int r, int f, color c, position p)
{
	set<struct mov> result;
	struct mov toAdd;
	
	for (int i = -1; i < 2; i += 2)
	{
		for (int j = 0; j < 8; j++)
		{
			if (r + i * j < 8 && r + i*j >= 0 && r != r + i * j)
			{
				if (!isSameColorOccupied(r + i * j, f, c, p))//if space is occupied by the same color, dont add the space and stop adding on this row
				{
					result.insert(moveFormat(makeMove(r,f,r+i*j,f)));
					if ((r + i * j) + 1 >= 8 || isOccupied((r + i * j), f, c, p))//if the next space is occupied, stop moving
					{
						//cout << "rook stopped rowwise at(" << r + i*j << "," << f << ")\n";
						break;
					}
				}
				else break;
			}
		}
	}
	for (int i = -1; i < 2; i += 2)
	{
		for (int j = 0; j < 8; j++)
		{
			if (f + i * j < 8 && f + i * j >= 0 && f != f + i * j)
			{
				if (!isSameColorOccupied(r, f + i * j, c, p))
				{
					result.insert(moveFormat(makeMove(r, f, r, f + i * j)));
					if ((f + i * j) + 1 >= 8 || isOccupied(r, (f + i * j), c, p))
					{
						//cout << "rook stopped filewise at (" << r << "," << f + i * j << ")\n";
						break;
					}
				}
				else break;
			}
		}
	}

	return result;
}

set <struct mov> pawnAttacks(int r, int f, color c, position p)
{
	set<struct mov> result;
	if (c == 'W')
	{
		if (r == 1 && !isOccupied(r + 2,f,c,p))
		{
			result.insert(moveFormat(makeMove(r, f, r + 2, f))); //for pawn first move they can go 2 forward
		}
		if(r+1 < 8 && !isOccupied(r+1,f,c,p))
			result.insert(moveFormat(makeMove(r, f, r + 1, f)));

		if (!(r + 1 >= 8) && !(f + 1 >= 8)&&(p[r + 1][f + 1])[0] != c && (p[r + 1][f + 1])[0] != 'e')
			result.insert(moveFormat(makeMove(r, f, r + 1, f + 1)));
		if (!(r+1 >= 8) && !(f-1 < 0) &&(p[r + 1][f - 1])[0] != c && (p[r + 1][f - 1])[0] != 'e')
			result.insert(moveFormat(makeMove(r, f, r + 1, f - 1)));
	}

	if (c == 'B')
	{
		if (r == 6 && !isOccupied(r - 2, f, c, p))
		{
			result.insert(moveFormat(makeMove(r, f, r - 2, f)));
		}
		if (r-1 > 0 &&!isOccupied(r - 1, f, c, p))
			result.insert(moveFormat(makeMove(r, f, r - 1, f)));

		if (!(r - 1 < 0) && !(f + 1 >= 8)&&(p[r - 1][f + 1])[0] != c && (p[r - 1][f + 1])[0] != 'e')
			result.insert(moveFormat(makeMove(r, f, r - 1, f + 1)));
		if (!(r - 1 < 0) && !(f - 1 < 0)&&(p[r - 1][f - 1])[0] != c && (p[r - 1][f - 1])[0] != 'e')
			result.insert(moveFormat(makeMove(r, f, r - 1, f - 1)));
	}
	return result;
}

struct mov makeMove(int oldRank, int oldFile, int newRank, int newFile) //makes a move object out of the spaces given
{
	struct mov result;
	string src;
	string dst;

	stringstream srcStream;
	stringstream dstStream;

	srcStream << oldRank << oldFile;
	dstStream << newRank << newFile;

	src = srcStream.str();
	dst = dstStream.str();

	result.src = src;
	result.dst = dst;

	return result;
}

bool isSameColorOccupied(int rank, int file, color c, position p)
{
	string test = p[rank][file];
	if (test[0] == 'e')
		return false;
	else if (test[0] == c)
		return true;
	else if (test[0] != c)
		return false;
}

bool isOccupied(int rank, int file, color c, position p)
{
	string test = p[rank][file];
	if (test == "e")
		return false;
	return true;
}

struct mov moveFormat(struct mov m)
{
	struct mov res;
	res.src = m.src;
	res.dst = m.dst;

	res.src[1] = res.src[1] + 49;
	res.dst[1] = res.dst[1] + 49;

	res.src[0] += 1;
	res.dst[0] += 1;
	return res;
}

set<struct mov> canCastle(color c, position p) //untested
{
	set<struct mov> result;

	if (check(c, p)) //if in check, castling is impossible
		return result;

	if (c == 'W' && p[0][4] == "WK")
	{
		if (p[0][0] == "Wr" && p[0][1] == "e"&& p[0][2] == "e"&& p[0][3] == "e" && !check(c, doMove({"1e","1d"},p,c)) && !check(c, doMove({ "1e","1c" }, p, c))) //checks if pieces are in correct places and that the king is not moving through check
			result.insert(moveFormat(makeMove(0,4,0,2)));
		if (p[0][7] == "Wr"&& p[0][5] == "e"&& p[0][6] == "e" && !check(c, doMove({ "1e","1f" }, p, c)) && !check(c, doMove({ "1e","1g" }, p, c)))
			result.insert(moveFormat(makeMove(0,4,0,6)));
	}

	if (c == 'B' &&p[7][4] == "BK")
	{
		if (p[7][0] == "Br"&& p[7][1] == "e"&& p[7][2] == "e"&& p[7][3] == "e" && !check(c, doMove({ "8e","8d" }, p, c)) && !check(c, doMove({ "8e","8c" }, p, c)))
			result.insert(moveFormat(makeMove(7, 4, 7, 2)));
		if (p[7][7] == "Br"&& p[7][5] == "e"&& p[7][6] == "e" && !check(c, doMove({ "8e","8f" }, p, c)) && !check(c, doMove({ "8e","8g" }, p, c)))
			result.insert(moveFormat(makeMove(7, 4, 7, 6)));
	}

	return result;
}
bool check(color c, position p) 
{
	color otherColor;
	if (c == 'W')
		otherColor = 'B';
	else otherColor = 'W';

	set <struct mov> tests = attacks(p, otherColor); //remember only the enemy can kill the king
	string kingPos = "";
	string kingString ="";
	kingString.push_back(c);
	kingString.push_back('K');
	for (char i = 0; i < 8; i++)
	{
		for (char j = 0; j < 8; j++)
		{
			if (kingString.compare(p[i][j]) == 0)
			{
				char c = i + 49;
				kingPos.append(1, c);
				c = j + 97;
				kingPos.append(1, c);
			}
		}
	}

	for (auto f : tests)
	{
		if (f.dst == kingPos)
		{
			return true;	
		}
	}
	return false;
}

position doMove(struct mov m, position p, color c)
{
	position updatedPos = p;
	
	//move both pieces for castling remember
	if (m.src.compare("8e")==0 && m.dst.compare("8c") == 0 && p[7][4] == "BK")
	{
		updatedPos[7][0] = "e";
		updatedPos[7][3] = "Br";
	}

	if (m.src.compare("8e") == 0 && m.dst.compare("8g") == 0 && p[7][4] == "BK")
	{
		updatedPos[7][7] = "e";
		updatedPos[7][5] = "Br";
	}

	if (m.src.compare("1e") == 0 && m.dst.compare("1c") == 0 && p[0][4] == "WK")
	{
		updatedPos[0][0] = "e";
		updatedPos[0][3] = "Wr";
	}

	if (m.src.compare("1e") == 0 && m.dst.compare("1g") == 0 && p[0][4] == "WK")
	{
		updatedPos[0][7] = "e";
		updatedPos[0][5] = "Wr";
	}
	
	string piecetoMoveStr = "";
	piecetoMoveStr = p[m.src[0] - 49][m.src[1] - 97];
	
	updatedPos[m.src[0] - 49][m.src[1] - 97] = "e";
	updatedPos[m.dst[0] - 49][m.dst[1] - 97] = piecetoMoveStr;
	return updatedPos;
}

int gameOver(position p, color c) //returns 0 if game is not over, returns one if checkmate for given color, returns 2 for stalemate
{
	set<struct mov> attackList = attacks(p, c);
	for (auto f : attackList)
	{
		//cout << f.src << f.dst;
		position r = doMove(f, p, c);
		if (!check(c, r))
			return 0;
	}
	if (check(c, p))
		return 1;
	else return 2;
}
set<struct mov> legalMoves(position p, color c)
{
	set<struct mov> result;

	if (gameOver(p, c) != 0)
		return result;

	result = attacks(p,c);
	
	result = getUnion(result, canCastle(c, p));

	for (set<struct mov>::iterator it = result.begin(); it != result.end();) //remove all of the moves that would force the king into check.
	{
		position updatedPos = doMove(*it, p, c); //execute the move and do the test on new position generated
		
		if (check(c, updatedPos))
			it = result.erase(it);
		else it++; //prevents iterator from refrencing deleted element
	}

	return result;
}

string delSpace(string s)
{
	int sCount = s.length() - 1;
	string r = "";
	while (sCount >= 0)
	{
		if (s[sCount] == ' ')
			sCount--;
		else
		{
			r.insert(0, 1, s[sCount]);
			sCount--;
		}
	}
	return r;
}

//function definition:

position readPosition(string s) //remember we're outputting the POSITION vector
{
	//set up return variable, fill with all empty by default
	row allEmpty;
	allEmpty.assign(8, "e");
	position board;
	board.assign(8, allEmpty);

	//remove spaces from puzzle string
	string workingString = delSpace(s);

	//for loop running by 4 characters at a time. of the puzzle string. the program then ID's the piece, then looks up the space number and saves it there.
	for (int j = 0; j < (signed)(workingString.length() - 1); j += 4)
	{
		string piecePos = workingString.substr(j, 4); //grabs 4 chars from working string beginning at index j
													  //cout << piecePos << "!\n";
		string piece = piecePos.substr(0, 2);

		//subtract the ascii value of the first possible letter to make the first digit correspond to 0
		int rowLetter = piecePos[2] - 49;
		int columnLetter = piecePos[3] - 97;

		board[rowLetter][columnLetter] = piece;
	}
	return board;
}


bool checkMate(position p, color c)
{
	if (!check(c,p))
		return false;
	set<mov> moves = attacks(p,c);
	for (auto f : moves)
	{
		position r = doMove(f, p, c);
		if (!check(c, r))
			return false;
	}
	return true;
}