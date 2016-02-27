#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <ctime>

using boost::asio::ip::tcp;
using namespace std;

class Server {
  public:

  string CreateServer(int port, char* data, int dataSize) {

    string client_ip;

    try
    {
      boost::asio::io_service io_service;

      tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));
        //creates a socket
        tcp::socket socket(io_service);

        //wait and listen
        acceptor.accept(socket);

        boost::system::error_code ignored_error;

        //find ip of the connected client
        client_ip = socket.remote_endpoint().address().to_string();

        //responds to client
        boost::asio::write(socket, boost::asio::buffer(data, dataSize), ignored_error);
    }
    catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
    return client_ip;
  };
};
