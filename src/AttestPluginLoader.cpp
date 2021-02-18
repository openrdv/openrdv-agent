#include <AttestPluginLoader.h>

#include <boost/dll.hpp>
#include <iostream>

using boost::shared_ptr;

using namespace openrdv;

static bool isLibraryExtension(boost::filesystem::path Ex) {
  if (Ex == ".so" || Ex == ".dll") {
    return true;
  }
  return false;
}

std::vector<shared_ptr<AttestPlugin>> AttestPluginLoader::providers() {
  return Providers;
}

shared_ptr<AttestPlugin>
AttestPluginLoader::loadFile(const boost::filesystem::path &Path) {
  shared_ptr<AttestPlugin> Plugin;
  Plugin = boost::dll::import<AttestPlugin>(
      Path, "Plugin", boost::dll::load_mode::append_decorations);
  return Plugin;
}

int AttestPluginLoader::loadDirectory(const boost::filesystem::path &Path) {
  using namespace boost::filesystem;
  boost::filesystem::path Dir(Path);
  int Count = -1;
  try {
    if (exists(Dir) && is_directory(Dir)) {
      Count = 0;
      for (auto It = directory_iterator(Dir); It != directory_iterator();
           It++) {
        if (isLibraryExtension(It->path().extension())) {
          auto Plugin = loadFile(It->path());
          if (initializePlugin(Plugin))
            Count++;
        }
      }
    }
  } catch (const std::exception &E) {
    std::cout << E.what() << "\n";
  }

  return Count;
}

bool AttestPluginLoader::initializePlugin(shared_ptr<AttestPlugin> Plugin) {
  if (Plugin != nullptr) {
    auto Status = Plugin->initialize();
    if (Status == AttestStatus::InitializeSuccess) {
      Providers.push_back(Plugin);
      std::cout << "Initialized plugin: " << Plugin->name() << " ["
                << Plugin->description() << "]\n";
      return true;
    }
    std::cout << "Failed to initialize plugin: " << Plugin->name() << "\n";
  }
  return false;
}
