#include <algorithm>
#include <string>

// trim space from front
std::string& ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
									std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim space from back
std::string& rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
						 std::not1(std::ptr_fun<int, int>(std::isspace)))
				.base(),
			s.end());
	return s;
}

// trim from both ends
std::string& trim(std::string& s) {
	return ltrim(rtrim(s));
}
