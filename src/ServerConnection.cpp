#include <ServerConnection.h>
#include <boost/property_tree/json_parser.hpp>

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

void ServerConnection::sendAttestResults(const std::string& DeviceID, const AttestResult& Result) {
  boost::property_tree::ptree Pt;
  Pt.put("device_id", DeviceID);
  Pt.add_child("attest", Result);
  std::stringstream JsonStream;
  boost::property_tree::json_parser::write_json(JsonStream, Pt, false);
  info() << JsonStream.str();

  http::request<http::string_body> Request{http::verb::post, "/attests", 11};
  Request.set(http::field::host, Host);
  Request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  Request.set(http::field::content_type, "application/json");
  Request.body() = JsonStream.str();
  Request.prepare_payload();
  http::write(TcpStream, Request);
}

boost::property_tree::ptree ServerConnection::getResponse() {
  beast::flat_buffer Buffer;
  http::response<http::string_body> Response;
  http::read(TcpStream, Buffer, Response);
  boost::property_tree::ptree PropertyTree;
  std::stringstream ResultsStream;
  ResultsStream << Response.body();
  boost::property_tree::json_parser::read_json(ResultsStream, PropertyTree);
  return PropertyTree;
}
