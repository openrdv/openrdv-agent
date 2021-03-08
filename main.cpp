#include <AttestManager.h>
#include <ServerConnection.h>
#include <thread>

using namespace openrdv;

int main(int argc, char **argv) {
  /*
   * Init AttestManager and find all providers
   */
  AttestManager Manager;
  Manager.searchProviders(".");

  /*
   * Create connection to server and register device
   */
  ServerConnection Connection("localhost", "8080");
  std::string UID = "pop-os super";
  Connection.sendRegisterDevice(UID, "text");
  auto RegisterResults = Connection.getResponse();
  std::string Token =
      RegisterResults.get_optional<std::string>("token").value_or("");

  /*
   * Run tests
   */
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
  while (true) {
    AttestResultMap Results = Manager.runTests();
    Connection.sendAttestResults(UID, Token, Results);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  }
#pragma clang diagnostic pop
}
