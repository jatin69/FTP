#include "./../client.hpp"

// LIST - list the directory contents

void Client::cmd_LIST(int controlConnectionfd, const vector<string>& args [[gnu::unused]]) { 
     
    string ftpResponse;

    /**Create a child - As per RFC 959
     * 
     * Why are we creating a child?
     * When the client requests a big stream of data, the data is to be
     * transferred by the connectionControlfd and not the controlfd.
     * This reponsibility of creating and destroying the connectionControlfd
     * is given to the child process.
     * Parent waits for child to complete. Once the child has done its work,
     * The final response is collected by controlfd.
    */
    int pid = fork();

    if(pid < 0){            // error
        printError();
        throw runtime_error("[CLIENT:CMD:LIST] Fork Error");
    }
    else if(pid > 0) {      // parent
        
        // waiting for child completion and final response
        int statusOfChild;
        wait(&statusOfChild);
        
        Recv(controlConnectionfd, ftpResponse);
        logs(ftpResponse.c_str());
    }
    else if(pid==0) {       // child
    
    /**Data Connection fd
     * 
     * The client starts passively listening to the 
     * [HOST:PORT] socket specified by [PORT Command OR Default]
     * The server actively connects to client and transfers data.
     * 
     * In case the PORT command is explicitly used and the dump is to be
     * received elsewhere, we allow that IP to receive data.
    */

    // Remote DUMP Mode : allow that IP to accept data

    if(string("CURRENT_MACHINE_IP").compare(getDataDumpReceiverIP()) != 0 ){
        handleDataDumpProcessAtRemoteIP();
        exit(0);
    }  

    // Normal DUMP mode : same (Control Connection) machine receives data
    
    /**Special Note : Race Condition Resolving
     * 
     * It is extremely important that we create this data connection
     * and start listening before the server attempts to connect. 
     * 
    */
    int dataConnectionfd = createDataConnection(controlConnectionfd);
    
    // Child no longer needs control connection, we can close it
    close(controlConnectionfd);

    // @logging
    logs(getDataDumpReceiverIP());
    logv(getDataDumpReceiverPortNumber());
    
    Recv(dataConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());
    
    Recv(dataConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());
    
    // child will exit upon completion of its task
    close(dataConnectionfd);    
    exit(0);
    }
}
