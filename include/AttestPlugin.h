#ifndef ATTESTPLUGIN_H
#define ATTESTPLUGIN_H

#include <boost/config.hpp>
#include <string>
#include <unordered_map>

namespace openrdv {

typedef std::unordered_map<std::string, std::string> AttestResult;

enum class AttestStatus {
  InitializeSuccess,
  InitializeErrorUnknown,
  InitializeErrorUnsafe,
  InitializeErrorInternal,
  CleanupSuccess,
  CleanupErrorUnknown
};

class BOOST_SYMBOL_VISIBLE AttestPlugin {
public:
  virtual AttestStatus initialize() = 0;
  virtual AttestResult run() = 0;
  virtual AttestStatus cleanup() = 0;
  virtual std::string name() = 0;
  virtual std::string description() = 0;
};

} // namespace openrdv

#endif // ATTESTPLUGIN_H