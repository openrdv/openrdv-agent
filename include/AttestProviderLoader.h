#ifndef OPENRDV_AGENT_ATTESTPROVIDERLOADER_H
#define OPENRDV_AGENT_ATTESTPROVIDERLOADER_H

#include <AttestProvider.h>
#include <string>
#include <vector>

class AttestProviderLoader {
private:
  std::vector<AttestProvider> Providers;

public:
  std::string Location;

  explicit AttestProviderLoader(std::string  location);
  int load();
  std::vector<AttestProvider> providers();
};

#endif // OPENRDV_AGENT_ATTESTPROVIDERLOADER_H
