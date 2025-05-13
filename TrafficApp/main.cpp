#include <iostream>
#include "Car/Car.h"
#include "Road/Point.h"
#include "Road/Road.h"
#include "Server/Server.h"
#include "Map/Map.h"
#include <chrono>
#include <thread>
#include <atomic>
#include <random>

int main(){

    std::atomic<bool> running(true);

    Map map;
    map.createMap();

    Server server;
    server.setMap(&map);  // pass reference to map
    server.start(9002);

    std::thread simThread([&]() {
        while (running) {
            map.updateMap();
            // Send updated car positions
            std::string carData = map.getMapCars();
            server.sendMessage(carData);
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        }
    });

    std::thread spawnThread([&]() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 3);

        while (running) {
            Road* randomStart = map.getStartRoads()[dist(gen)];
            map.addCar(randomStart);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });

    std::thread lightThread([&]() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(5, 8); // seconds

        while (running) {
            map.changeLights();
            std::string lightData = map.getLightLayout();
            server.sendMessage(lightData);

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            map.changeLights();
            std::string lightDataAgain = map.getLightLayout();
            server.sendMessage(lightDataAgain);

            int delay = dist(gen);
            std::this_thread::sleep_for(std::chrono::seconds(delay));
        }
    });


    std::cin.get();  // wait until Enter is pressed
    running = false;     // Stop simulation loop
    simThread.join();
    spawnThread.join();
    lightThread.join();
    server.stop();
    return 0;
}