#ifndef ATTESTPLUGINLOADER_H
#define ATTESTPLUGINLOADER_H

#include <AttestPlugin.h>
#include <boost/filesystem/path.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <string>
#include <vector>

namespace openrdv {

using boost::shared_ptr;

/// Attestation plugin loader.
///
/// Loads plugins from the specified directory or file.
class AttestPluginLoader {
private:
  std::vector<shared_ptr<AttestPlugin>> Providers;

public:
  explicit AttestPluginLoader() = default;
  int loadDirectory(const std::string &Path);

  /// Load library as plugin.
  ///
  /// Try to load .so or .dll file at the specified location as plugin.
  /// \param Path to the library file.
  /// \return \c std::shared_ptr to the plugin instance.
  shared_ptr<AttestPlugin> loadFile(const boost::filesystem::path& Path);

  /// Getter for Providers.
  /// \return Shared pointer to the providers vector.
  std::vector<shared_ptr<AttestPlugin>> providers();

private:
  bool initializePlugin(shared_ptr<AttestPlugin> Plugin);
};

} // namespace openrdv

#endif // ATTESTPLUGINLOADER_H
