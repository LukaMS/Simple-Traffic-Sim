#include "./Road/Road.h"
#ifndef TRAFFICLIB_INCLUDE_CAR_CAR_H_
#define TRAFFICLIB_INCLUDE_CAR_CAR_H_

class Car {
    public:
        Car(double x, double y, Road* road);
        double getX();
        double getY();
        void move();
        Road* getRoad(){return currentRoad;};
    private:
        double posX, posY;
        Road* currentRoad;
};

#endif /* TRAFFICLIB_INCLUDE_CAR_CAR_H_ */