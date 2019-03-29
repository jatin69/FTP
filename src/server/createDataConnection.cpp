#include "./server.hpp"

int Server::createDataConnection(int controlConnectionfd) {
    logs("[SERVER] : I am creating a new data Connection");

    const char* ip = getDataConnectionIP();
    int port = getDataConnectionPortNumber();

    logServerConfiguration();
    log(getDataConnectionIP());
    logs(ip);
    logv(port);

            /**Special Note : Race Condition Resolving
         * 
         * It is extremely important that we try to connect only after the
         * client has started listening.
         * 
         * To ensure this, we try to take measures.
         * 
         * sleep(1)
         * we delay the server by sleeping it for 1 second.
         * But this is not full proof. If the client is so slow that it takes
         * more than one second to start listening,
         * our this code will crash.
         * 
         * sleep(3)
         * We can delay the server by 3 seconds to ensure that 
         * client will be listening, but this increases response time to 3+ seconds,
         * which is very much.
         * 
         * Solution :
         * We implement a transfer request as stated in RFC-959
         * Recv() is a blocking call, so it'll wait until transfer request comes up.
         * 
        */
        // sleep(1);
        string transferRequest;
        // timeout of 3 seconds
        int stat = RecvWithTimeout(controlConnectionfd, transferRequest, 3);
        if(stat == -2){
            logs("TIMEOUT OCCURRED. No Transfer Request Received from Client.");
            exit(-2);
        }

        int dataConnectionfd = createSocketAndConnectToHost(ip, port );

        return dataConnectionfd;

    // server actually can't connect himself
    // he needs a transfer request
    // maybe it'll be needed with NAT
}