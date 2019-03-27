#include "./client.hpp"

// Protocol Interpreter for Server
void Client::initiateProtocolInterpreter(int connectionControlfd) {

    string msgFromServer;
    Recv(connectionControlfd, msgFromServer);
    logs(msgFromServer.c_str());

    string ftpRequest;
    string ftpResponse;
    
    while(true) {
        cout<<"J-FTP ➜ ";
		getline(std::cin, ftpRequest);
        Send(connectionControlfd, ftpRequest);
        Recv(connectionControlfd, ftpResponse);
        logs(ftpResponse.c_str());
    }
}

