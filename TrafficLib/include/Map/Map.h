#ifndef MAP_H
#define MAP_H
#include <string>
#include "Road/Road.h"
#include "Car/Car.h"
#include <map>
#include <vector>
#include <memory>
#include "Light/Light.h"

class Map  {
    public:
        void updateMap();
        std::string getMapLayout();
        std::string getMapCars();
        std::string getLightLayout();
        void changeLights();
        void addCar(Road* road);
        void createMap();
        std::vector<Road*>& getStartRoads();
    private:
        std::map<Road*, std::vector<std::unique_ptr<Car>>> map_;
        std::vector<Road*> startRoads_;
        std::vector<Light*> lights_;
};

#endif