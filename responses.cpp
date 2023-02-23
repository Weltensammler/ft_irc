#include "user.hpp"

// # define RPL_WELCOME(nick)              ("001 " #nick " welcome to ft_irc")
const char* User::RPL_WELCOME(std::string nick)
{std::string message = "001 " + nick + " welcome to ft_irc"; return (message.c_str());}


// # define RPL_JOIN(nick, channel)                        (":" #nick " JOIN :" #channel)
const char* User::RPL_JOIN(std::string nick, std::string channel)
{replyMessage = ":" + nick + " JOIN :" + channel; return (replyMessage.c_str());}
