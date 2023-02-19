#ifndef CHANNEL_HPP
 #define CHANNEL_HPP

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <poll.h>
#include <sstream>
// #include <signal.h>
#include <string>
#include <vector>
/* #include "channel.hpp" */
#include "server.hpp"

class User;

class Channel {
public:
	Channel();
	Channel(...);
	Channel&				operator=(const Channel &src);
	~Channel();

	std::vector<Channel*>	getChannels(); // gives list of all channels that exist / could als obe under User class;

	std::vector<User*>		getOperators();
	void					setOperator();

	std::string				channelName;

private:
	std::vector<User*> 		_operatorList;
	std::vector<User*> 		_userLogList; // all users joined the channel
};

#endif