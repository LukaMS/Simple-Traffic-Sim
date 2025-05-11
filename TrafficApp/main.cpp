#include <iostream>
#include "Car/Car.h"
#include "Road/Point.h"
#include "Road/Road.h"
#include <chrono>
#include <thread>

int main(){
    Point start1(-100,0);
    Point end1(0.0 , 0.0);
    Point start2(0,0);
    Point end2(100,0);
    Road* road1 = new Road(start1, end1, true, 1);
    Road* road2 = new Road(start2, end2, true, 1);

    Car myCar(road1->getStart().x, road1->getStart().y, road1);
    road1->connectRoad('S', road2);

    std::chrono::seconds interval(1);
    while(myCar.getRoad() != nullptr){
        myCar.move();
        std::cout << "X: " << myCar.getX() << " Y: " << myCar.getY() << std::endl;
        std::this_thread::sleep_for(interval);
    }
    return 0;
}