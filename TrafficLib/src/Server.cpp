#define ASIO_STANDALONE
#include "Server/Server.h"
#include "Map/Map.h"
#include <iostream>

Server::Server() : isRunning_(false) {
    server_.init_asio();

    server_.set_open_handler([this](ConnectionHandle hdl) {
        onOpen(hdl);
    });

    server_.set_close_handler([this](ConnectionHandle hdl) {
        onClose(hdl);
    });

    server_.set_message_handler([this](ConnectionHandle hdl, WebSocketServer::message_ptr msg) {
        onMessage(hdl, msg);
    });
}

Server::~Server() {
    stop();
}

void Server::setMap(Map* map) {
    map_ = map;
}

void Server::start(int port) {
    if (isRunning_) return;

    isRunning_ = true;
    serverThread_ = std::thread([this, port]() {
        server_.listen(port);
        server_.start_accept();
        run();
    });
}

void Server::stop() {
    if (!isRunning_) return;

    server_.stop_listening();
    server_.stop();
    if (serverThread_.joinable())
        serverThread_.join();

    isRunning_ = false;
}

void Server::run() {
    try {
        server_.run();
    } catch (const std::exception& e) {
        std::cerr << "WebSocket server error: " << e.what() << std::endl;
    }
}

void Server::onOpen(ConnectionHandle hdl) {
    std::lock_guard<std::mutex> lock(connMutex_);
    connections_.insert(hdl);
    std::cout << "Client connected\n";

    if (map_) {
        std::string mapData = map_->getMapLayout();
        std::string lightData = map_->getLightLayout();
        server_.send(hdl, mapData, websocketpp::frame::opcode::text);
        server_.send(hdl, lightData, websocketpp::frame::opcode::text);
    }
}


void Server::onClose(ConnectionHandle hdl) {
    std::lock_guard<std::mutex> lock(connMutex_);
    connections_.erase(hdl);
}

void Server::onMessage(ConnectionHandle hdl, WebSocketServer::message_ptr msg) {
    std::cout << "Received message: " << msg->get_payload() << std::endl;
}

void Server::broadcastPosition(double x, double y) {
    std::string msg = "{\"x\":" + std::to_string(x) + ",\"y\":" + std::to_string(y) + "}";

    std::lock_guard<std::mutex> lock(connMutex_);
    for (const auto& hdl : connections_) {
        server_.send(hdl, msg, websocketpp::frame::opcode::text);
    }
}

void Server::sendMessage(std::string msg){
    std::lock_guard<std::mutex> lock(connMutex_);
    for (const auto& hdl : connections_) {
        server_.send(hdl, msg, websocketpp::frame::opcode::text);
    }
}
