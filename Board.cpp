
#include "Board.h"


CBoard::CBoard(int x)
{
	m_x = x;
	m_y = x;
	m_numtanks = 0;
	Clear();
}
CBoard::CBoard()
{
	m_x = 0;
	m_y = 0;
	m_numtanks = 0;
	Clear();
}

CBoard::~CBoard(void)
{
	for(int x = 0; x< MAX;x++)
	{
		for(int y = 0; y< MAX;y++)
		{
			delete m_Board[x][y];
		}
	}
}
void CBoard::Clear()
{
	for(int i = 0;i < m_x; i++)
	{
		for( int j = 0;j < m_y;j++)
		{
			m_Board[i][j] = new Cell();
		}
	}
}
void CBoard::reportPositions()
{
	int v = 0;
	int h = 0;
	for(int x = 0; x < m_numtanks; x++)
	{

		m_Board[h][v]->occupied();
	}
}
char CBoard::getSpace(int x,int y)
{

	if(x < 0  )
	{
		return m_Board[m_x-1][y]->ToChar();
	}else if(x > (m_x - 1))
	{
		return m_Board[0][y]->ToChar();
	}else if(y > (m_y-1))
	{
		return m_Board[x][0]->ToChar();
	}else if(y < 0)
	{
		return m_Board[x][m_y-1]->ToChar();
	}else
	{
		return m_Board[x][y]->ToChar();
	}



}

string CBoard::toString()
{
	stringstream out;
	for(int x = 0; x<m_x;x++)
	{

		for (int y = 0; y<m_y;y++)
		{
			if(x==0 && y == 0)
			{
				for (int l = 0; l<m_y;l++)
				{
					if (l == 0)
					{
						out<<"   "<<l<<"  ";
					}else
					{
						if(l<10)
						{
							out<<l<<"   ";
						}else
						{ 
							out<<l<<"  ";
						}
					}

				}
				out<<endl;
			}
			if(x <10 && y== 0)
			{
				out<<x<<"  "<<m_Board[x][y]->ToChar()<<"   ";
			}
			else if(y== 0)
			{
				out<<x<<" "<<m_Board[x][y]->ToChar()<<"   ";;
			} else 
			{
				out<<m_Board[x][y]->ToChar()<<"   ";;
			}
		}
		out<<endl;
	}
	return out.str();

}

int CBoard::getmax()
{
	return MAX;
}
int CBoard::getX()
{
	return m_x;
}
int CBoard::getY()
{
	return m_y;
}
void CBoard::setX(int x)
{
	m_x = x;
}
void CBoard::setY(int y)
{
	m_y = y;
}


void CBoard::Equals( CBoard &in)
{
	int f = in.getX();
	int g = in.getY();
	setX(f);
	setY(f);

	for(int i = 0;i < f; i++)
	{
		for( int j = 0;j < g;j++)
		{
			m_Board[i][j]=in.m_Board[i][j];
		}
	}




}


bool CBoard::hit(int x, int y)
{

	if(m_Board[x][y]->ToChar() == '^')
	{
		return true;
	} else
	{
		return false;
	}

}

void CBoard::remove(int x,int y)
{
	m_Board[x][y]->Clear();

}

bool CBoard::place(int x, int y)
{
	if(m_Board[x][y]->ToChar() != '^')
	{
		m_Board[x][y]->occupied();
		return true;
	}else
	{
		return false;
	}

}
int CBoard::getCell(int x, int y)
{
	return m_Board[x][y]->get();
}