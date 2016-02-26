#include "string.h"
#include <time.h>
#include "./networkNodeIdentification.cpp"

using namespace std;

struct ScanNodeInfo {
  char ip[16];
  char mac[18];
  char name[64];
  bool available;
  clock_t time;
};

class networkScanManagement {

  vector<ScanNodeInfo> currentNetworkInfo;

  public:

  vector<ScanNodeInfo> scanNetworkWAN(string currentWAN) {
    consoleOutput *co            = new consoleOutput();
    identifyNetworkHardware *inh = new identifyNetworkHardware();

    vector <string> resultVector = inh -> searchForNetworkHardware();
    vector <string> nodeIPMACvector;
    vector <ScanNodeInfo> scanNodeInfoVector;
    string word;

    ScanNodeInfo scanNodeInfo;

    for (int i=0; i < resultVector.size(); i++) {
      string str = co -> getOutputFromConsole("iwconfig " + resultVector[i] + " | awk '/Mode/ {print $4}'");

      if (str.find("Master") != std::string::npos) {
        str = co -> getOutputFromConsole("sudo arp-scan --interface=" + resultVector[i] + " --retry 5 --localnet | awk 'FNR > 2 {print $1 \" \" $2}' | head -n -3");

        if (str.size() > 0) {
          istringstream stm(str);

          while(stm >> word) {
            nodeIPMACvector.push_back(word);
          };

          for (int j=0; j < nodeIPMACvector.size() - 1; j+=2) {
            ScanNodeInfo tmp;
            strcpy(tmp.ip, nodeIPMACvector[j].data());
            strcpy(tmp.mac, nodeIPMACvector[j+1].data());
            scanNodeInfoVector.push_back(tmp);
          };
        };
      };
    };
    return scanNodeInfoVector;
  };

  int updateNetworkData(int port, string currentWAN) {
    int i;
    int j;

    networkNodeIdentification *nni   = new networkNodeIdentification();
    vector<ScanNodeInfo> scanNetwork = scanNetworkWAN(currentWAN);

    for (i=0; i < currentNetworkInfo.size(); i++) {
       currentNetworkInfo[i].available = false;
    };

    if (scanNetwork.size() != 0 ) {
      for (i=0; i < scanNetwork.size(); i++) {
        bool found = false;
        for (j=0; j < currentNetworkInfo.size(); j++) {
          if (strcmp(scanNetwork[i].ip, currentNetworkInfo[j].ip) == 0) {
            found = true;
            currentNetworkInfo[j].available = true;
          };
        };

        if (!found) {
          ScanNodeInfo tmp;
          strcpy(tmp.name, (nni -> identifyClient(scanNetwork[i].ip, port)).c_str());
          strcpy(tmp.ip, scanNetwork[i].ip);
          strcpy(tmp.mac, scanNetwork[i].mac);
          tmp.available = true;
          tmp.time = clock();
          currentNetworkInfo.push_back(tmp);
        };
      };

      for (i=0; i < currentNetworkInfo.size(); i++) {
        bool found = false;
        for (j=0; j < scanNetwork.size(); j++) {
          if (strcmp(scanNetwork[i].ip, currentNetworkInfo[j].ip) == 0) {
            found = true;
          };
        };
        if (!found) {
          if (currentNetworkInfo[j].available) {
            currentNetworkInfo[j].time = clock();
          };
        };
      };
          
      for (i=0; i < currentNetworkInfo.size(); i++) {
        if (!currentNetworkInfo[i].available) {
          for (j=0; j < scanNetwork.size(); j++) {
             if (scanNetwork[j].available) {
             if (strcmp(currentNetworkInfo[i].name, scanNetwork[j].name) == 0) {
                currentNetworkInfo.erase (currentNetworkInfo.begin()+i);
             };
           };
          };
        };
      };

     for (i=0; i < currentNetworkInfo.size(); i++) {
       cout << currentNetworkInfo[i].ip   << endl;
       cout << currentNetworkInfo[i].name   << endl;
       cout << currentNetworkInfo[i].available << endl;
       cout << ".........." << endl;
     };
      return 0;

    } else {
      cout << "Network is empty" << endl;
      return 1;
    };
  };
};
