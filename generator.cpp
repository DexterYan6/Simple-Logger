#include "logger.h"
#include <csignal>
#include <unistd.h>
#include <ctime>
#include <chrono>

using namespace std;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::cout; using std::endl;
using std::chrono::duration_cast;

logger *newLog; //declaring variable before main so signal handler can run destructor

void signalHandler(int signum) { //catch signals being sent to terminal
    if(signum == 2){ //if control c function is caught run destructor (close database)
        delete newLog;
    }
    exit(signum);  
}

string timeToStr(long timestamp) {  //convert the current time to a string to store in database
    time_t rawtime;                                
    if (timestamp < 0) rawtime = time(nullptr);    
    else rawtime = static_cast<time_t>(timestamp); 

    struct tm * dt = localtime(&rawtime);
    char timestr[30];
    strftime(timestr, sizeof(timestr), "%B%e %X %Y", dt);  //convert to readable format
    return std::string(timestr); 
}

int main(int argc, char* argv[]) {
    int numMsg, randMsg;
    string msg, time;
    vector<string> userInput;

    string appName = argv[0];
    appName.erase(0,2);

    for (int i = 1; i < argc; i++) {  //user input is stored from array 1 onwards
        userInput.push_back(argv[i]);
    }
    
    newLog =new logger(appName);  //open database
    signal(SIGINT, signalHandler);  
    
    while(1) {
        auto currTime = duration_cast<seconds>(system_clock::now().time_since_epoch()).count(); //current time
        time = timeToStr(currTime);

        randMsg = rand() % (argc-1); //randomize message being entered into the log
        msg = userInput.at(randMsg);

        newLog->write(time, msg);
        int sleepT = rand() % 10 + 1; //randomize sleep time between 1 and 10 seconds
        sleep(sleepT);
    }

    return 0;
};