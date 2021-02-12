#include <AttestPluginLoader.h>

#include <boost/dll.hpp>
#include <iostream>
#include <utility>

using boost::shared_ptr;

using namespace openrdv;

static bool isLibraryExtension(boost::filesystem::path ex) {
  if (ex == ".so" || ex == ".dll") {
    return true;
  }
  return false;
}

std::vector<shared_ptr<AttestPlugin>> AttestPluginLoader::providers() {
  return Providers;
}

shared_ptr<AttestPlugin>
AttestPluginLoader::loadFile(const boost::filesystem::path &path) {
  shared_ptr<AttestPlugin> plugin;
  plugin = boost::dll::import<AttestPlugin>(
      path, "plugin", boost::dll::load_mode::append_decorations);
  return plugin;
}

int AttestPluginLoader::loadDirectory(const std::string &path) {
  using namespace boost::filesystem;
  boost::filesystem::path dir(path);
  int count = -1;
  try {
    if (exists(dir) && is_directory(dir)) {
      count = 0;
      for (auto it = directory_iterator(dir); it != directory_iterator();
           it++) {
        if (isLibraryExtension(it->path().extension())) {
          auto plugin = loadFile(it->path());
          if (initializePlugin(plugin))
            count++;
        }
      }
    }
  } catch (const std::exception &e) {
    std::cout << e.what() << "\n";
  }

  return count;
}

bool AttestPluginLoader::initializePlugin(shared_ptr<AttestPlugin> plugin) {
  if (plugin != nullptr) {
    auto status = plugin->initialize();
    if (status == AttestStatus::InitializeSuccess) {
      Providers.push_back(plugin);
      std::cout << "Initialized plugin: " << plugin->name() << " ["
                << plugin->description() << "]"
                << "\n";
      return true;
    } else {
      std::cout << "Failed to initialize plugin: " << plugin->name() << "\n";
    }
  }
  return false;
}
