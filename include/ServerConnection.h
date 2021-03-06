#ifndef OPENRDV_AGENT_SERVERCONNECTION_H
#define OPENRDV_AGENT_SERVERCONNECTION_H

#include <AttestPlugin.h>
#include <LogStreamDecorator.h>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

namespace openrdv {

/**
 * @brief Communicate with the server via HTTP/HTTPS.
 */
class ServerConnection : LogStreamDecorator<ServerConnection> {
public:
  /**
   * @brief Create connection with the given host and port.
   *
   * @param Host Server's domain name or IP address.
   * @param Port Server's port.
   */
  explicit ServerConnection(const std::string &Host, const std::string &Port);

  /**
   * @brief Cleanup, close connection.
   */
  ~ServerConnection();

  /**
   * @brief Send device information to perform registration.
   *
   * @param UID Device's unique ID.
   * @param UIDType Type of ID, e.g. @c IMEI.
   */
  void sendRegisterDevice(const std::string &UID, const std::string &UIDType);

  /**
   * @brief Send results of the most recent test.
   *
   * @param UID This device's ID.
   * @param Token Access token received from server.
   * @param Result Attest results.
   */
  void sendAttestResults(const std::string &UID, const std::string &Token,
                         const AttestResult &Result);

  /**
   * @brief Get the response for a just-sent request.
   *
   * @return @c http::response<http::dynamic_body> server response.
   */
  boost::property_tree::ptree getResponse();

private:
  net::io_context Ioc;
  tcp::resolver Resolver;
  beast::tcp_stream TcpStream;
  std::string Host;
  std::string Port;
};

} // namespace openrdv

#endif // OPENRDV_AGENT_SERVERCONNECTION_H
