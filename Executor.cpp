#pragma once


#include <iostream>

#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include "math.h"

#define _CRTDBG_MAP_ALLOC                        //Memory Leak Logic
#include <stdlib.h>								 //Memory Leak Logic
#include <crtdbg.h>                              //Memory Leak Logic
using namespace std;
#include "Board.h"
#include "Bot.h"
#include "ConfigFile.h"

void filereadstate(string filename, double& xfac,int& botnum,long& fitcap, int& rounds);
void FitSort(Bot* input[], int numbot);
void ClearScreen();
void refreshBoard();
int Executor(void)
{
	{
		srand ( time(NULL) );
		double xfactor; //mutation rate
		ofstream fitnessfile;
		int iteration = 0;
		fitnessfile.open ("FoT.csv", ios::out | ios::app);
		int m_bot = 25; 
		bool flag;
		long fitnesscap;
		int rounds;
		string filen;
		string simrun;
		int roundcount =0;
		CBoard Biome(50);
		Bot *specimens[25];
		cout<<"Please Enter Filename for board configuration"<<'\n';
		cin>>filen;
		filereadstate( filen,  xfactor, m_bot, fitnesscap, rounds);
		
		//cout<<Biome.toString();

		for(int x = 0; x < m_bot; x++)
		{

			int h = rand()% 49;  //roll for horizontal position
			int v = rand() % 49; // roll for vertical position

			if(x == 0) //if first bot in the sequence add bot to board
			{

				specimens[x] = new Bot(h,v, Biome);
				Biome.place(h,v);	
				ClearScreen();
			//	cout<<Biome.toString();

			}else  //if not first bot check for overlapping positions. If there are no overlaps then place bot
			{



				if(Biome.place(h,v) == true)
				{
					specimens[x] = new Bot(h,v, Biome);
					ClearScreen();
				//	cout<<Biome.toString();

				}



			}
		}
			cout<<"Would you like to run the Simulation(y/n)? (simulation will always run once)"<<endl;
				cin>>simrun;
		do
		{
			
		do
		{

			for(int x =0;x<m_bot;x++)
			{
				int n = 0;
				int prY = 0;
				int	prX = 0;

				specimens[x]->refresh(Biome);
				ClearScreen();
			//	cout<<Biome.toString();

				specimens[x]->Look();
				cout<<specimens[x]->ToString();
				n=(specimens[x]->decide());
				cout<< n;
				specimens[x]->Position(prX,prY);

				if(n <= 5)
				{

					if(specimens[x]->move(n) == true)
					{
						int q;
						int r;
						specimens[x]->Position(q,r);
						Biome.remove(prX,prY);
						Biome.place(q,r);

					}
				}else if(n >5 && n < 11)
				{
					specimens[x]->turretmove(n);
				}else if(n == 11)
				{
					bool flag;
					int b;
					int s;

					if( specimens[x]->fire(b,s) == true && flag !=true)
					{
						for(int l = 0; l < m_bot;l++)
						{
							if(specimens[l]->positionTest(b,s) == true)
							{
								specimens[l]->IsHit();
								specimens[x]->hit();
								flag = false;
							}
						}
					}

				}


				ClearScreen();
			//	cout<<Biome.toString();
				cout<<specimens[x]->ToString();

			}
			long maxfit = 0;
			for(int r = 0; r<m_bot;r++)
			{

				if(maxfit < specimens[r]->getFitness())
				{
					maxfit = specimens[r]->getFitness();
				}
				
			}
			if(roundcount == 0 && iteration == 0)
				{
					fitnessfile<<"iteration,"<<"Round,"<<"Fitness"<<endl;
				}
			fitnessfile<<iteration<<","<<roundcount<<","<<maxfit<<endl;


			roundcount++;
			cout<<roundcount;
		}while(roundcount < rounds);
		
		iteration++;
		int prevY =0;
		int prevX =0;
		Bot newbot(Biome);
		Bot newbot1(Biome);
		newbot.refresh(Biome);
	FitSort(specimens, m_bot);
		specimens[m_bot-2]->Position(prevY, prevX);
		newbot.Breed(specimens[0],specimens[1],xfactor);
		specimens[m_bot-2]->setEqualto(newbot);
		specimens[m_bot-2]->setPosition(prevY, prevX);
		for(int qq = 0;qq<m_bot;qq++)
		{
			specimens[qq]->refresh(Biome);
		}
		specimens[m_bot-1]->Position(prevY, prevX);

		newbot1.Breed(specimens[3],specimens[2],xfactor);
		newbot1.refresh(Biome);
		specimens[m_bot-1]->setEqualto(newbot1);
		specimens[m_bot-1]->setPosition(prevY, prevX);

		}while(simrun == "y");
			for(int i = 0; i<m_bot;i++)
			{
				delete specimens[i];
			}
	}
	_CrtDumpMemoryLeaks(); //check for memory leaks
	cout << endl;

	system("pause");
	return 0;
};


void filereadstate(string filename, double& xfac,int& botnum,long& fitcap,int& rounds)
{
	ConfigFile config( filename );

	// Values can be read from the file by name
	config.readInto( botnum, "Robots" );
	config.readInto(xfac, "xfactor" );
	config.readInto( fitcap, "fitnesscap" );
	config.readInto(rounds, "roundlength");

}


void ClearScreen() //taken from a beginner thread on cplusplus.com
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition( hStdOut, homeCoords );
}

void FitSort(Bot* input[], int numbot)
{
	Bot *out;
	for(int x=0; x<numbot; x++)

	{


		for(int y=0; y<numbot-1; y++)

		{

			if( input[y]->getFitness() < input[y+1]->getFitness())
			{

				out = input[y+1];

				input[y+1] = input[y];

				input[y] = out;

			}

		}

	}

}

void refreshBoard(CBoard in, Bot *bots[], int numbots)
{
	in.Clear();
	int f;
	int g;
	for(int x = 0; x < numbots; x++ )
	{
		bots[x]->Position(f,g);
		in.place(f,g);

	}
}