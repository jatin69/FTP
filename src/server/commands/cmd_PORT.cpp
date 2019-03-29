#include "./../server.hpp"

// Set new Data connection IP and PORT for the next command
void Server::cmd_PORT(int controlConnectionfd, const vector<string>& args) {
        const char* IP;
        int PORT;

        // @todo: swap these comments
        // encode port and everything and decode this side : maybe
        // resolvePortCommandString(args[1], IP, PORT);
        // accepting : 127.0.0.1 9000
        IP = args[1].c_str();
        PORT = atoi(args[2].c_str());

        setDataConnectionIP(IP);
        setDataConnectionPortNumber(PORT);

        string res;
        res.append("PORT Command Successful.");
        res.append("\nNew Data IP is : ");
        res.append(getDataConnectionIP());
        res.append("\nNew Data Port is : ");
        res.append(to_string(getDataConnectionPortNumber()));

        logServerConfiguration();

        Send(controlConnectionfd, res , 220);
}
