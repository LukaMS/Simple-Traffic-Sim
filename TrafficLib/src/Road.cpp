#include "Road/Road.h"

Road::Road(Point start, Point end, bool horz, int dir)
    : startPoint{start}
    , endPoint{end}
    , isHorz{horz}
    , direction{dir}
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
        if(coord = 'X'){
            return pos <= endPoint.x;
        } else {
            return pos <= endPoint.y;
        }
    }
}

Road* Road::nextRoad(char dir){
    return nextRoads[dir];
}