#include "sockets/server/server.cpp"
#include "sockets/client/client.cpp"

using namespace std;

class realTimeCommunication {
  public:

  int startServer() {
    cout << "Server will start shortly." << endl;
    Server *server = new Server();
    server -> CreateServer(4658);
    return 0;
  };

  int startClient() {
    cout << "Client will connect shortly." << endl;
    Client *client = new Client();
    client -> getData("127.0.0.1", "4658");
    return 0;
  };
};
