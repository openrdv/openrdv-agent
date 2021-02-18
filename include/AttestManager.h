#ifndef ATTESTMANAGER_H
#define ATTESTMANAGER_H

#include "AttestPluginLoader.h"
#include <boost/filesystem.hpp>
#include <string>

namespace openrdv {

using AttestResultMap = std::unordered_map<std::string, AttestResult>;

class AttestManager {
private:
  std::unique_ptr<AttestPluginLoader> PluginLoader;

public:
  explicit AttestManager() = default;
  AttestManager(const boost::filesystem::path &Directory);

  AttestResultMap runTests();
};

} // namespace openrdv

#endif // ATTESTMANAGER_H