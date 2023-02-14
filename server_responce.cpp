
#include "responses.hpp"

void    sendReply(char * nick, int replyCode)
{
    std::string          msg = ":My_IRC_Server ";
    std::stringstream    ss;  

    ss << replyCode;
    msg += ss.str() + " " + nick;
    switch (replyCode)
    {
        case RPL_WELCOME:
            msg += " :Welcome to the Internet Relay Chat network " + nick;
        case RPL_YOURHOST:
            msg += " :Your host is " + servername + ", running version " + serverversion;
        case RPL_CREATED
            msg += " :This server was created " + date;
        case RPL_MYINFO
            msg += servername + " " + serverversion +  " " + available_user_modes + " " + available_channel_modes;
            break;

    }
    send(user.getfd(), msg.c_str(), msg.size(), 0);
}
