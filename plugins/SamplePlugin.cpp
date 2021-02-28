#include <AttestPlugin.h>

using namespace openrdv;

class SamplePlugin : public AttestPlugin {
public:
  AttestStatus initialize() override { return AttestStatus::InitializeSuccess; }

  AttestResult run() override {
    AttestResult Result;
    Result.put("code", "1");
    Result.put("safe", "true");
    return Result;
  }

  AttestStatus cleanup() override { return AttestStatus::CleanupSuccess; }

  std::string name() override { return "SamplePlugin"; }

  std::string description() override {
    return "This is a sample device verification plugin for OpenRDV.";
  }
};

extern "C" BOOST_SYMBOL_EXPORT SamplePlugin Plugin;
SamplePlugin Plugin;
