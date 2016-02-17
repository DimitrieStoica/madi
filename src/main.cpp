#include <iostream>
#include "Controller/realTimeCommunication.cpp"
#include "bin/networkManagement.cpp"

using namespace std;

int main() {
  //needs to set up WiFi first

  cout << "System started" << endl;
  //dynamic object creation to improve performance and memory usage

  networkManagement *nm = new networkManagement();
  nm -> setUpWAN("robotino");
  nm -> connectToWAN("robotino");

  cout << "....................." << endl;
  cout << "Starting communication" << endl;

  realTimeCommunication *rtc = new realTimeCommunication();  
  rtc -> startServer();
  rtc -> startClient();

  cout << "....................." << endl;
  cout << "Reading from database" << endl;

  myDatabase *mdb = new myDatabase();
  mdb -> readAllFromDatabase("./test");

  return 0;
};
