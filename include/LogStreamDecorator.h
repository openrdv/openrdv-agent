#ifndef OPENRDV_AGENT_LOGSTREAMDECORATOR_H
#define OPENRDV_AGENT_LOGSTREAMDECORATOR_H

#include <iostream>

namespace openrdv {

/**
 * @brief Utilize CRTP to beautify log messages.
 *
 * @tparam T Derived class which would use @c err, @c warn and @c info.
 */
template <typename T> class LogStreamDecorator {
protected:
  /**
   * @brief Adds @c [ERROR] to the @c std::cerr and returns it.
   *
   * @return @c std::cerr.
   */
  std::ostream &err() {
    return std::cerr << "[ERROR] <" << typeid(T).name() << ">: ";
  }

  /**
   * @brief Adds @c [WARN] to the @c std::cout and returns it.
   *
   * @return @c std::cout.
   */
  std::ostream &warn() {
    return std::cout << "[WARN] <" << typeid(T).name() << ">: ";
  }

  /**
   * @brief Adds @c [INFO] to the @c std::cout and returns it.
   *
   * @return @c std::cout.
   */
  std::ostream &info() {
    return std::cout << "[INFO] <" << typeid(T).name() << ">: ";
  }
};

} // namespace openrdv

#endif // OPENRDV_AGENT_LOGSTREAMDECORATOR_H
