
#include "Bot.h"




Bot::Bot(int x, int y, CBoard& j)
{
	p_x = x;
	p_y = y;
	fitness = 0;
	states = 11;

	current.Equals(j);
	ammo = 10;
	turret = 0;
	boardmax = current.getmax();
	//srand(time(NULL));
	genName();
	genGenome();
}
Bot::Bot( CBoard& j)
{
	p_x=0;
	p_y=0;
	fitness = 0;
	states = 11;

	current.Equals(j);
	ammo = 10;
	turret = 0;
	boardmax = current.getmax();
	//srand(time(NULL));
	genName();
	genGenome();
}
Bot::Bot()
{
	p_x=0;
	p_y=0;
	fitness = 0;
	states = 11;
	ammo = 10;
	turret = 0;


}
Bot::~Bot(void)
{

}
Bot::Bot( Bot &cp)
{
		ammo = cp.ammo;
	setGenome(cp.genome);
	name = cp.name;
	
	p_x = cp.p_x;
	p_y = cp.p_y;
	fitness = cp.fitness;
	current.Equals(cp.current);

}

void Bot::Position(int& x, int& y)
{
	x = p_x;
	y = p_y;

}
void Bot::setPosition(int x, int y)
{
	p_x = x;
	p_y = y;

}
void Bot::genGenome()
{
	for(int a= 0; a < full; a++)
	{
		genome[a] = rand() % 11;
	}
}

void Bot::Look()
{
	bool flag = false;

	if(current.getSpace((p_x-1),(p_y)) == '^')//checking north
	{
		memory[0] = 1;
	}else
	{
		memory[0]=0;
	}
	if(current.getSpace((p_x+1),(p_y)) == '^')//checking south
	{
		memory[1]=1;
	}else
	{
		memory[1]=0;
	}
	if(current.getSpace((p_x),(p_y+1)) == '^')//checking east
	{
		memory[2] = 1;
	}else
	{
		memory[2]=0;
	}
	if(current.getSpace((p_x),(p_y-1)) == '^') //checking west
	{
		memory[3] = 1;
	}else
	{
		memory[3]=0;
	}
	if(turret == 0)
	{
		if(p_x- 1 > 0)
		{
			for(int j =p_x-1;j >= 0;j--) //
			{
				if(current.getSpace((j),(p_y)) == '^')
				{
					memory[4]=1;
					flag = true;

				}
				else if( flag == false )
				{
					memory[4]=0;
				}

			}

		}else
		{
			memory[4]= 0;
		}
	}

	if(turret == 2)
	{
		if(p_x+1 != current.getmax())
		{
			for(int j =p_x+1; j<current.getmax();j++)  //turret path south
			{
				if(current.getSpace((j),(p_y)) =='^')
				{
					memory[4]=1;
					flag = true;

				}
				else if( flag == false )
				{
					memory[4]=0;
				}
			}
		}else
		{
			memory[4]=0;
		}

	}
	if(turret == 1)
	{
		if(p_y+1 != current.getmax())
		{
			for(int j =p_y+1; j< (current.getmax() );j++) //turret path east
			{
				if(current.getSpace((p_x),(j)) == '^')
				{
					memory[4]=1;
					flag = true;

				}
				else if( flag == false )
				{
					memory[4]=0;
				}

			}
		}else
		{
			memory[4]=0;
		}

	}
	if(turret == 3)
	{
		if(p_y- 1 > 0)
		{
			for(int j =p_y-1; j >= 0;j--) //turret path west
			{
				if(current.getSpace((p_x),(j)) == '^')
				{
					memory[4]=1;
					flag = true;

				}
				else if( flag == false )
				{
					memory[4]=0;
				}
			}
		}else
		{
			memory[4]=0;
		}

	}



}
bool Bot::fire(int& g, int& h)
{


	if(ammo != 0)
	{
		ammo--;
		if(turret == 0)
		{
			if(p_x- 1 > 0)
			{
				for(int j =p_x-1;j >= 0;j--) //
				{
					if(current.getSpace((j),(p_y)) == '^')
					{
						g = j;
						h = p_y;
						return true;

					}


				}

			}else
			{
				return false;
			}
		}

		if(turret == 2)
		{
			if(p_x+1 != current.getmax())
			{
				for(int j =p_x+1; j<current.getmax();j++)  //turret path south
				{
					if(current.getSpace((j),(p_y)) =='^')
					{
						g = j;
						h = p_y;
						return true;


					}

				}
			}else
			{
				return false;
			}

		}
		if(turret == 1)
		{
			if(p_y+1 != current.getmax())
			{
				for(int j =p_y+1; j< (current.getmax() );j++) //turret path east
				{
					if(current.getSpace((p_x),(j)) == '^')
					{
						g = p_x;
						h = j;
						return true;

					}


				}
			}else
			{
				return false;
			}

		}
		if(turret == 3)
		{
			if(p_y- 1 > 0)
			{
				for(int j =p_y-1; j >= 0;j--) //turret path west
				{
					if(current.getSpace((p_x),(j)) == '^')
					{
						g = p_x;
						h = j;
						return true;

					}

				}
			}else
			{
				return false;
			}

		}

	}else
	{
		fitness -= 2;
		return false;
	}

}
void Bot::hit()
{
	fitness += 3;
}
void Bot::IsHit()
{
	fitness -= 3;
}
bool Bot::move(int t)
{
	if(t == 0)
	{
		if(memory[0] == 0)
		{
			if(p_x != 0)
			{
				p_x--;

			}
			else if(p_x == 0)
			{
				p_x = boardmax-1;
			}

			return true;
		}else
		{
			fitness -= 3;
			return false;
		}
	}
	if(t == 1)
	{
		if(memory[1] == 0)
		{
			if(p_x != boardmax-1 )
			{
				p_x++;
			}
			else if(p_x == boardmax-1)
			{
				p_x = 0;
			}

			return true;
		}else
		{
			fitness -= 3;
			return false;
		}
	}
	if(t == 2)
	{
		if(memory[2] == 0)
		{
			if(p_y != boardmax-1 )
			{
				p_y++;
			}
			else if(p_y == boardmax-1)
			{
				p_y = 0;
			}
			return true;

		}else
		{
			fitness -= 3;
			return false;
		}
	}
	if(t == 3)
	{
		if(memory[3] == 0)
		{
			if(p_y != 0 )
			{
				p_y--;
			}
			else if(p_y == 0)
			{
				p_y = boardmax-1;
			}

			return true;
		}else
		{
			fitness -= 3;
			return false;
		}
	}

	if(t == 4)
	{
		move(rand()%4);
	}
	if(t== 5 )
	{

	}
}
void Bot::turretmove(int j)
{
	if(j == 6)
	{
		turret = 0;
	}
	if(j == 7)
	{
		turret = 1;
	}
	if(j == 8)
	{
		turret = 2;
	}
	if(j == 9)
	{
		turret = 3;
	}
	if(j == 10)
	{
		turret = (rand()%3);
	}
}
int Bot::decide()
{
	string comp = "00000";
	bool test = true;
	int count;
	int save = 0;
	for(int c = 0; c<5;c++)
	{
		comp[c]=(memory[c] + 48);
	}

	for(int f = 0; f< full;f++)
	{


		if(comp.compare(decision[f]) == 0)
		{
			save = genome[f];
		}
	}


	/*if(save> 5)
	{
	move(save);
	}else if(save >5 && save < 11)
	{
	turretmove(save);
	}else if(save == 11)
	{
	}*/
	return save;

}

void Bot::genName()
{
	static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	int length = 10;

	name.resize(length);

	for (int i = 0; i < length; i++)
	{
		int l = rand() % (sizeof(charset));
		name[i] = charset[l];
	}

}


void Bot::Breed(Bot *xx,Bot *xy, double xfactor)
{
	int split = (rand() % 19 + 13);
	int first[full];
	int second[full];
	int Baby[full];
	Bot Offspring(xx->current);
	xx->copyGenome(first);
	
	xy->copyGenome(second);
	for(int o=0;o<split;o++)
	{
		Baby[o]=first[o];
	}
	for(int n=split; n<full;n++)
	{
		Baby[n]=second[n];
	}

	Offspring.setGenome(Baby);
	Offspring.Mutation(xfactor);
	setEqualto(Offspring);
    }

void Bot::setGenome(int gen[])
{
	for(int v=0;v<full;v++)
	{
		genome[v]=gen[v];
	}	


}

void Bot::copyGenome(int cpy[])
{
	for(int v=0;v<full;v++)
	{
		cpy[v]=genome[v];
	}	

}
void Bot::Mutation(double xfactor)// xfactor is the mutation rate variable and it must be <=1 or else everything will mutate at an extreme rate [this is the equivalent effect of
{                                 //introducing radiation into the biosphere]
	double Roll = ((rand() % 100 )/100);

	for(int z = 0; z<full; z++)
	{
		double Roll = ((rand() % 100 )/100);

		if(Roll < xfactor)
		{
			genome[z] = (rand()% 11 );
		}
	}

}

Bot Bot::operator=( Bot &in)
{
	Bot Result;
	Result.ammo = in.ammo;
	Result.setGenome(in.genome);
	Result.name = in.name;
	Result.fitness = in.fitness;
	Result.p_x = in.p_x;
	Result.p_y = in.p_y;
	Result.fitness = in.fitness;
	Result.current = in.current;
	return Result;

}
void Bot::setEqualto(Bot& in)
{
	ammo = in.ammo;
	setGenome(in.genome);
	name = in.name;
	
	p_x = in.p_x;
	p_y = in.p_y;
	fitness = in.fitness;
	//current.Equals(in.current);
}
void Bot::refresh(CBoard& j)
{
	current.Equals(j);
}
bool Bot::positionTest(int x, int y)
{
	if(x == p_x && y == p_y)
	{
		return true;
	}else
	{
		return false;
	}
}
long Bot::getFitness()
{
	return fitness;
}
void Bot::setFitness(int f)
{
	fitness = f;
}

string Bot::ToString()
{
	string positions[4]= {"North","South","East","West"};
	stringstream out;
	out<<"* * * * * * * * * * * * *"<<endl;
	out<<" Name: "<< name<<"       "<<endl;
	out<<"Position "<< p_x<< " , "<<p_y<<"       "<<endl;
	out<<" Fitness: "<< fitness<<"       "<<endl;
	out<<" Ammo Remaining:  "<< ammo<<"       "<<endl;
	out<<" Observation: ";
	for(int i = 0; i< 5;i++)
	{
		out<< " "<< memory[i];
	}
	out<<endl;
	out<<" Turret Facing:  "<< positions[turret]<<endl;
	out<<"* * * * * * * * * * * * *"<<endl;

	return out.str();


}

bool Bot::islessThan( Bot &a, Bot &b)
{
	return a.getFitness() < b.getFitness();
}

bool Bot::cmp(const Bot *a, const Bot *b)
{
	return false;
}

