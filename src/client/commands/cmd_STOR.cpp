#include "./../client.hpp"

// STOR - put/store a file on server

void Client::cmd_STOR(int controlConnectionfd, const vector<string>& args) { 
      
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
        
        // waiting for this child's completion
        int statusOfChild;
        waitpid(pid, &statusOfChild, 0);
        
        int exitCodeOfChild;
        if ( WIFEXITED(statusOfChild) ) { 
            exitCodeOfChild = WEXITSTATUS(statusOfChild);
        } 
        
        if(exitCodeOfChild == 0){
            Send(controlConnectionfd, "Client Sent File Successfully.");
        }
        else{ 
            Send(controlConnectionfd, "Resuming current connection.");
        }
        
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
         * received elsewhere, we allow that IP to receive data
        */

        // Remote DUMP Mode : allow that IP to accept data
       
        if(string("CURRENT_MACHINE_IP").compare(getDataDumpReceiverIP()) != 0 ){
            handleDataDumpProcessAtRemoteIP();
            exit(0);
        }  

        // Normal DUMP mode     

        /**Special Note : Race Condition Resolving
         * 
         * It is extremely important that we create this data connection
         * and start listening before the server attempts to connect. 
         * 
        */
        int dataConnectionfd = createDataConnection(controlConnectionfd);
        close(controlConnectionfd);
        // @logging
        logs(getDataDumpReceiverIP());
        logv(getDataDumpReceiverPortNumber());
        
        Send(dataConnectionfd, "Client Ready to Send File");
        logs("Sending file in Binary Mode");
        
        Recv(dataConnectionfd, ftpResponse);
        logs(ftpResponse.c_str());
        
        string fileName(args[1]);
        SendFile(dataConnectionfd, fileName);
        /**Important Note -
         *
         * don't send anything else now.
         * Server knows about completion because of connection termination.
         *
         * if anything more is sent here, it will be assumed as part of the file
         * and will be appended in file at the client side.
        */
        logs("File Sent.");

        close(dataConnectionfd);  
        // @todo : close the control connection as well.      
        // close(controlConnectionfd);
        
        // child will exit upon completion of its task
        exit(0);
    }
}
 