#include "Car/Car.h"
#include <cmath>

Car::Car(double x, double y, Road* road)
    : posX{ x }
    , posY{ y }
    , currentRoad{ road }
{
}

double Car::getX(){ return posX; }
double Car::getY(){ return posY; }

void Car::move(Car* carInFront){
    double inFrontX = carInFront->getX();
    double inFrontY = carInFront->getY();

    if (currentRoad == nullptr) return;

    bool movingHorz = currentRoad->getHorz();
    int direction = currentRoad->getDirection();
    
    if(movingHorz){
        double newX = posX + 1*direction;
        bool onRoad = currentRoad->onRoad(newX, 'X');
        bool noCar = canMove(this, carInFront, movingHorz, newX);
        if(onRoad){
            if(noCar){
                posX = newX;
            } else {
                return;
            }    
        } else {
            Light* light = currentRoad->getLight();
            if(light->getState() == Light::GREEN){
                Road* next = currentRoad->nextRoad('R');
                if(next != nullptr){
                    currentRoad = currentRoad->nextRoad('R');
                    Point start = currentRoad->getStart();
                    posX = start.x;
                    posY = start.y;
                } else {
                    currentRoad = nullptr;
                }
            } else {
                return;
            }
        }  
    } else {
        double newY = posY + 1*direction;
        bool onRoad = currentRoad->onRoad(newY, 'Y');
        bool noCar = canMove(this, carInFront, movingHorz, newY);
        if(onRoad){
            if(noCar){
                posY = newY;
            } else {
                return;
            }    
        } else {
            Light* light = currentRoad->getLight();
            if(light->getState() == Light::GREEN){
                Road* next = currentRoad->nextRoad('R');
                if(next != nullptr){
                    currentRoad = currentRoad->nextRoad('R');
                    Point start = currentRoad->getStart();
                    posX = start.x;
                    posY = start.y;
                } else {
                    currentRoad = nullptr;
                }
            } else {
                return;
            }
        }  
    }
}

bool Car::canMove(Car* car, Car* carInFront, bool movingHorz, double newPos) {
    if (!carInFront) return true;

    if (movingHorz) {
        return std::abs(newPos - carInFront->getX()) > 5;
    } else {
        return std::abs(newPos - carInFront->getY()) > 5;
    }
}
