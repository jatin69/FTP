#include <iostream>
#include<algorithm>
#include<vector>
#include<string>

using std::string;
using std::cout;
using std::vector;
const string PATH_SEPARATOR("/");

string &ltrim(string &s);
string &rtrim(string &s);
string &trim(string &s);
vector<string> splitString(const string &str, const string &delim, const int limit = 10);

// breaks up the command 
vector<string> commandTokenizer(string& cmd) {
    trim(cmd);
    vector<string> Command = splitString(cmd, " ");
    return Command;
}

// breaks up path
vector<string> pathTokenizer(string& path) {
    return splitString(path, PATH_SEPARATOR);
}

// trim from start
std::string &ltrim(std::string &s) {
  s.erase(s.begin(),
          std::find_if(s.begin(), s.end(),
                       std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end
std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       std::not1(std::ptr_fun<int, int>(std::isspace)))
              .base(),
          s.end());
  return s;
}

// trim from both ends
std::string &trim(std::string &s) { return ltrim(rtrim(s)); }

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

