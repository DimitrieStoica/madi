#include "../controller/sockets/server/server.cpp"
#include "../controller/sockets/client/client.cpp"

using namespace std;

struct InfoNode {
  char name[64];
};

class networkNodeIdentification {
  public:

  int identifyServer(int port, string myName, string currentWAN) {
    cout << "Identification server will start shorlty." << endl;

    identifyNetworkHardware *inh = new identifyNetworkHardware();
    consoleOutput *co            = new consoleOutput();
    Server *server               = new Server();

    vector <string> resultVector = inh -> searchForNetworkHardware();
    InfoNode infoNodeServer;

    for (int i=0; i < resultVector.size(); i++) {

      string strWAN = co -> getOutputFromConsole("iwconfig " + resultVector[i] + " | awk '/ESSID/ {print $4}'");
      strWAN.erase(std::remove(strWAN.begin(), strWAN.end(), '\n'), strWAN.end());

      if (strWAN.find(currentWAN) != std::string::npos) {
        strcpy( infoNodeServer.name, myName.c_str());
        for (;;) {
          server -> CreateServer(port, (char*)&infoNodeServer, sizeof(InfoNode));
        };
      };
    };

    return 0;
  };

  string identifyClient(string ip, int port) {
    cout << "Identification client will connect shortly." << endl;

    Client *client = new Client();

    InfoNode infoNodeClient;
    vector<char> buffer;

    int n = client -> getData(ip, port, &buffer);
    memcpy(&infoNodeClient, buffer.data(), sizeof(InfoNode));

    return string(infoNodeClient.name);
  };
};
