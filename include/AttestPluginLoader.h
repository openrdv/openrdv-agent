#ifndef ATTESTPLUGINLOADER_H
#define ATTESTPLUGINLOADER_H

#include <AttestPlugin.h>
#include <boost/filesystem/path.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <string>
#include <vector>

namespace openrdv {

using boost::shared_ptr;

/**
 * @brief Attestation plugin loader.
 *
 * Loads plugins from the specified directory or file.
 */
class AttestPluginLoader {
private:
  std::vector<shared_ptr<AttestPlugin>> Providers;

  bool initializePlugin(shared_ptr<AttestPlugin> Plugin);

public:
  explicit AttestPluginLoader() = default;

  /**
   * @brief Load all plugins in the specified directory.
   *
   * Iterates through all files in the directory and tries to load those,
   * which have either .so or .dll name extension.
   * @param Path to a directory.
   * @return @c int number of loaded libraries.
   */
  int loadDirectory(const std::string &Path);

  /**
   * @brief Load library as plugin.
   *
   * Try to load .so or .dll file at the specified location as plugin.
   * @param Path to the library file.
   * @return @c shared_ptr<AttestPlugin> to the plugin instance.
   */
  shared_ptr<AttestPlugin> loadFile(const boost::filesystem::path &Path);

  /**
   * @brief Getter for Providers.
   *
   * @return @c std::vector<shared_ptr<AttestPlugin>> Shared pointer to the
   * providers vector.
   */
  std::vector<shared_ptr<AttestPlugin>> providers();
};

} // namespace openrdv

#endif // ATTESTPLUGINLOADER_H
