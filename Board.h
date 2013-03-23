
#pragma once
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "math.h"
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>


using namespace std;
#include "Cell.h"
class Bot;
class Cell;
const int MAX = 50;
class CBoard
{
protected:
	int m_x;
	int m_y;
	Cell *m_Board[MAX][MAX];
	int  m_numtanks;

public:
	CBoard(int x);
	CBoard();
	~CBoard(void);
	void Clear();
	char getSpace(int x,int y);
	void reportPositions();
	string toString();
	int getmax();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	void Equals( CBoard &in);
	bool hit(int x, int y);
	bool place(int x, int y);
	void remove(int x,int y);
	int getCell(int x, int y);


};
