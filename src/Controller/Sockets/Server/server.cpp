#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <ctime>

using boost::asio::ip::tcp;

class Server {
  public:

  int CreateServer(int port) {
    try
    {
      //define io_service
      boost::asio::io_service io_service;

      //acceptor object needs to be created to listen for new connections
      tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

      for (;;)
      {
        //creates a socket
        tcp::socket socket(io_service);

        //wait and listen
        acceptor.accept(socket);

        //prepare message to send back to client

        boost::system::error_code ignored_error;

        //responding to client
        for ( int x = 0; x < 20; x++ ) {

          std::string message = "Hello from server " + std::to_string(x) + "\n";
          boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
          usleep(1000000);
        }
      }
    }
    catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }

    return 0;
  };
};
