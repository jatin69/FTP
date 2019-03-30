#include "./../server.hpp"

void Server::cmd_STOR(int controlConnectionfd, const vector<string>& args){
    
    string ftpResponse;
    int pid = fork();
    
    if(pid < 0){        // error
        printError();
        throw runtime_error("[SERVER:CMD:LIST] Fork Error");
    }
 
    if(pid > 0) {       // parent
        int statusOfChild;
        // waiting for this child's completion
        waitpid(pid, &statusOfChild, 0);
        
        int exitCodeOfChild;
        if ( WIFEXITED(statusOfChild) ) { 
            exitCodeOfChild = WEXITSTATUS(statusOfChild);
        } 
        
        Recv(controlConnectionfd, ftpResponse);
        log(ftpResponse.c_str());

        if(exitCodeOfChild == 0){
            Send(controlConnectionfd, "Server Received File Successfully.");
        }
        else{
            Send(controlConnectionfd, "Resuming current connection.");
        }
    }

    if(pid==0) {        // child
        
        // child does not need control connection
        // close(controlConnectionfd);

        int dataConnectionfd = createDataConnection(controlConnectionfd);  
        // int dataConnectionfd = controlConnectionfd;
        
        logs(getDataConnectionIP());
        logv(getDataConnectionPortNumber());
        
        Recv(dataConnectionfd, ftpResponse);
        logs(ftpResponse.c_str());
        
        Send(dataConnectionfd, "Server Ready To Receive file.");
        logs("Server Ready To Receive file.");
        
        string fileName(args[1]);
        RecvFile(dataConnectionfd, fileName);
        logs("File Received.");

        // child will exit upon completion of its task
        close(dataConnectionfd);        
        exit(0);
    }
}
