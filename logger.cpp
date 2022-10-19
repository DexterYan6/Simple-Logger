#include "logger.h"
#include "log_message.h"
#include <cstring>

using namespace std;

         
logger::logger(string nameApp) {  //constructor
    appName = nameApp;
    sqlite3_open("database.db", &db);
    cout <<"Database Opened" << endl;
}

logger::~logger() {  //destructor
    sqlite3_close(db);
    cout <<"Database Closed" << endl;
}

void logger::write(string timeStp, string msgLog) { //insert into database
    sqlite3_stmt * stmt;
    string createQuery, sqlMsg, queryStr, selectStr;
    sqlite3_stmt *createStmt;

    logMsg = msgLog;
    timestamp = timeStp;

    queryStr = "CREATE TABLE IF NOT EXISTS " + appName + " (timestamp varchar(255), message varchar(255));";  //each unique app name will have its own table
    const char *queryStmt = queryStr.c_str();
    createQuery = queryStmt; //create table
    sqlite3_prepare(db, queryStmt, createQuery.size(), &createStmt, NULL);
    if (sqlite3_step(createStmt) != SQLITE_DONE) {
        cout << "Did not create table" << endl;
    }   

    selectStr = "INSERT INTO " + appName + " (timestamp, message) VALUES ("  //insert into unique app name table
    + quotesql(timestamp) + ","
    + quotesql(logMsg) + ");";   //insert timestamp and message into table;

    const char *selectStmt = selectStr.c_str();
    sqlMsg = selectStmt;  

    sqlite3_prepare( db, selectStmt, sqlMsg.size(), &stmt, NULL);//preparing the statement
    cout <<"Inserting item" << endl;
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cout << "Didn't Insert Item" << endl;  //insert item
    }
    sqlite3_finalize(stmt);
}

vector<log_message> logger::read_all() {  // output all files from database
    sqlite3_stmt * stmt;
    string sqlMsg ,selectStr;
    log_message *logTxt;
    const char* end;
    vector<log_message> logVector;
	int checker, numCols, i;
    
    selectStr = "SELECT * FROM " + appName + ";";   //open table of specific app name
    const char *selectStmt = selectStr.c_str();
    sqlMsg = selectStmt;  
	sqlite3_prepare(db, selectStmt, sqlMsg.size(), &stmt, &end);  //getting all queries in database
    numCols = sqlite3_column_count(stmt);  
    checker = sqlite3_step(stmt);
	while(checker == SQLITE_ROW){  //while there are still more rows in the database
		for(i = 0; i < numCols; i++){  //timestamp column
            if(i==0) {
                timestamp2 = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            }
            else if (i==1) { //message column
                logMsg2 = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt,i)));
            }
		}    
        log_message logTxt(timestamp2, logMsg2);  //store items in log message item
        logVector.push_back(logTxt);  //add items into vector
		checker = sqlite3_step(stmt);
	}
    sqlite3_finalize(stmt);
    return logVector;
}

string logger::quotesql( const string &s ) { //helper method to wrap text to input into database
    return string("'") + s + string("'");
}