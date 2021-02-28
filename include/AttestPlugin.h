#ifndef OPENRDV_AGENT_ATTESTPLUGIN_H
#define OPENRDV_AGENT_ATTESTPLUGIN_H

#include <boost/config.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <unordered_map>

namespace openrdv {

using AttestResult = boost::property_tree::ptree;

enum class AttestStatus {
  InitializeSuccess,
  InitializeErrorUnknown,
  InitializeErrorUnsafe,
  InitializeErrorInternal,
  CleanupSuccess,
  CleanupErrorUnknown
};

/**
 * @brief Default symbol name for plugin export/import.
 */
const std::string PluginSymbolName = "Plugin";

/**
 * @brief Attestation plugin interface.
 *
 * Third-party plugins should inherit this class.
 */
class BOOST_SYMBOL_VISIBLE AttestPlugin {
public:
  /**
   * @brief Allocate memory or perform initial checks.
   *
   * @return @c AttestStatus initialization result.
   */
  virtual AttestStatus initialize() = 0;

  /**
   * @brief Performs corresponding checks.
   *
   * @return @c AttestResult test result.
   */
  virtual AttestResult run() = 0;

  /**
   * @brief Free memory and do other cleaning operations.
   *
   * @return @c AttestStatus cleanup result.
   */
  virtual AttestStatus cleanup() = 0;

  /**
   * @brief Plugin name getter.
   *
   * @return @c std::string name of the plugin.
   */
  virtual std::string name() = 0;

  /**
   * @brief Plugin description getter.
   *
   * @return @c std::string short description of the plugin.
   */
  virtual std::string description() = 0;
};

} // namespace openrdv

#endif // OPENRDV_AGENT_ATTESTPLUGIN_H