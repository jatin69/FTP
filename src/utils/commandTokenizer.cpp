#include<vector>
#include<string>

using std::string;
using std::vector;

// prototypes for functions used below
string &trim(string &s);
vector<string> splitString(const string &str, const string &delim, const int limit = 10);

/**Command Tokenizer
 * 
 * @Usage
 * When user enters a command, it is first santized and then
 * passed into the command tokenizer 
 * 
 * @Working
 * Trims spaces from front and back and,
 * splits up the command on `space` and returns vector of tokens
 * 
*/
vector<string> commandTokenizer(string& cmd) {
    cmd = trim(cmd);
    vector<string> Command = splitString(cmd, " ");
    return Command;
}

