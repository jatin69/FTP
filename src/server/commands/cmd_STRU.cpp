#include "./../server.hpp"

void Server::cmd_STRU(int controlConnectionfd, const vector<string>& args [[gnu::unused]]) {
    string response = "Hey there,\nType Change is not supported for now.\n";
    response.append("The Default file structure type is - FILE");
    Send(controlConnectionfd, response , 502);
}
