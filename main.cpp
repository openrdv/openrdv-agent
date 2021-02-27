#include <AttestManager.h>
#include <AttestPluginLoader.h>
#include <ServerConnection.h>
#include <iostream>

using namespace openrdv;

std::ostream &operator<<(std::ostream &Out, const AttestResultSingle &Pair) {
  Out << Pair.first << " : " << Pair.second;
  return Out;
}

int main(int argc, char **argv) {
  AttestManager Manager;
  Manager.searchProviders(".");
  AttestResultMap Results = Manager.runTests();
  std::for_each(Results.begin(), Results.end(), [](std::pair<std::string, AttestResult> Result) {
    std::cout << "===> " << Result.first << "\n";
    std::for_each(Result.second.begin(), Result.second.end(), [](AttestResultSingle ResultPair) {
      std::cout << "=> " << ResultPair.first << " : " << ResultPair.second << "\n";
    });
  });

  ServerConnection Connection("localhost", "8080");
  Connection.sendRegisterDevice();
  auto RegisterResults = Connection.getResponse();
  std::cout << RegisterResults << "\n";

  return 0;
}
