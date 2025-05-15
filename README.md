# Simple-Traffic-Sim

A simple C++ traffic simulation engine with a built-in WebSocket server. Vehicles spawn at random on predefined roads, obey traffic-light rules, and broadcast their positions (and light states) over a WebSocket. You can hook this up to any frontend—e.g. a minimal Vite + React app—to visualize the simulation in real time.

## Features

- **Road network**: 8 one-way road segments arranged in a 4-way intersection  
- **Traffic lights**: 8 lights cycling through RED → GREEN → YELLOW  
- **Vehicle spawning**: Cars spawn every 2 s on one of four entry roads  
- **Vehicle movement**: Cars move one unit per tick, queue behind other cars, and randomly choose valid turns at green lights  
- **WebSocket server**: Broadcasts three JSON message types:
  - `{"type":"Map",   "data":[…]}` – road layout  
  - `{"type":"Lights","data":[…]}` – light positions & states  
  - `{"type":"Cars",  "data":[…]}` – car positions  

## Prerequisites

- **C++17** compiler  
- [CMake 3.28+](https://cmake.org/)  
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)  
- [websocketpp](https://github.com/zaphoyd/websocketpp) (with standalone ASIO)  

On Ubuntu-like systems you can install:
```bash
sudo apt install build-essential cmake libjsoncpp-dev
# websocketpp is header-only; just clone into third_party/
