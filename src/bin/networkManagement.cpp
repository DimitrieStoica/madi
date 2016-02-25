#include <iostream>
#include <vector>
#include <cstdlib>
#include "helpers/createWANfile.cpp"
#include "helpers/identifyNetworkHardware.cpp"
#include <unistd.h>

class networkManagement {

  public: 

  int setUpWAN(string myName) {

    consoleOutput *co            = new consoleOutput();
    createWANfile *cwf           = new createWANfile();
    identifyNetworkHardware *inh = new identifyNetworkHardware();

    vector <string> resultVector = inh -> searchForNetworkHardware();
    string str;

    for (int i=0; i < resultVector.size(); i++) {

      str = co -> getOutputFromConsole("iw " + resultVector[i] + " link");

      if (str.find("Not connected.") != string::npos) {
        cout << resultVector[i] + " is trying to set up a WAN connection" << endl;

        cwf -> writeToFile(resultVector[i], "robotino");

        co -> getOutputFromConsole("chmod 600 " + myName);
        co -> getOutputFromConsole("sudo cp " + myName + " /etc/NetworkManager/system-connections/");
        co -> getOutputFromConsole("sudo rm " + myName);
        co -> getOutputFromConsole("sudo /etc/init.d/networking restart");
        usleep(1000000);
        str = co -> getOutputFromConsole("sudo nmcli con up id " + myName + " iface " + resultVector[i]);
        if ( str.find("Error") == string::npos) {
          cout << "Setting up the connection was succesful." << endl;
          return 0;
        };
      };
    };
    cout << str << endl;
    return 1;
  };

  int connectToWAN(string myNetworkName) {

    consoleOutput *co            = new consoleOutput();
    createWANfile *cwf           = new createWANfile();
    identifyNetworkHardware *inh = new identifyNetworkHardware();

    vector <string> resultVector = inh -> searchForNetworkHardware();
    string str;

    for (int i=0; i < resultVector.size(); i++) { 
      str = co -> getOutputFromConsole("iw " + resultVector[i] + " link");
      if (str.find("Not connected.") != string::npos) {
        cout << resultVector[i] + " is trying to connect to " + myNetworkName << endl;
        str = co -> getOutputFromConsole("sudo nmcli d wifi connect " + myNetworkName);
        if ( str.find("Error") == string::npos) {
          cout << "Setting up the connection was succesful." << endl;
          return 0;
        };
      };
    };
    cout << str << endl;
    return 1;
  };
};
