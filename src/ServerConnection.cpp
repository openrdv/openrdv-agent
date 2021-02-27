#include <ServerConnection.h>

using namespace openrdv;

ServerConnection::ServerConnection(const std::string &Host,
                                   const std::string &Port)
    : Resolver(Ioc), TcpStream(Ioc), Host(Host), Port(Port) {
  auto const ResolveResults = Resolver.resolve(Host, Port);
  TcpStream.connect(ResolveResults);
}

ServerConnection::~ServerConnection() { TcpStream.close(); }

void ServerConnection::sendRegisterDevice() {
  // TODO: actually send device info
  http::request<http::string_body> Request{http::verb::post, "/devices", 11};
  Request.set(http::field::host, Host);
  Request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  Request.set(http::field::content_type, "application/json");
  Request.body() = "{}";
  Request.prepare_payload();
  http::write(TcpStream, Request);
}

void ServerConnection::sendAttestResults() {
  // TODO: actually send attest data
  http::request<http::string_body> Request{http::verb::post, "{}", 11};
  Request.set(http::field::host, Host);
  Request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  http::write(TcpStream, Request);
}

http::response<http::dynamic_body> ServerConnection::getResponse() {
  beast::flat_buffer Buffer;
  http::response<http::dynamic_body> Response;
  http::read(TcpStream, Buffer, Response);
  return Response;
}
