#include "./../server.hpp"

void Server::cmd_MODE(int controlConnectionfd, const vector<string>& args) {
    string response = "Hey there,\nMODE Change is not supported for now.\n";
    response.append("The Default transfer mode is - STREAM MODE.");
    Send(controlConnectionfd, response , 200);
}
