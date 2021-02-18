#include <AttestManager.h>
#include <AttestPluginLoader.h>
#include <iostream>

using namespace openrdv;

std::ostream &operator<<(std::ostream &Out, const AttestResultSingle &Pair) {
  Out << Pair.first << " : " << Pair.second;
  return Out;
}

int main(int argc, char **argv) {
  openrdv::AttestManager Manager(".");
  auto TestResults = Manager.runTests();
  for (const auto &TestResult : TestResults) {
    std::cout << "-- " << TestResult.first << "\n";
    std::for_each(
        TestResult.second.begin(), TestResult.second.end(),
        [](const AttestResultSingle &Pair) { std::cout << Pair << "\n"; });
  }
  return 0;
}
