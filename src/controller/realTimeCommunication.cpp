#include "sockets/server/server.cpp"
#include "sockets/client/client.cpp"

using namespace std;

class realTimeCommunication {
  public:

  int startServer() {
    cout << "Server will start shortly." << endl;
    Server *server = new Server();

    char data[128];
    strcpy(data, "Hello from server");
    server -> CreateServer(4658, data, strlen(data));

    //char data[128];
    //int nr = 1231;
    //server -> CreateServer(4658, (char*)&nr, sizeof(int));
    return 0;
  };

  int startClient() {
    cout << "Client will connect shortly." << endl;
    Client *client = new Client();
    char* data = client -> getData("127.0.0.1", "4658");
    cout << data << endl;
    return 0;
  };
};
