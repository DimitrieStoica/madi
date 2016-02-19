#include "../controller/sockets/server/server.cpp"
#include "../controller/sockets/client/client.cpp"

#include "consoleOutput.cpp"
#include "Helpers/identifyNetworkHardware.cpp"

using namespace std;

class networkNodeIdentification {
  public:

  int identifyServer() {
    cout << "Identification server will start shorlty." << endl;

    identifyNetworkHardware *inh = new identifyNetworkHardware();
    Server *server               = new Server();

    vector <string> resultVector = inh -> searchForNetworkHardware();
    string myName = "alexandru";
    resultVector = resultVector.push_front(myName);

    for (int i=0; i < resultVector.size(); i++) {
      vectorSize = strlen(resultVector[i]);
    };

    server -> CreateServer(2509, resultVector, vectorSize);
    return 0;
  };

  int identifyClient() {
    cout << "Identification client will connect shortly." << endl;
    char* data = client -> getData("127.0.0.1", "2509");
    cout << data << endl;
    return 0;
  };
};
