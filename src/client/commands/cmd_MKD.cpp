#include "./../client.hpp"

void Client::cmd_MKD(int controlConnectionfd, const vector<string>& args) {
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    log(ftpResponse.c_str());
}
