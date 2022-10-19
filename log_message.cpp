#include <iostream>
#include <stdio.h>
#include <string>
#include "log_message.h"

using namespace std;
       
    log_message::log_message(string timeSt, string text_msg) {
        timestamp = timeSt;
        msg_text = text_msg;  
    }

    log_message::~log_message() {
    }

    string log_message::get_message() {
        return msg_text;
    }

    string log_message::get_timestamp() {
        return timestamp;
    }
        