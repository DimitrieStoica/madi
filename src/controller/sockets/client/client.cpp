#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "../../database/database.cpp"
#include <chrono> 
#include <stdio.h>

using boost::asio::ip::tcp;
using namespace std;

class Client {
  public:

  int getData(string myDatabaseName, string ip, string port) {
    myDatabase *mdb = new myDatabase();

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

    // The connection is open. All we need to do now is read the response from the daytime service.
    for (;;)
    {
      // We use a boost::array to hold the received data.
      boost::array<char, 128> buf;
      boost::system::error_code error;

      // The boost::asio::buffer() function automatically determines
      // the size of the array to help prevent buffer overruns.
      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      cout << "Writing to database" << endl;

      std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
      auto duration = now.time_since_epoch();
      mdb -> writeToDatabase(myDatabaseName, to_string(duration.count()), buf.data());

      //if connection closed by server return error
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.
    }
  }
  // handle any exceptions that may have been thrown.
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
};
};

