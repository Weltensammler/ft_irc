
#include <sys/socket.h>
#include <sstream>
#include <iostream>

#include "responses.hpp"


void    sendReply(User const & user, User const & target, int userSocket, int replyCode)
{
    std::string          msg = ":My_IRC_Server ";
    std::stringstream    ss;  

    ss << replyCode;
    msg += ss.str() + " " + user.getNick();
    switch (replyCode)
    {
        case RPL_WELCOME:
            // msg += " :Welcome to the Internet Relay Chat network o";
            msg += " :Welcome to the Internet Relay Network " + user.getNick() + "!" + user.getName() + "@My_IRC_Server\r\n";
            break;
        case RPL_YOURHOST:
            msg += " :Your host is My_IRC_Server, running version " + server.getVersion() + "\r\n";
            break;
        case RPL_CREATED:
            msg += " :This server was created " + server.getTimeCreated() + "\r\n";
            break;
        // case RPL_MYINFO:
        //     msg += "servername serverversion available_user_modes available_channel_modes";
        //     break;
        case RPL_WHOISUSER:
            msg += target.getNick() + " " + target.getName() + " " + server.getName() + " :" + target.getRealName + "\r\n";
            break;
        case RPL_WHOISSERVER:
            msg += user.getNick() + " " + server.getName() + " :" + server.getInfos() + "\r\n";
            break;
        case RPL_WHOISOPERATOR:
            msg += channel.getOperator() + " :is an IRC operator\r\n";
            break;
        case RPL_INVITING:
            msg += channel.getName() + " " + target.getName() + "\r\n";
            break;
        case RPL_YOUREOPER:
            msg += ":You are now an IRC operator\r\n";
            break;
        case RPL_TIME:
            msg += server.getName() + " :" + server.getActualTime() + "\r\n";
            break;
        case ERR_NOSUCHNICK:
            msg += target.getNick() + ":No such nick/channel\r\n";
            break;
        case ERR_NOSUCHCHANNEL:
            msg += channel.getName() + ":No such channel\r\n";
            break;
        case ERR_CANNOTSENDTOCHAN:
            msg += channel.getName() + ":Cannot send to channel\r\n";
            break;
        // case ERR_WASNOSUCHNICK:
        //     msg += target.getNick() + "There was no such nickname\r\n";
        //     break;
        case ERR_NOORIGIN:
            msg += ":No origin specified\r\n";
            break;
        case ERR_NORECIPIENT:
            msg += ":No recipient given (" + command.getName() + ")\r\n";
            break;
        case ERR_UNKNOWNCOMMAND:
            msg += command.getName() + ":Unknown command\r\n";
            break;
        case ERR_NICKNAMEINUSE:
            msg += target.getNick() + ":Nickname is already in use\r\n";
            break;
        case ERR_USERNOTINCHANNEL:
            msg += target.getNick() + " " + channel.getName() + " :They aren't on that channel\r\n";
            break;
        case ERR_NOTONCHANNEL:
            msg += channel.getName() + " :You're not on that channel\r\n";
            break;
        case ERR_USERONCHANNEL:
            msg += target.getName() + " " + channel.getName() + " :is already on channel\r\n";
            break;
        case ERR_PASSWDMISMATCH:
            msg += ":Password incorrect\r\n";
            break;
        case ERR_NOPRIVILEGES:
            msg += ":Permission Denied- You're not an IRC operator\r\n";
            break;
        case ERR_CHANOPRIVSNEEDED:
            msg += channel.getName() + " :You're not channel operator\r\n";
            break;

    }
    send(userSocket, msg.c_str(), msg.size(), 0);
}
