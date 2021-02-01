#ifndef OPENRDV_AGENT_ATTESTPROVIDER_H
#define OPENRDV_AGENT_ATTESTPROVIDER_H

#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> AttestResult;

enum AttestStatus {
  InitializeSuccess,
  InitializeErrorUnknown,
  InitializeErrorUnsafe,
  InitializeErrorInternal,
  CleanupSuccess,
  CleanupErrorUnknown
};

class AttestProvider {
public:
  virtual AttestStatus initialize() = 0;
  virtual AttestResult run() = 0;
  virtual AttestStatus cleanup() = 0;
  virtual std::string name() = 0;
  virtual std::string description() = 0;
};

#endif // OPENRDV_AGENT_ATTESTPROVIDER_H
