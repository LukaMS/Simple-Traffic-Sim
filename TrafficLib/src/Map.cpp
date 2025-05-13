#include "Map/Map.h"
#include "Road/Point.h"
#include "Road/Road.h"
#include <json/json.h>
#include <string>
#include <iostream>
#include "Light/Light.h"

void Map::createMap(){
    //LIGHTS
    Light* EastWest1 = new Light(Light::RED1, -40,20);
    Light* EastWest2 = new Light(Light::RED1, -40,-20);

    Light* WestEast1 = new Light(Light::RED1, 40,20);
    Light* WestEast2 = new Light(Light::RED1, 40,-20);

    Light* NorthSouth1 = new Light(Light::GREEN, 20, -40);
    Light* NorthSouth2 = new Light(Light::GREEN, -20, -40);

    Light* SouthNorth1 = new Light(Light::GREEN, 20, 40);
    Light* SouthNorth2 = new Light(Light::GREEN, -20, 40);

    for (Light* light : {EastWest1, EastWest2, WestEast1, WestEast2, NorthSouth1, NorthSouth2, SouthNorth1, SouthNorth2}){
        lights_.push_back(light);
    }

    //ROADS

    //WEST TO EAST
    Point Road1Start(-200,-10);
    Point Road1End(-10,-10);
    Road* Road1 = new Road(Road1Start, Road1End, true, 1, WestEast1);

    Point Road2Start(10,-10);
    Point Road2End(200,-10);
    Road* Road2 = new Road(Road2Start, Road2End, true, 1);

    //EAST TO WEST
    Point Road3Start(200,10);
    Point Road3End(10,10);
    Road* Road3 = new Road(Road3Start, Road3End, true, -1, EastWest1);

    Point Road4Start(-10,10);
    Point Road4End(-200,10);
    Road* Road4 = new Road(Road4Start, Road4End, true, -1);

    //SOUTH TO NORTH
    Point Road5Start(10,-200);
    Point Road5End(10,-10);
    Road* Road5 = new Road(Road5Start, Road5End, false, 1, SouthNorth1);

    Point Road6Start(10,10);
    Point Road6End(10,200);
    Road* Road6 = new Road(Road6Start, Road6End, false, 1);

    //NORTH TO SOUTH
    Point Road7Start(-10,200);
    Point Road7End(-10,10);
    Road* Road7 = new Road(Road7Start, Road7End, false, -1, NorthSouth1);

    Point Road8Start(-10,-10);
    Point Road8End(-10,-200);
    Road* Road8 = new Road(Road8Start, Road8End, false, -1);

    //CONNECTIONS
    Road1->connectRoad('S', Road2);
    Road1->connectRoad('R', Road8);
    Road1->connectRoad('L', Road6);

    Road3->connectRoad('S', Road4);
    Road3->connectRoad('R', Road6);
    Road3->connectRoad('L', Road8);

    Road5->connectRoad('S', Road6);
    Road5->connectRoad('R', Road2);
    Road5->connectRoad('L', Road4);

    Road7->connectRoad('S', Road8);
    Road7->connectRoad('R', Road4);
    Road7->connectRoad('L', Road2);

    //Add Roads to Map
    for (Road* road : {Road1, Road2, Road3, Road4, Road5, Road6, Road7, Road8}) {
        map_[road] = std::vector<std::unique_ptr<Car>>();
    }

    startRoads_ = {Road1, Road3, Road5, Road7};

}

void Map::changeLights(){
    for (Light* light : lights_) {
                light->changeState();  // Switch to next state
            }
}

void Map::addCar(Road* road) {
    std::cout << "test" << std::endl;
    auto newCar = std::make_unique<Car>(road->getStart().x, road->getStart().y, road);
    map_[road].push_back(std::move(newCar));
}

std::vector<Road*>& Map::getStartRoads() {
    return startRoads_;
}

std::string Map::getMapLayout() {
    Json::Value layout(Json::arrayValue);

    for (const auto& pair : map_) {
        Road* road = pair.first;
        Point start = road->getStart();
        Point end = road->getEnd();

        Json::Value roadJson;
        roadJson["start"]["x"] = start.x;
        roadJson["start"]["y"] = start.y;
        roadJson["end"]["x"] = end.x;
        roadJson["end"]["y"] = end.y;
        roadJson["horizontal"] = road->getHorz(); 
        roadJson["direction"] = road->getDirection();

        layout.append(roadJson);
    }

    Json::Value wrapped;
    wrapped["type"] = "Map";
    wrapped["data"] = layout;

    Json::StreamWriterBuilder writer;
    std::string jsonString = Json::writeString(writer, wrapped);

    return jsonString;
}

std::string Map::getLightLayout(){
    Json::Value root(Json::arrayValue);

    for (Light* light : lights_){
        Json::Value lightJson;
        lightJson["STATE"] = light->getState();
        lightJson["X"] = light->getX();
        lightJson["Y"] = light->getY();
        root.append(lightJson);
    }

    Json::Value wrapped;
    wrapped["type"] = "Lights";
    wrapped["data"] = root;

    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, wrapped);
}

std::string Map::getMapCars() {
    Json::Value root(Json::arrayValue);

    for (const auto& pair : map_) {
        const auto& cars = pair.second;
        for (const auto& car : cars) {
            Json::Value carJson;
            carJson["X"] = car->getX();
            carJson["Y"] = car->getY();
            root.append(carJson);
        }
    }

    Json::Value wrapped;
    wrapped["type"] = "Cars";
    wrapped["data"] = root;

    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, wrapped);
}

void Map::updateMap() {
    // Copy the keys if you might move cars between vectors,
    // but since you’re only moving between existing vectors,
    // iterating by reference is fine:
    for (auto& [roadPtr, cars] : map_) {
        Car* carInFront = nullptr;
        for (auto carIt = cars.begin(); carIt != cars.end(); /*no-op*/) {
            Car* car = carIt->get();

            if (!car->getRoad()) {
                carIt = cars.erase(carIt);
            } else {
                Road* before = roadPtr;
                car->move(carInFront);
                Road* after = car->getRoad();

                if (after != before && after) {
                    auto moved = std::move(*carIt);
                    carIt = cars.erase(carIt);
                    map_[after].push_back(std::move(moved));
                } else {
                    carInFront = car;
                    ++carIt;
                }
            }
        }
    }
}

