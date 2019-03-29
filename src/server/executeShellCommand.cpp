#include "./server.hpp"

string executeShellCommand(const string& cmd) {
    FILE *pipe = popen(cmd.c_str(), "r");
	if (!pipe){
        printError("[ERROR:EXEC]");
        return "[ERROR:EXEC]";
    }

	char buffer[FTP::LINE_SIZE];
	string result = "";
	while (!feof(pipe)){
		if (fgets(buffer, FTP::LINE_SIZE, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return result;
}