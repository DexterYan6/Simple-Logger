//logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "log_message.h"
#include <sqlite3.h>

using namespace std;

class logger{
    public:
        logger();
        logger(string nameApp);
        ~logger();
        void write(string msgLog, string timeStp);
        vector<log_message> read_all();
        string quotesql( const string &s );

    private:
        string timestamp, logMsg, timestamp2, logMsg2, appName;
        sqlite3 *db;
        

};


#endif /* LOGGER_H*/