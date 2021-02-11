#ifndef OPENRDV_AGENT_ATTESTPLUGINLOADER_H
#define OPENRDV_AGENT_ATTESTPLUGINLOADER_H

#include <AttestPlugin.h>
#include <boost/filesystem/path.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <string>
#include <vector>

namespace openrdv {

using boost::shared_ptr;

class AttestPluginLoader {
private:
  std::vector<shared_ptr<AttestPlugin>> Providers;

public:
  explicit AttestPluginLoader() = default;
  int loadDirectory(const std::string &path);
  shared_ptr<AttestPlugin> loadFile(const boost::filesystem::path& path);

  std::vector<shared_ptr<AttestPlugin>> providers();

private:
  bool initializePlugin(shared_ptr<AttestPlugin> plugin);
};

} // namespace openrdv

#endif // OPENRDV_AGENT_ATTESTPLUGINLOADER_H
