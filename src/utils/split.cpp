#include<vector>
#include<string>

using std::string;
using std::vector;

/**Split string
 * 
 * Splits the string based on the given delimeter
 * 
*/
vector<string> splitString(const string &str, const string &delim, const int limit) {
  vector<string> tokens;
  size_t prev = 0, pos = 0;
  int found = 0;
  do {
    pos = str.find(delim, prev);
    if (pos == string::npos) pos = str.length();
    string token = str.substr(prev, pos-prev);
    if (!token.empty()) {
      tokens.push_back(token);
      ++found;
      if (found == limit) break;
    }
    prev = pos + delim.length();
  } while (pos < str.length() && prev < str.length());
  return tokens;
}

