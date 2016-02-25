#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <stdio.h>

using boost::asio::ip::tcp;
using namespace std;

using boost::asio::ip::tcp;
using namespace std;

class Client {
  public:

  int getData(string ip, int port, vector<char> *buf) {
    try
    {
      boost::asio::io_service io_service;

      // Convert the server name that was specified as a parameter to the application, to a TCP endpoint.
      tcp::resolver resolver(io_service);

      tcp::resolver::query query(ip, port);

      tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

      //connects to the socket
      tcp::socket socket(io_service);

      boost::asio::connect(socket, endpoint_iterator);

      //waits until data is available on the socket
      while (!socket.available());

      int n = socket.available();

      buf -> resize(n);
      std::vector<char> buffer(socket.available());

      boost::asio::read(socket, boost::asio::buffer(buffer));
      memcpy(buf -> data(), buffer.data(), n);

      return n;
    }
    // handle any exceptions that may have been thrown.
    catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
    return 0;
  };
};
