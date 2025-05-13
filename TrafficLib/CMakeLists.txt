find_package(jsoncpp REQUIRED)

add_library(TrafficLib src/Car.cpp src/Road.cpp src/Server.cpp src/Map.cpp src/Light.cpp)

message("Current Source Dir = ${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(TrafficLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/websocketpp)

target_link_libraries(TrafficLib PRIVATE JsonCpp::JsonCpp)

