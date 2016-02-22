#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <stdio.h>

using boost::asio::ip::tcp;
using namespace std;

class Client {
  public:

  vector<char> getData(string ip, string port) {
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

      std::vector<char> buf(socket.available());

      boost::asio::read(socket, boost::asio::buffer(buf));

      return buf;
    }
    // handle any exceptions that may have been thrown.
    catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
    std::vector<char> buf;
    return buf;
  };
};
