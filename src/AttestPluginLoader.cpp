#include <AttestPluginLoader.h>
#include <boost/dll.hpp>
#include <iostream>

using boost::shared_ptr;

using namespace openrdv;

namespace {
bool isLibraryExtension(boost::filesystem::path Ex) {
  if (Ex == ".so" || Ex == ".dll") {
    return true;
  }
  return false;
}
} // namespace

std::vector<shared_ptr<AttestPlugin>> AttestPluginLoader::providers() {
  return Providers;
}

shared_ptr<AttestPlugin>
AttestPluginLoader::loadFile(const boost::filesystem::path &Path) {
  try {
    auto Plugin = boost::dll::import<AttestPlugin>(
        Path, PluginSymbolName, boost::dll::load_mode::append_decorations);
    return Plugin;
  } catch (const std::exception &E) {
    err() << "Failed to load library at " << Path << "\n";
    err() << E.what();
    return nullptr;
  }
}

LoadDirectoryResult
AttestPluginLoader::loadDirectory(const boost::filesystem::path &Path) {
  using namespace boost::filesystem;
  boost::filesystem::path Dir(Path);
  LoadDirectoryResult Count = -1;

  if (exists(Dir) && is_directory(Dir)) {
    Count = 0;
    for (auto It = directory_iterator(Dir); It != directory_iterator(); It++) {
      if (isLibraryExtension(It->path().extension())) {
        auto Plugin = loadFile(It->path());
        if (Plugin != nullptr && initializePlugin(Plugin))
          Count++;
      }
    }
  }

  return Count;
}

bool AttestPluginLoader::initializePlugin(shared_ptr<AttestPlugin> Plugin) {
  if (Plugin != nullptr) {
    auto Status = Plugin->initialize();
    if (Status == AttestStatus::InitializeSuccess) {
      Providers.push_back(Plugin);
      info() << "Initialized plugin: " << Plugin->name() << ": "
             << Plugin->description() << "\n";
      return true;
    }
    err() << "Failed to initialize plugin: " << Plugin->name() << "\n";
  }
  return false;
}
