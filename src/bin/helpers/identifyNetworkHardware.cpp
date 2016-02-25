class identifyNetworkHardware {

  public:

  vector <string> searchForNetworkHardware() {
    consoleOutput *co  = new consoleOutput();
    createWANfile *cwf = new createWANfile();

    string word;
    vector <string> resultVector;

    string str = co -> getOutputFromConsole("ifconfig | grep wlan | awk '{print $1}'");
    istringstream stm(str);

    while(stm >> word) {
      resultVector.push_back(word);
    };
    return resultVector;
  };
};
