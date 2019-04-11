#include <vector>
#include <string>

using std::vector;
using std::string;

// prototypes for functions used below
vector<string> splitString(const string& str, const string& delim, const int limit = 10);
const string PATH_SEPARATOR("/");

/**path tokenizer
 *
 * @usage
 * can be used to break the given path into tokens
 *
 * Currently unused.
 *
*/
vector<string> pathTokenizer(string& path) {
	return splitString(path, PATH_SEPARATOR);
}
