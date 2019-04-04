#include<vector>
#include<string>

using std::string;
using std::vector;

string &trim(string &s);
vector<string> splitString(const string &str, const string &delim, const int limit = 10);

// breaks up the command 
vector<string> commandTokenizer(string& cmd) {
    cmd = trim(cmd);
    vector<string> Command = splitString(cmd, " ");
    return Command;
}

