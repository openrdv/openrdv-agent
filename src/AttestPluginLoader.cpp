#include <AttestPluginLoader.h>

#include <boost/dll.hpp>
#include <utility>

using boost::shared_ptr;

namespace openrdv {

std::vector<shared_ptr<AttestPlugin>> AttestPluginLoader::providers() {
  return Providers;
}

shared_ptr<AttestPlugin> AttestPluginLoader::load(const std::string &path) {
  boost::dll::fs::path lib_path(path);
  shared_ptr<AttestPlugin> plugin;
  plugin = boost::dll::import<AttestPlugin>(
      lib_path, "plugin", boost::dll::load_mode::append_decorations);
  return plugin;
}

int AttestPluginLoader::load() { return 0; }

AttestPluginLoader::AttestPluginLoader(std::string location)
    : Location(std::move(location)) {}

} // namespace openrdv