add_library(TrafficLib src/Car.cpp src/Road.cpp src/Server.cpp)

message("Current Source Dir = ${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(TrafficLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

