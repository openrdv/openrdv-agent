#include <AttestProviderLoader.h>

#include <utility>

std::vector<AttestProvider> AttestProviderLoader::providers() {
  return std::vector<AttestProvider>();
}

int AttestProviderLoader::load() {

  return 0;
}

AttestProviderLoader::AttestProviderLoader(std::string location)
    : Location(std::move(location)) {

}
