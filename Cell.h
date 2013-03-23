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
using namespace std;

class Cell
{
	int cstate; 

public:
	Cell();
~Cell(void);
string getState();

void Clear();
char ToChar();
void occupied();
void set(int x);
int  get();

Cell operator=( Cell& x);

};
