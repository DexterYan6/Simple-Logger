#include "logger.h"

using namespace std;

int main(int argc, char* argv[]) {
    vector<log_message> logMessage;
    string timestamp, msg;

    string appName = argv[1];  // app name

    logger *newLog =new logger(appName);
    logMessage = newLog->read_all();
    
    for (int i = 0; i < logMessage.size(); i++) {  //grabbing all vector items
       timestamp = logMessage.at(i).get_timestamp();  //get timestamp
       msg = logMessage.at(i).get_message();   //get message
       cout << timestamp + ":" + " " + msg<< endl;  //format
    }
    delete newLog;
}
