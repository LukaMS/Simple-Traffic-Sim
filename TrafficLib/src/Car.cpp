#include "Car/Car.h"
#include <cmath>
#include <algorithm>
#include <array>
#include <random>

Car::Car(double x, double y, Road* road)
    : posX{ x }
    , posY{ y }
    , currentRoad{ road }
{
}

double Car::getX(){ return posX; }
double Car::getY(){ return posY; }

void Car::move(Car* carInFront){
    if (!currentRoad) return;

    bool movingHorz = currentRoad->getHorz();
    int  dir        = currentRoad->getDirection();

    // compute the “would‐be” next position
    double newPos = (movingHorz ? posX : posY) + dir;
    bool   onRoad = currentRoad->onRoad(newPos, movingHorz ? 'X' : 'Y');
    bool   noCar  = canMove(this, carInFront, movingHorz, newPos);

    if (onRoad) {
        if (noCar) {
            if (movingHorz) posX = newPos;
            else             posY = newPos;
        }
        return;
    }

    // we’ve reached the end of this road
    Light* light = currentRoad->getLight();
    if(!light){
        currentRoad = nullptr;
        return;
    }
    if (light->getState() != Light::GREEN)
        return;

    // ** TURN SELECTION **
    std::array<char,3> prefs = { 'S','L','R' };

    static std::mt19937 rng{ std::random_device{}() };
    std::shuffle(prefs.begin(), prefs.end(), rng);

    // 2) find the first direction that actually exists:
    for (char turn : prefs) {
        Road* next = currentRoad->nextRoad(turn);
        if (next) {
            currentRoad = next;
            Point  s   = next->getStart();
            posX = s.x;
            posY = s.y;
            return;
        }
    }

    currentRoad = nullptr;
}


bool Car::canMove(Car* car, Car* carInFront, bool movingHorz, double newPos) {
    if (!carInFront) return true;

    if (movingHorz) {
        return std::abs(newPos - carInFront->getX()) > 10;
    } else {
        return std::abs(newPos - carInFront->getY()) > 10;
    }
}
