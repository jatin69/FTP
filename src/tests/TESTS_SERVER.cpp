#include "./../server/server.hpp"
#include <iostream>

namespace TESTS_SERVER {
  void TEST_server_is_initialised_properly() {
    using namespace std;

    cout << "Default constructor \n";
    Server ftpServer1;
    ftpServer1.logServerConfiguration();

    cout << "Single argument \n";
    Server ftpServer2(4000);
    ftpServer2.logServerConfiguration();

    cout << "Two arguments\n";
    Server ftpServer3(6000, 6001);
    ftpServer3.logServerConfiguration();

    cout << "All Arguements\n";
    Server ftpServer4(6000, 6001, true, 5, "$$$");
    ftpServer4.logServerConfiguration();
  }
} // namespace TESTS_SERVER
