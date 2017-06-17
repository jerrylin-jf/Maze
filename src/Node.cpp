#include "Node.h"

Node::Node()
{
    Start = false;
    Finish = false;
    Path = false;
    Obstacle = false;
    Path_Obstacle = false;
    path_color = 0;
    weight = 0;
}

Node::~Node()
{
    //dtor
}

void Node::setWeight(int new_Weight)
{
    weight = new_Weight;
}

void Node::setPath_Color(int new_path_color)
{
    path_color = new_path_color;
}

void Node::setStart(bool isStart)
{
    Start = isStart;
}

void Node::setFinish(bool isFinish)
{
    Finish = isFinish;
}

void Node::setObstacle(bool isObstacle)
{
    Obstacle = isObstacle;
}

void Node::setPath_Obstacle(bool isPath_Obstacle)
{
    Path_Obstacle = isPath_Obstacle;
}

void Node::setPath(bool isPath)
{
    Path = isPath;
}

int Node::getWeight()
{
    return weight;
}

int Node::getPath_Color()
{
    return path_color;
}

bool Node::getStart()
{
    return Start;
}

bool Node::getFinish()
{
    return Finish;
}

bool Node::getObstacle()
{
    return Obstacle;
}

bool Node::getPath_Obstacle()
{
    return Path_Obstacle;
}

bool Node::getPath()
{
    return Path;
}
