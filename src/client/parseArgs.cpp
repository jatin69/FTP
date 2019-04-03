#include "./client.hpp"

Client parseArgs(int argc, char** argv){
    string IP = "127.0.0.1";
    int port = 9000;

    if(argc > 1)   { IP = argv[1];         }
    if(argc > 2)   { port = atoi(argv[2]); }
    
    Client ftpClient(IP, port);
    fprintf(stdout, "Connection to Server ...\nServer IP : %s \nPort      : %d", IP.c_str(), port);
       
    return ftpClient;
}