#include "./../client.hpp"

void Client::cmd_PORT(int controlConnectionfd, const vector<string>& args) {
    
    // port has to be sent in an encoded format
    // but i am sending ftprequest directly. Capture that somehow.
    // maybe the santize ftpRequest command

    // @todo : works for now

    // client simply tells server to dump data at `x` port
    // client should create a socket, bind and start listening 
    // at the port `x` 
    // for that we need to know port `x`

    // in case the communication is between two servers

    const char* IP = args[1].c_str();
    int PORT = atoi(args[2].c_str());

    setDataDumpReceiverIP(IP);
    setDataDumpReceiverPortNumber(PORT);
 
    string res;
    res.append("PORT Command Successful.");
    res.append("\nNew Data IP is : ");
    res.append(getDataDumpReceiverIP());
    res.append("\nNew Data Port is : ");
    res.append(to_string(getDataDumpReceiverPortNumber()));
    logs(res.c_str());

    logClientConfiguration();

    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    log(ftpResponse.c_str());
}
