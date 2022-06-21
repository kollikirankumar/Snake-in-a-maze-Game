#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool Game;
int width = 90;      //width of the board
int height = 30;     //height of the board
int x, y, X, Y, score; //(x,y) are coordinates of the head of snake, (X,Y) are coordinates of fruit in game
int bodyX[100], bodyY[100];   // array to store the coordinates of the body of snake
int nTail;
enum eDirecton {STOP = 0, LEFT, RIGHT, UP, DOWN, PAUSE};
eDirecton dir;

bool find(int val,int a[],int n)
{
	for(int i=0;i<n;i++)
	{
		if(a[i]==i)
	       return true;
	}
	return false;
}

void Setup()
{
	Game = false;
	dir = STOP;
	x = 0;
	y = 0;
	X = 20;
	Y = 0;
	score = 0;
}
void Draw()
{
	int t;
	if(score<=50)
	t = 3;
	else if(score<=100)
	t = 2;
	else
	t = 1;
	while(t--)
	{
		system("cls"); 
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
    
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == Y && j == X)
				cout << "@";
			else if((i==6||i==7||i==24||i==25)&& (j>10 && j<80))                
			cout<<"*";
			else if((j==11||j==12||j==13||j==79||j==78||j==77) && (i>=10 && i<=21))  
			cout<<"*";   
			else if((i>=8 && i<=23) && (j==44||j==45||j==46||j==47))
			cout<<"*";	
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (bodyX[k] == j && bodyY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
				

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
	}
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'p':
		    dir = PAUSE;
			break;	
		case 'x':
			Game = true;
			break;
		}
	}
}

bool calc(int X,int Y)
{
	int i = Y,j = X;
	if((i==6||i==7||i==24||i==25)&& (j>10 && j<80))               
	    return false;
	else if((j==11||j==12||j==13||j==79||j==78||j==77) && (i>=10 && i<=21))  
	    return false;   
    else if((i>=8 && i<=23) && (j==44||j==45||j==46||j==47))
		return false;		
	else
	    return true;
}

void Logic()
{
	int prevX = bodyX[0];
	int prevY = bodyY[0];
	int prev2X, prev2Y;
	bodyX[0] = x;
	bodyY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = bodyX[i];
		prev2Y = bodyY[i];
		bodyX[i] = prevX;
		bodyY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case PAUSE:
	    break;	
	default:
		break;
	}
	
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (bodyX[i] == x && bodyY[i] == y)
			{
				Game = true;
				cout<<"OOPS! SNAKE HIT IT'S OWN BODY"<<endl;
			}
   
    int i = y,j = x;		
    if((i==6||i==7||i==24||i==25)&& (j>10 && j<80))                
	    {
	    	Game = true;
	    	cout<<"OOPS! SNAKE HIT THE MAZE"<<endl;
		}
	else if((j==11||j==12||j==13||j==79||j==78||j==77) && (i>=10 && i<=21))  
	    {
	    	Game = true;
	    	cout<<"OOPS! SNAKE HIT THE MAZE"<<endl;
		}  
    else if((i>=8 && i<=23) && (j==44||j==45||j==46||j==47))
		{
	    	Game = true;
	    	cout<<"OOPS! SNAKE HIT THE MAZE"<<endl;
		}
		
	if (x == X && y == Y)
	{
		score += 10;
		X = rand() % width;
		Y = rand() % height;
		while(calc(X,Y)==false)
		{
			X = rand() % width;
		    Y = rand() % height;
		}
		nTail++;
	}
}
void Instructions()
{
	cout<<"HII, WELCOME TO SNAKE IN A MAZE GAME:"<<endl;
	cout<<"Please go through the instructions carefully"<<endl;  //cout<<" "<<endl;
	cout<<"1.INDICATIONS: @-fruit,##-border,**-maze"<<endl;
	cout<<"2.CONTROLS: a-LEFT, s-DOWN, w-UP, d-RIGHT, p-PAUSE"<<endl;
	cout<<"3.The size of the snake gets increased by 1 for every fruit "<<endl;
	cout<<"4.The speed of snake gets increased as you progress in the game and eventually becomes contant "<<endl;
	cout<<"5.If snake hits either maze or its own body then the game will end "<<endl;
}
int main()
{
	Setup();
	Instructions();
	cout<<endl;
	cout<<"IF YOU WOULD LIKE TO PLAY THIS GAME PRESS '1' ELSE PRESS ANY OTHER KEY:"<<endl;
	int a;
	cin>>a;
	if(a==1)
	{		
		while (Game==false)
	   {
		Draw();
		Input();
		Logic();
		Sleep(10); //sleep(10);
    	}
    	cout<<"YOU SCORED : "<<score<<" POINTS"<<endl;
    	cout<<"BETTER LUCK NEXT TIME"<<endl;
    	//cin>>a;
    }
	return 0;
}
