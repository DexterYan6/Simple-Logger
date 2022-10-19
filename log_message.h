//log_message.h

#ifndef LOG_MESSAGE_H
#define LOG_MESSAGE_H

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

class log_message {
    private:
        string timestamp;
        string msg_text;

    public:
        log_message();
        log_message(string timeSt, string text_msg);
        ~log_message();
        string get_message();
        string get_timestamp(); 
};



#endif /*LOG_MESSAGE_H*/
