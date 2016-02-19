#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <stdio.h>

using boost::asio::ip::tcp;
using namespace std;

class Client {
  public:

  char* getData(string ip, string port) {
    try
    {
      // the user should specify the server - the 2nd argument
      boost::asio::io_service io_service;

      // Convert the server name that was specified as a parameter to the application, to a TCP endpoint.
      tcp::resolver resolver(io_service);

      tcp::resolver::query query(ip, port);

      // The list of endpoints is returned using an iterator of type ip::tcp::resolver::iterator.
      // A default constructed ip::tcp::resolver::iterator object can be used as an end iterator.
      tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

      // Now we create and connect the socket.
      tcp::socket socket(io_service);
      boost::asio::connect(socket, endpoint_iterator);

      // The connection is open.
      // We use a boost::array to hold the received data.
      boost::system::error_code error;

      // The boost::asio::buffer() function automatically determines
      // the size of the array to help prevent buffer overruns.
      std::vector<char> buf(socket.available());
      boost::asio::read(socket, boost::asio::buffer(buf));

      return buf.data();
    }
    // handle any exceptions that may have been thrown.
    catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
    return 0;
  };
};
