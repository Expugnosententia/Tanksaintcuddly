#pragma once

#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "math.h"
#include "Board.h"
using namespace std;
class CBoard;
class Cell;
const int full = 32;
const string decision[33] = {"00000","00001","00010","00011","00100","00101","00110","00111","01000","01001","01010","01011","01100","01101","01110","01111","10000","10001","10010","10011","10100","10101","10110","10111","11000","11001","","11010","11011","11100","11101","11110","11111"}; 
class Bot
{
	CBoard current;
	int genome[full];
	int memory[5];
	long fitness;
	int p_x;
	int p_y;
	int states;
	int ammo;
	int turret;
	int boardmax;
	string name;



public:
	Bot(int x, int y, CBoard &j);
	Bot();
	Bot( CBoard& j);
	 Bot( Bot &cp);
	~Bot(void);
	void Position(int& x, int& y);
	void setPosition(int x, int y);
	void genGenome();
	void Look();
	int decide();
	bool move(int t);
	void turretmove(int j);
	bool fire(int& g,int& h);
	void hit();
	void IsHit();
	void genName();
	int searchGenome(int x);
	void setGenome(int gen[]);
	void Breed(Bot *xx,Bot *xy, double xfactor);
	void copyGenome(int cpy[]);
	void Mutation(double xfactor);
	Bot operator=( Bot &in);
	void setEqualto(Bot& in);
	bool islessThan(  Bot &a,  Bot &b);
	void refresh(CBoard &j);
	bool positionTest(int x, int y);
	long getFitness();
	void setFitness(int f);
	string ToString();
	bool cmp(const Bot *a, const Bot *b);

};