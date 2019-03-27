#include <iostream>
using namespace std;

#include "./../server/server.hpp"
#include "./TESTS_SERVER.cpp"

int main() {
    cout << "HELLO WORLD\n";
    TESTS_SERVER::TEST_server_is_initialised_properly();
}