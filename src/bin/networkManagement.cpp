#include <iostream>
#include <vector>
#include <cstdlib>
#include "Helpers/createWANfile.cpp"

using namespace std;

class networkManagement{

  public: 

  vector <string> searchForNetworkHardware() {
    consoleOutput *co  = new consoleOutput();
    createWANfile *cwf = new createWANfile();

    string word;
    vector <string> resultVector;

    string str = co -> getOutputFromConsole("iw dev | grep \"Interface\" | awk '{print $2}'");
    istringstream stm(str);

    while(stm >> word) {
      resultVector.push_back(word);
    };

    return resultVector;
  };

  int setUpWAN(string myName) {
    consoleOutput *co  = new consoleOutput();
    createWANfile *cwf = new createWANfile();

    vector <string> resultVector = searchForNetworkHardware();
    string str;

    for (int i=0; i < resultVector.size(); i++) {
    cout << "..........." << endl;
    cout << resultVector[i] << endl;
    str = co -> getOutputFromConsole("iw " + resultVector[i] + " link");
    if (str.find("Not connected.") != string::npos) {
      cout << resultVector[i] + " is free and can be used for setting up a WAN connection" << endl;

      cwf -> writeToFile(resultVector[i], "robotino");

      co -> getOutputFromConsole("chmod 600 " + myName);
      co -> getOutputFromConsole("sudo cp " + myName + " /etc/NetworkManager/system-connections/");
      co -> getOutputFromConsole("sudo rm " + myName);
      co -> getOutputFromConsole("sudo /etc/init.d/networking restart");
      co -> getOutputFromConsole("nmcli con up id " + myName + " iface " + resultVector[i]);
      
    } else {
      cout << "Hardware is busy for a WAN connection" << endl;
      return 1;
    };
  };

    return 0;
  };

  int connectToWAN(string myName) {
    consoleOutput *co  = new consoleOutput();
    createWANfile *cwf = new createWANfile();

    vector <string> resultVector = searchForNetworkHardware();
    string str;

    for (int i=0; i < resultVector.size(); i++) { 
      cout << "..........." << endl;
      cout << resultVector[i] << endl;
      str = co -> getOutputFromConsole("iw " + resultVector[i] + " link");
      if (str.find("Not connected.") != string::npos) {
        cout << resultVector[i] + " is free and can be used for setting up a WAN connection" << endl;
        co -> getOutputFromConsole("nmcli d wifi connect " + myName);
      } else {
        cout << "Hardware is busy for a WAN connection" << endl;
      };
    };
    return 0;
  };

  int scanNetworkWAN(string myName) {
    consoleOutput *co  = new consoleOutput();

    vector <string> resultVector = searchForNetworkHardware();
    string str;

    for (int i=0; i < resultVector.size(); i++) {
      str = co -> getOutputFromConsole("iwconfig | grep " + resultVector[i]);
      if (str.find(myName) != string::npos) {
        str = co -> getOutputFromConsole("sudo arp-scan --interface=" + resultVector[i] + " --localnet | awk 'FNR > 2 {print $1 \" \" $2}' | head -n -3");
        cout << str << endl;
      } else {
        cout << "Not connected to WAN" << endl;
      };
    };
    return 0;
  };
};
