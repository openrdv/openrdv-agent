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
  /**
   * Initialize manager with the specified directory.
   *
   * Creates @c AttestPluginLoader and tries to load plugins
   * from the specified directory.
   * @param Directory to load plugins from.
   */
  AttestManager(const boost::filesystem::path &Directory);

  /**
   * Run all tests.
   *
   * @return @c AttestResultMap results for all providers.
   */
  AttestResultMap runTests();
};

} // namespace openrdv

#endif // ATTESTMANAGER_H