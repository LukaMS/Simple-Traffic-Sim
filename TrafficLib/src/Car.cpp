#include "Car/Car.h"

Car::Car(double x, double y, Road* road)
    : posX{ x }
    , posY{ y }
    , currentRoad{ road }
{
}

double Car::getX(){ return posX; }
double Car::getY(){ return posY; }

void Car::move(){

    if (currentRoad == nullptr) return;

    bool movingHorz = currentRoad->getHorz();
    int direction = currentRoad->getDirection();
    
    if(movingHorz){
        double newX = posX + 10*direction;
        if(currentRoad->onRoad(newX, 'X')){
            posX = newX;
        } else {
            Road* next = currentRoad->nextRoad('S');
            if(next != nullptr){
                currentRoad = currentRoad->nextRoad('S');
                Point start = currentRoad->getStart();
                posX = start.x;
                posY = start.y;
            } else {
                currentRoad = nullptr;
            }
        }  
    } else {
        double newY = posY + 10*direction;
        if(currentRoad->onRoad(newY, 'Y')){
            posY = newY;
        } else {
            Road* next = currentRoad->nextRoad('S');
            if(next != nullptr){
                currentRoad = currentRoad->nextRoad('S');
                Point start = currentRoad->getStart();
                posX = start.x;
                posY = start.y;
            } else {
                currentRoad = nullptr;
            }
        }
    }
}