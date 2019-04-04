#include "./../client.hpp"

void Client::cmd_TYPE(int controlConnectionfd, const vector<string>& args  [[gnu::unused]]) {
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    log(ftpResponse.c_str());
}
