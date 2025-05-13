#include "Point.h"
#include "Light/Light.h"

#include <map>
#ifndef ROAD_H
#define ROAD_H

class Road{
    public:
        Road(Point start, Point end, bool horz, int dir, Light* light_ = nullptr);
        void connectRoad(char direction, Road* road);
        Point getStart(){return startPoint;};
        Point getEnd(){return endPoint;};
        Light* getLight(){return light;};
        int getDirection(){return direction;};
        bool getHorz(){return isHorz;};
        bool onRoad(double pos, char coord);
        Road* nextRoad(char dir);
    private:
        Point startPoint, endPoint;
        bool isHorz;
        int direction;
        Light* light;
        std::map<char, Road*> nextRoads;
};

#endif