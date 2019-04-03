#include "./../client.hpp"

int Client::cmd_PASS(int controlConnectionfd, const vector<string>& args) {
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    log(ftpResponse.c_str());
    if(ftpResponse.find("[RESPONSE] [AUTHENTICATION:FAILURE] Retry") == 0){
        // logs("I AM FAILED");
        return 0;
    }
    else{
        return 1;
    }
}
