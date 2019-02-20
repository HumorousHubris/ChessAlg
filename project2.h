//Name= Liam Ellinger, R11500458
//Lab501

#ifndef  PROJECT1
#define PROJECT1

#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <sstream>
#include <tuple>

using namespace std;
typedef vector<string> row;
typedef vector<row> position;
typedef char color;
typedef string square;

struct mov {
	string src;
	string dst;


};
typedef struct mov move;


position readPosition(string s);
string delSpace(string s); 
bool isOccupied(int rank, int file, color c, position p);
bool isSameColorOccupied(int rank, int file, color c, position p);

struct mov makeMove(int oldRank, int oldFile, int newRank, int newFile);

set<struct mov> attacks(position p, color c);

set<struct mov> legalMoves(position p, color c);

//piece attack funcs
set<struct mov> kingAttacks(int rank, int file, color c, position p);
set<struct mov> queenAttacks(int rank, int file, color c, position p);
set<struct mov> bishopAttacks(int rank, int file, color c, position p);
set<struct mov> knightAttacks(int rank, int file, color c, position p);
set<struct mov> rookAttacks(int rank, int file, color c, position p);
set<struct mov> pawnAttacks(int rank, int file, color c, position p);

set<struct mov> canCastle(color c, position p);
struct mov moveFormat(struct mov m); 

set<struct mov> getUnion(set<struct mov> a, set<struct mov> b);
bool operator <(const struct mov& lhs, const struct mov& rhs);

int gameOver(position p, color c);//returns 0 if not game over, 1 if checkmate for given color and 2 for stalemate

bool check(color c, position p);
position doMove(struct mov m, position p, color c);

bool checkMate(position p, color c);
//project 3 functions
bool win(position p, color c, int n);
struct mov chooseMove(position s, int n);
void showBoard(position p);
#endif
#pragma once
