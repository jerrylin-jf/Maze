#ifndef NODE_H
#define NODE_H


class Node
{
    private:
        unsigned int weight;
        unsigned int path_color;
        bool Start;
        bool Finish;
        bool Path;
        bool Obstacle;
        bool Path_Obstacle;
    public:
        Node();
        virtual ~Node();

        void setWeight(int new_Weight);
        void setPath_Color(int new_path_color);
        void setStart(bool isStart);
        void setFinish(bool isFinish);
        void setObstacle(bool isObstacle);
        void setPath(bool isPath);
        void setPath_Obstacle(bool isPath_Obstacle);


        int getWeight();
        int getPath_Color();
        bool getStart();
        bool getFinish();
        bool getObstacle();
        bool getPath();
        bool getPath_Obstacle();

    protected:

};

#endif // NODE_H
