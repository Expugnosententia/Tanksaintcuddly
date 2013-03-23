
#include "Cell.h"



Cell::Cell()
{
	Clear();
}

Cell::~Cell(void)
{


}
string Cell::getState()
{

	return "this function is empty";

}

void Cell::Clear()
{
	cstate = 0;
}

void Cell::occupied()
{
	cstate = 1;
}

char Cell::ToChar()
{
	if(cstate != 1)
	{
		return '-';
	}
	if(cstate == 1)
	{
		return '^';
	}

}
void Cell::set(int x)
{
	if(x == 0 || x== 1)
	{
		cstate = x;
	}else
	{
		cout<<"OHMAHGAHDWHATHAVEYOUDONE"<<endl;
	}
}
int  Cell::get()
{
	return cstate;
}
Cell Cell::operator=( Cell& x)
{
	Cell result;
	result.set(x.get());
	return result;
}



