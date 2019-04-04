#include "./../server.hpp"

void Server::cmd_TYPE(int controlConnectionfd, const vector<string>& args [[gnu::unused]]) {
    string response = "Hey there,\nType Change is not supported for now.\n";
    response.append("The Default Representation Type is - ASCII Non-Print.");
    Send(controlConnectionfd, response , 502);
}