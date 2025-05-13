#include "Road/Road.h"
#include "Light/Light.h"

Road::Road(Point start, Point end, bool horz, int dir, Light* light_)
    : startPoint{start}
    , endPoint{end}
    , isHorz{horz}
    , direction{dir}
    , light{light_}
{
}

void Road::connectRoad(char direction, Road* road){
    nextRoads[direction] = road;
}

bool Road::onRoad(double pos, char coord){
    if(direction == -1){
        if(coord == 'X'){
            return pos >= endPoint.x;
        } else {
            return pos >= endPoint.y;
        }
    } else {
        if(coord == 'X'){
            return pos <= endPoint.x;
        } else {
            return pos <= endPoint.y;
        }
    }
}

Road* Road::nextRoad(char dir){
    return nextRoads[dir];
}