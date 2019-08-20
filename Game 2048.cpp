#include<iostream>
#include<ctime>
#include<iomanip>
#include<cstdlib>
using namespace std;
int board[4][4];
int dirline[]={1,0,-1,0};
int dircolumn[]={0,1,0,-1};
pair<int, int> generateunoccupiedpos()
{
	int occupied=1, line, column;
	while(occupied)
	{
		line=rand()%4;
		column=rand()%4;
		if(board[line][column]==0)
		occupied=0;
	}
	return make_pair(line,column);
}
void addpiece()
{
	pair<int, int> pos=generateunoccupiedpos();
	board[pos.first][pos.second]=2;
}
void newgame()
{
	for(int i=0;i<4;i++)
	for(int j=0;j<4;j++)
	board[i][j]=0;
//	pair<int, int> pos=generateunoccupiedpos();
//	board[pos.first][pos.second]=2;
addpiece();
}
void printui()
{	
    system("cls");
	for(int i=0;i<4;i++)
	{
	for(int j=0;j<4;j++)
	
		if(board[i][j]==0)
		cout<< setw(4) <<".";
		else cout<< setw(4) <<board[i][j];
		cout<<"\n";
    }
	cout<<"n: newgame, w: up, s: down, d: right, a:left, q: quit\n";
	
}
bool candomove(int line, int column, int nextline, int nextcolumn)
{
	if(nextline<0 || nextcolumn<0 || nextline>=4 || nextcolumn>=4 || (board[line][column]!=board[nextline][nextcolumn] && board[nextline][nextcolumn]!=0))
	return false;
	return true;
}
void applymove(int dir)
{
	int startline=0, startcolumn=0, linestep=1, colstep=1;
	if(dir==0)
	{
		startline=3;
		linestep=-1;
	}
	if(dir==1)
	{
		startcolumn=3;
		colstep=-1;
	}
	int movepossible, canaddpiece=0;
	do{
		movepossible=0;
	for(int i=startline;i>=0 && i<4; i=i+linestep)
		for(int j=startcolumn;j>=0 && j<4;j+=colstep)
		{
			int nexti=i+dirline[dir], nextj= j+dircolumn[dir];
			if(board[i][j] && candomove(i, j, nexti, nextj))
			{
				board[nexti][nextj]+=board[i][j];
				board[i][j]=0;
				movepossible=canaddpiece=1;
			}
			
		}
		printui();
	}while(movepossible);
	
	if(canaddpiece)
	addpiece();
}
int main()
{
	srand(time(0));
	char commandtodir[128];
	commandtodir['s']=0;
	commandtodir['d']=1;
	commandtodir['w']=2;
	commandtodir['a']=3;
	newgame();
	while(true)
	{
		printui();
		char command;
		cin>>command;
		if(command=='n')
		newgame();
		else if(command=='q')
		break;
		else
		{
			int currentdir=commandtodir[command];
			applymove(currentdir);
		}		
	}
	return 0;
}
