#include <iostream>
#include "Controller/realTimeCommunication.cpp"

using namespace std;

int main() {
  //needs to set up WiFi first

  cout << "System started" << endl;
  //dynamic object creation to improve performance and memory usage
  realTimeCommunication *rtc = new realTimeCommunication();  
  rtc -> startServer();
  rtc -> startClient();
  return 0;
};
