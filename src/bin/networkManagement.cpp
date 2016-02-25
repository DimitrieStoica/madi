#include <iostream>
#include <vector>
#include <cstdlib>
#include "helpers/createWANfile.cpp"
#include "helpers/identifyNetworkHardware.cpp"

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
        str = co -> getOutputFromConsole("nmcli con up id " + myName + " iface " + resultVector[i]);
        if ( str.find("Error") == string::npos) {
          cout << "Setting up the connection was succesful." << endl;
          return 0;
        };
      };
    };
    cout << str << endl;
    return 1;
  };

  int connectToWAN(string myName) {

    consoleOutput *co            = new consoleOutput();
    createWANfile *cwf           = new createWANfile();
    identifyNetworkHardware *inh = new identifyNetworkHardware();

    vector <string> resultVector = inh -> searchForNetworkHardware();
    string str;

    for (int i=0; i < resultVector.size(); i++) { 
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
};
