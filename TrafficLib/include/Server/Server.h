#ifndef TRAFFICLIB_INCLUDE_SERVER_SERVER_H_
#define TRAFFICLIB_INCLUDE_SERVER_SERVER_H_

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <set>
#include <mutex>
#include <thread>
#include <string>
#include "Map/Map.h"

class Server {
public:
    Server();
    ~Server();

    void start(int port = 9002);
    void broadcastPosition(double x, double y);
    void sendMessage(std::string msg);
    void stop();
    void setMap(Map* map);

private:
    typedef websocketpp::server<websocketpp::config::asio> WebSocketServer;
    typedef websocketpp::connection_hdl ConnectionHandle;

    void onOpen(ConnectionHandle hdl);
    void onClose(ConnectionHandle hdl);
    void onMessage(ConnectionHandle hdl, WebSocketServer::message_ptr msg);
    void run();

    WebSocketServer server_;
    std::set<ConnectionHandle, std::owner_less<ConnectionHandle>> connections_;
    std::mutex connMutex_;
    std::thread serverThread_;
    bool isRunning_;
    Map* map_;
};

#endif  // TRAFFICLIB_INCLUDE_SERVER_SERVER_H_
