
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <Windows.h>
#include "Node.h"

using namespace std;

int state = 1;
int pause = 1;
int counter;

char func;

const int WIDTH = 10;
Node Map[WIDTH][WIDTH];

typedef struct Coords
{
	int x;
	int y;
} Coords;

Coords StartCoords;
Coords FinishCoords;
Coords ActiveCoords;
Coords Obstacle;
Coords temp;

vector<Coords> Obstacles;
vector<Coords> invalid_set;

queue<Coords> working_set;
queue<Coords> neighbour_set;
queue<Coords> path;
queue<Coords> start_set;
queue<Coords> finish_set;
queue<Coords> pathObstacles_set;

void setMapStart(int x, int y)
{
	Map[x][y].setStart(true);
}

void setMapFinish(int x, int y)
{
	Map[x][y].setFinish(true);
}

void setMapObstacle(int x, int y)
{
	Map[x][y].setObstacle(true);
}

void setMapPath_Obstacle(int x, int y)
{
    Map[x][y].setPath_Obstacle(true);
}

void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int f = 7, int b = 0)
{
	unsigned short ForeColor = f + 16 * b;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, ForeColor);
}

void inputStart()
{
	Coords s;
	cout << "default start (y/n)? ";
	cin  >> func;
	if(func=='y')
    {
        s.x = 3;
        s.y = 3;
        setMapStart(s.x, s.y);
        start_set.push(s);

        s.x = 4;
        s.y = 1;
        setMapStart(s.x, s.y);
        start_set.push(s);

        s.x = 0;
        s.y = 5;
        setMapStart(s.x, s.y);
        start_set.push(s);

        s.x = 5;
        s.y = 5;
        setMapStart(s.x, s.y);
        start_set.push(s);

    }
    else
    {
        for(int i = 1; i<=3; i++)
        {
        cout << "input start x coordinate: ";
        cin >> s.x;
        cout << "input start y coordinate: ";
        cin >> s.y;
        setMapStart(s.x, s.y);
        start_set.push(s);
        }
    }



}

void inputFinish()
{
	Coords t;

	if(func=='y')
    {
        t.x = 0;
        t.y = 0;
        setMapFinish(t.x, t.y);
        finish_set.push(t);

        t.x = 1;
        t.y = 3;
        setMapFinish(t.x, t.y);
        finish_set.push(t);

        t.x = 7;
        t.y = 2;
        setMapFinish(t.x, t.y);
        finish_set.push(t);

        t.x = 6;
        t.y = 8;
        setMapFinish(t.x, t.y);
        finish_set.push(t);

    }
	else
    {
        for(int i = 1; i<=3; i++)
        {
            cout << "input end x coordinate: ";
            cin >> t.x;
            cout << "input end y coordinate: ";
            cin >> t.y;
            setMapFinish(t.x, t.y);
            finish_set.push(t);
        }
    }

}

void inputObstacle()
{
	Coords o;
	o.x = 4;
	o.y = 3;
	setMapObstacle(o.x, o.y);
	Obstacles.push_back(o);

	o.x = 4;
	o.y = 4;
	setMapObstacle(o.x, o.y);
	Obstacles.push_back(o);


	o.x = 3;
	o.y = 5;
	setMapObstacle(o.x, o.y);
	Obstacles.push_back(o);
/*
	o.x = 3;
	o.y = 6;
	setMapObstacle(o.x, o.y);
	Obstacles.push_back(o);
//

    o.x = 3;
	o.y = 7;
	setMapObstacle(o.x, o.y);
	setMapPath_Obstacle(o.x, o.y);
	Obstacles.push_back(o);
//
	o.x = 4;
	o.y = 7;
	setMapObstacle(o.x, o.y);
	Obstacles.push_back(o);

	o.x = 5;
	o.y = 7;
	setMapObstacle(o.x, o.y);
	Obstacles.push_back(o);*/
}

void printMap()
{
	GotoXY(0, 0);
	for (int y = 0; y<WIDTH; y++)
	{
		for (int x = 0; x<WIDTH; x++)
		{
			//print Start
			if (Map[x][y].getStart())
			{
				SetColor(0, 7); //黑底白字
				cout << " S";
				SetColor();
			}
			else
				//print Finish
				if (Map[x][y].getFinish())
				{
					SetColor(0, 7);
					cout << " T";
					SetColor();
				}
				else
					//print Obstacle
					if (Map[x][y].getObstacle())
					{
					    /*
						SetColor(2, 2);
						cout << "  ";   //印綠色
						SetColor();
						*/
						SetColor(7,2);  //白字綠底
						if(Map[x][y].getObstacle()<=9)
                            cout << " " << Map[x][y].getWeight();
                        else
                            cout << Map[x][y].getWeight();
                        SetColor();
					}
					else
						//print Path
						if (Map[x][y].getPath())
						{
						    if(Map[x][y].getPath_Obstacle())
                            {
                                SetColor(Map[x][y].getPath_Color(),Map[x][y].getPath_Color());
                                cout << "  ";
                                SetColor();
                            }
                            else
						    {
						        SetColor(0, 7);
                                if (Map[x][y].getWeight() != 0 && Map[x][y].getWeight() <= 9)
                                    cout << " " << Map[x][y].getWeight();
                                else
                                    cout << Map[x][y].getWeight();
                                SetColor();
						    }

						}
						else
							//print not go
							if (Map[x][y].getWeight() == 0)
							{
								SetColor(0, 0);
								cout << "  "; //印藍色
								SetColor();
							}
							else
								//print number
								if (Map[x][y].getWeight() != 0 && Map[x][y].getWeight() <= 9)
									cout << " " << Map[x][y].getWeight();
								else
									cout << Map[x][y].getWeight();
		}
		cout << endl;
	}
}

bool CheckInvalid(Coords toCheck)
{
	//確認有無超出格子範圍
	if (toCheck.x >= 10)
		return false;
	if (toCheck.y >= 10)
		return false;
	//確認是否有數字了
	if (state != 2)
	{
		if (Map[toCheck.x][toCheck.y].getWeight() != 0)
		return false;
	}

	//確認是否是Obstacles
	for (int i = 0; i < Obstacles.size(); i++)
	{
		if (toCheck.x == Obstacles[i].x)
		{
			if (toCheck.y == Obstacles[i].y)
			{
				return false;
			}

		}
	}


	if (state != 2)
	{
		for (int i = 0; i < invalid_set.size(); i++)
		{
			if (toCheck.x == invalid_set[i].x)
			{
				if (toCheck.y == invalid_set[i].y)
				{
					return false;
				}
			}
		}
	}
	//紀錄之前確認過的
	invalid_set.push_back(toCheck);
	return true;

}

void FindNeighbours()
{
	Coords Neighbour;
	if ((ActiveCoords.x >= 0) && (ActiveCoords.x <= 9))
	{
		//左鄰居
		if (ActiveCoords.x > 0)
		{
			Neighbour.x = ActiveCoords.x - 1;
			Neighbour.y = ActiveCoords.y;
			if (CheckInvalid(Neighbour))
				neighbour_set.push(Neighbour);
		}
		//右鄰居
		if (ActiveCoords.x < 9)
		{
			Neighbour.x = ActiveCoords.x + 1;
			Neighbour.y = ActiveCoords.y;
			if (CheckInvalid(Neighbour))
				neighbour_set.push(Neighbour);
		}
	}

	if ((ActiveCoords.y >= 0) && (ActiveCoords.y <= 9))
	{
		if (ActiveCoords.y > 0)
		{
			Neighbour.x = ActiveCoords.x;
			Neighbour.y = ActiveCoords.y - 1;
			if (CheckInvalid(Neighbour))
				neighbour_set.push(Neighbour);
		}
		if (ActiveCoords.y < 9)
		{
			Neighbour.x = ActiveCoords.x;
			Neighbour.y = ActiveCoords.y + 1;
			if (CheckInvalid(Neighbour))
				neighbour_set.push(Neighbour);
		}
	}
}

void LeePopulate()
{
	int ActiveWeight = 0;

	while (!Map[FinishCoords.x][FinishCoords.y].getWeight())
	{
		printMap();

		ActiveCoords = working_set.front();
		working_set.pop();
		//find neighbour
		FindNeighbours();
		Map[ActiveCoords.x][ActiveCoords.y].setWeight(ActiveWeight);
		//將neighbour_set存入working_set
		if (working_set.empty())
		{
			ActiveWeight++;
			working_set = neighbour_set;
			//neighbour_set不為空就pop
			while (!neighbour_set.empty())
				neighbour_set.pop();
		}
	}
	state = 2;
}

void LeeBacktrace()
{
	//清空working_set
	if (!working_set.empty())
	{
		while (!working_set.empty())
			working_set.pop();
	}

	int CurrentWeight = 0;
	Coords Neighbour;

	ActiveCoords = FinishCoords;
	CurrentWeight = Map[FinishCoords.x][FinishCoords.y].getWeight();
	while (!((ActiveCoords.x == StartCoords.x) && (ActiveCoords.y == StartCoords.y)))
	{
		FindNeighbours();
		do
		{
			Neighbour = neighbour_set.front();
			neighbour_set.pop();
			if ((Neighbour.x == StartCoords.x) && (Neighbour.y == StartCoords.y))
				break;
		} while (Map[Neighbour.x][Neighbour.y].getWeight() > CurrentWeight || (Map[Neighbour.x][Neighbour.y].getWeight() == 0));

		CurrentWeight = Map[Neighbour.x][Neighbour.y].getWeight();
		path.push(Neighbour);

		ActiveCoords = Neighbour;

		while (!neighbour_set.empty())
			neighbour_set.pop();
	}
	state = 3;
}

void LeeShowPath()
{

	Coords Pathnode;

	while (!path.empty())
	{
		Pathnode = path.front();
		path.pop();
		if(path.size()!=0)
        {
            pathObstacles_set.push(Pathnode);
            setMapPath_Obstacle(Pathnode.x,Pathnode.y);
            Map[Pathnode.x][Pathnode.y].setPath_Color(counter);
        }
		Map[Pathnode.x][Pathnode.y].setPath(true);
		printMap();
	}
	state = 4;
}
void formatCoord()
{

    start_set.push(StartCoords);
    finish_set.push(FinishCoords);
    invalid_set.clear();
	Obstacles.clear();

	//GotoXY(0, 0);
	for (int y = 0; y < WIDTH;	y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			Map[x][y].setWeight(0);
		}
	}
	//state = 5;
}

void inputPathObstacles()
{
    int pathSize = pathObstacles_set.size();
    while(pathSize!=0)
    {
        for(int i = 1; i <= pathSize; i++)
        {
            temp = pathObstacles_set.front();
            pathObstacles_set.pop();
            Obstacles.push_back(temp);
            pathObstacles_set.push(temp);
        }
        break;
    }
}

void initial()
{
    StartCoords = start_set.front();
    start_set.pop();
    working_set.push(StartCoords);

    FinishCoords = finish_set.front();
    finish_set.pop();
}

void finalMap(void);

int main(void)
{
	inputStart();
	inputFinish();
	int size = start_set.size();

    system("CLS");
	while (true)
	{
      //  inputObstacle();

        printMap();



		for (counter = 1; counter <= size; counter++)
		{
			initial();
			inputPathObstacles();

			for(int j = 1; j<size; j++)
            {
                temp = start_set.front();
                start_set.pop();
                Obstacles.push_back(temp);
                start_set.push(temp);

                temp = finish_set.front();
                finish_set.pop();
                Obstacles.push_back(temp);
                finish_set.push(temp);
            }


			//in LeeALGO
			switch (state)
			{
			case 1:
			{
				LeePopulate(); // dead in this
			}
			case 2:
			{
				LeeBacktrace();
			}
			case 3:
			{

				LeeShowPath();
			}
			case 4:
			{
				formatCoord();
			}
			}
			state = 1;
			pause++;
			system("pause");
		}

		break;
	}
 //   cout << "pathObstacles_set.size: " << pathObstacles_set.size() << endl;
    finalMap();
	return 0;
}

void finalMap()
{
	GotoXY(0, 0);
	for (int y = 0; y<WIDTH; y++)
	{
		for (int x = 0; x<WIDTH; x++)
		{
			//print Start
			if (Map[x][y].getStart())
			{
				SetColor(0, 7); //白字黑底
				cout << " S";
				SetColor();
			}
			else
            {
                if (Map[x][y].getFinish())
                {
                    SetColor(0, 7); //白字黑底
                    cout << " T";
                    SetColor();
                }
                else
                {
                    if (Map[x][y].getPath())
                    {
                        SetColor(Map[x][y].getPath_Color(), Map[x][y].getPath_Color());
                        cout << "  ";
                        SetColor();
                    }
                    else
                        cout << "  ";
                }
            }



		}
		cout << endl;
	}

}
