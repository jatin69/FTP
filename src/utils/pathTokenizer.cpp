#include<vector>
#include<string>

using std::vector;
using std::string;

vector<string> splitString(const string &str, const string &delim, const int limit = 10);

const string PATH_SEPARATOR("/");

// breaks up path
vector<string> pathTokenizer(string& path) {
    return splitString(path, PATH_SEPARATOR);
}
