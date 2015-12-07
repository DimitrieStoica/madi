#include "Sockets/Server/server.cpp"

using namespace std;

class realTimeCommunication {
  public:

  int startServer () {
    cout << "Server will start shortly." << endl;
    Server *server = new Server();
    server -> CreateServer(4658);
    return 0;
  };

  int sendData () {
    cout << "Client will connect shortly." << endl;

    return 0;
  };
};
