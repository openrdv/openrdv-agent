#ifndef OPENRDV_AGENT_ATTESTMANAGER_H
#define OPENRDV_AGENT_ATTESTMANAGER_H

#include "AttestPluginLoader.h"
#include <boost/filesystem.hpp>
#include <string>

namespace openrdv {

using AttestResultMap = boost::property_tree::ptree;

/**
 * @brief Manages loading plugins and running tests.
 */
class AttestManager {
private:
  std::unique_ptr<AttestPluginLoader> PluginLoader;

public:
  /**
   * @brief Default constructor.
   */
  explicit AttestManager();

  /**
   * @brief Initialize manager with the specified directory.
   *
   * Creates @c AttestPluginLoader and tries to load plugins
   * from the specified directory.
   * @param Directory to load plugins from.
   */
  AttestManager(const boost::filesystem::path &Directory);

  /**
   * @brief Run all tests.
   *
   * @return @c AttestResultMap results for all providers.
   */
  AttestResultMap runTests();

  /**
   * @brief Scan the given directory for plugins.
   *
   * @param Directory where to look for plugins.
   * @return number of plugins loaded or @c -1 if not directory.
   */
  LoadDirectoryResult searchProviders(const boost::filesystem::path &Directory);
};

} // namespace openrdv

#endif // OPENRDV_AGENT_ATTESTMANAGER_H