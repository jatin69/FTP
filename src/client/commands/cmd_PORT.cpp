#include "./../client.hpp"

/**PORT command
 *
 * @usage
 * sets new Data connection IP and PORT for the next command
*/
void Client::cmd_PORT(int controlConnectionfd, const vector<string>& args) {
    
    // @todo
    /**PORT Command format
     *
     * Actually, the port command has a comma format during the transfer.
     * But for simplicity here, we have hold on to original format
     * for transfer as well.
     *
     * We can implement comma format if needed,
     * encode port string on client side and decode it on the server side.
     *
     * encodePortCommandString(IP, PORT);
     *
     */
    const char* IP = args[1].c_str();
    int PORT = atoi(args[2].c_str());

    setDataDumpReceiverIP(IP);
    setDataDumpReceiverPortNumber(PORT);
 
    string res("PORT Command Successful.");
    res += "\nNew Data IP is : " + string(getDataDumpReceiverIP());
    res += "\nNew Data Port is : " + to_string(getDataDumpReceiverPortNumber());
    logs(res.c_str());
    
    // @logging
    // logClientConfiguration();

    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());
}
