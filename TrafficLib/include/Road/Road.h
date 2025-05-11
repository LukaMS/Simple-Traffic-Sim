#include "Point.h"
#include <map>
#ifndef ROAD_H
#define ROAD_H

class Road{
    public:
        Road(Point start, Point end, bool horz, int dir);
        void connectRoad(char direction, Road* road);
        Point getStart(){return startPoint;};
        Point getEnd(){return endPoint;};
        int getDirection(){return direction;};
        bool getHorz(){return isHorz;};
        bool onRoad(double pos, char coord);
        Road* nextRoad(char dir);
    private:
        Point startPoint, endPoint;
        bool isHorz;
        int direction;
        std::map<char, Road*> nextRoads;
};

#endif