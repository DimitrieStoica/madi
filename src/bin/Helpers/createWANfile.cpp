#include <fstream>
#include "consoleOutput.cpp"

class createWANfile {
  public:

  int writeToFile(string networkHardware, string myName) {
    consoleOutput *co = new consoleOutput();

    ofstream myfile;
    myfile.open ("robotino");
    myfile << "[connection]\n";
    myfile << "id=" + myName + "\n";
    myfile << "uuid=" + co -> getOutputFromConsole("uuidgen");
    myfile << "type=802-11-wireless\n";
    myfile << "autoconnect=false\n";
    myfile << "[802-11-wireless]\n";
    myfile << "ssid=" + myName + "\n";
    myfile << "mode=ap\n";
    myfile << "mac-address= " + co -> getOutputFromConsole("ifconfig " + networkHardware + " | awk '/HWaddr/ {print $5}'");
    myfile << "[ipv6]\n";
    myfile << "method=auto\n";
    myfile << "[ipv4]\n";
    myfile << "method=shared";
    myfile.close();
    return 0;
  };
};
