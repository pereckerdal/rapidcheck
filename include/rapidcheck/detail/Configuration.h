#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

#include "rapidcheck/detail/TestParams.h"

namespace rc {
namespace detail {

/// Global suite configuration.
struct Configuration {
  /// The default test parameters.
  TestParams testParams;

  /// Enable/disable verbose printing during testing.
  bool verboseProgress = false;

  /// Enable/disable verbose printing during shrinking.
  bool verboseShrinking = false;
};

std::ostream &operator<<(std::ostream &os, const Configuration &config);
bool operator==(const Configuration &c1, const Configuration &c2);
bool operator!=(const Configuration &c1, const Configuration &c2);

/// Thrown to indicate something went wrong when loading configuration.
class ConfigurationException : public std::exception {
public:
  ConfigurationException(std::string msg);
  const char *what() const noexcept override;

private:
  std::string m_msg;
};

/// Reads a `Configuration` from the given string.
///
/// @param defaults  Defaults for keys that are not specified.
Configuration configFromString(const std::string &str,
                               const Configuration &defaults = Configuration());

/// Returns a configuration string from a `Configuration`.
std::string configToString(const Configuration &config);

/// Returns a configuration string from a `Configuration` that only contains the
/// keys that differ from the default configuration.
std::string configToMinimalString(const Configuration &config);

/// Returns the default configuration.
const Configuration &defaultConfiguration();

namespace param {

/// ImplicitParam containing the current configuration.
struct CurrentConfiguration {
  using ValueType = Configuration;
  static Configuration defaultValue() { return defaultConfiguration(); }
};

} // namespace param

} // namespace detail
} // namespace rc
