#include <iostream>
#include <sstream>
#include <string>

#include "leveldb/db.h"

using namespace std;

class myDatabase {
  public:

  int writeToDatabase(string myDatabase, string key, string value) {
    //open database
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, myDatabase, &db);

    if (false == status.ok()) {
      error(myDatabase);
    };

    //write to the database
    leveldb::WriteOptions writeOptions;
    db -> Put(writeOptions, key, value); 

    //close the database
    delete db;
    return 0;
  };

  int readFromDatabase(string myDatabase, string key) {
    //open database
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, myDatabase, &db);

    if (false == status.ok()) {
      error(myDatabase);
    };

    //read from the database
    leveldb::ReadOptions readOptions;
    std::string value;
    db -> Get(readOptions, key, &value);
    cout << value << endl;

    //close the database
    delete db;
    return 0;
  };

  int readAllFromDatabase(string myDatabase) {
    //open database
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, myDatabase, &db);

    if (false == status.ok()) {
      error(myDatabase);  
    };

    //iterate over all elements in database and read read
    leveldb::Iterator* it = db -> NewIterator(leveldb::ReadOptions());
    
    for (it -> SeekToFirst(); it -> Valid(); it -> Next()) {
      cout << it -> key().ToString() << " : " << it -> value().ToString() << endl;
    };
    
    if (false == it->status().ok()) {
     cout << "An error was found during the scan" << endl;
     cout << it -> status().ToString() << endl; 
    };

    //close the database
    delete it;
    delete db;
  };

  int error(string myDatabase) {
    //return error
    cout << "Unable to open database " << myDatabase << endl;
    return -1;
  };
}; 
