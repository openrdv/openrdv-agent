#include <AttestManager.h>
#include <iostream>

using namespace openrdv;

AttestManager::AttestManager(const boost::filesystem::path &Directory) {
  PluginLoader = std::make_unique<AttestPluginLoader>();
  PluginLoader->loadDirectory(Directory);
}

AttestManager::AttestManager() {
  PluginLoader = std::make_unique<AttestPluginLoader>();
}

AttestResultMap AttestManager::runTests() {
  AttestResultMap Result;
  if (PluginLoader != nullptr) {
    auto Providers = PluginLoader->providers();
    for (const auto &Provider : Providers) {
      Result[Provider->name()] = Provider->run();
    }
  }
  return Result;
}

LoadDirectoryResult
AttestManager::searchProviders(const boost::filesystem::path &Directory) {
  return PluginLoader->loadDirectory(Directory);
}
