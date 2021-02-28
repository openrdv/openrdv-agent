#include <AttestManager.h>
#include <AttestPluginLoader.h>
#include <ServerConnection.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <thread>

using namespace openrdv;

int main(int argc, char **argv) {
  /*
   * Init AttestManager and find all providers
   */
  AttestManager Manager;
  Manager.searchProviders(".");
  bool ShouldRun = true;

  /*
   * Create connection to server and register device
   */
  ServerConnection Connection("localhost", "8080");
  Connection.sendRegisterDevice();
  auto RegisterResults = Connection.getResponse();
  std::string DeviceID =
      RegisterResults.get_optional<std::string>("data.ID").value_or("");

  /*
   * Run tests
   */
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
  while (ShouldRun) {
    AttestResultMap Results = Manager.runTests();
    Connection.sendAttestResults(DeviceID, Results);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  }
#pragma clang diagnostic pop
}
