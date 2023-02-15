
#include <sys/socket.h>
#include <sstream>
#include <iostream>

#include "responses.hpp"


void    sendReply(int userSocket, int replyCode)
{
    std::string          msg = ":My_IRC_Server ";
    std::stringstream    ss;  

    ss << replyCode;
    msg += ss.str() + " " + "o";
    switch (replyCode)
    {
        case RPL_WELCOME:
            // msg += " :Welcome to the Internet Relay Chat network o";
            msg += " :Welcome to the Internet Relay Network oli!oli@My_IRC_Server";
            break;
        case RPL_YOURHOST:
            msg += " :Your host is My_IRC_Server, running version serverversion";
            break;
        case RPL_CREATED:
            msg += " :This server was created date";
            break;
        case RPL_MYINFO:
            msg += "servername serverversion available_user_modes available_channel_modes";
            break;

    }
    send(userSocket, msg.c_str(), msg.size(), 0);
}
