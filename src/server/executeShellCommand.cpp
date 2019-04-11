#include "./server.hpp"

/**Execute the given command in shell
 *
 * @usage
 * opens a pipe and extracts the output from the shell command
 *
 * @returns
 * executed command's output
*/
string executeShellCommand(const string& cmd) {
	FILE* pipe = popen(cmd.c_str(), "r");
	if (!pipe) {
		printError("[ERROR:EXEC]");
		return "[ERROR:EXEC]";
	}

	char buffer[FTP::SOCKET_READ_BUFFER_SIZE];
	string result = "";
	while (!feof(pipe)) {
		if (fgets(buffer, FTP::LINE_SIZE, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return result;
}