#include <iostream>
#include "bin/networkManagement.cpp"
#include "bin/networkScanManagement.cpp"

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

  cout << "....................." << endl;
  cout << "Starting identification process" << endl;

  networkScanManagement *nsm = new networkScanManagement();
  nsm -> updateNetworkData(2509);

  return 0;
};
