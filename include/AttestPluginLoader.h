#ifndef OPENRDV_AGENT_ATTESTPLUGINLOADER_H
#define OPENRDV_AGENT_ATTESTPLUGINLOADER_H

#include <AttestPlugin.h>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <string>
#include <vector>

namespace openrdv {

using boost::shared_ptr;

class AttestPluginLoader {
private:
  std::vector<shared_ptr<AttestPlugin>> Providers;

public:
  std::string Location;

  explicit AttestPluginLoader(std::string location);
  int load();
  shared_ptr<AttestPlugin> load(const std::string &path);
  std::vector<shared_ptr<AttestPlugin>> providers();
};

} // namespace openrdv

#endif // OPENRDV_AGENT_ATTESTPLUGINLOADER_H
