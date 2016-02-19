#include <iostream>
#include "controller/realTimeCommunication.cpp"
#include "bin/networkManagement.cpp"

using namespace std;

int main() {
  //needs to set up WiFi first

  cout << "System started" << endl;
  //dynamic object creation to improve performance and memory usage
 
  cout << "....................." << endl;
  cout << "Setting up network" << endl;

  networkManagement *nm = new networkManagement();
  nm -> setUpWAN("robotino");
  nm -> connectToWAN("robotino");
  nm -> scanNetworkWAN("robotino");

  cout << "....................." << endl;
  cout << "Starting communication" << endl;

  realTimeCommunication *rtc = new realTimeCommunication();  
  rtc -> startServer();
  rtc -> startClient();

  return 0;
};
