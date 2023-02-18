#ifndef USER_HPP
 #define USER_HPP

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <poll.h>
#include <sstream>
#include <ctime>
// #include <signal.h>
#include <string>
#include <vector>
/* #include "channel.hpp" */
#include "server.hpp"

class Channel;

class User {
public:
	/* User(); */
	User(pollfd &client);
	/* User(User &src); */ // can't make copy, because all users have to be unique?
	User&					operator=(const User &src);
	~User();

	void					setFd(int new_fd);
	int 					getFd() const;

	void					setPass(std::string pass);
	std::string				getPass() const;

	void 					setNick(std::string nick); // set in lowercase / convert
	std::string				getNick() const;

	void					setUsername(std::string username);
	std::string				getUsername() const;
	
	void					setRealname(std::string realname);
	std::string				getRealname() const;

	bool					isRegistered();

	void					joinChannel(); // makes user join a channel; prompts server to send message to all relevant users about joining; 
	void					leaveChannel(); // also sends message that user left channel;
	void					createChannel(); // ourUser.createChannel() _ creates new channel, and user is made operator;
	void					removeChannel();

	time_t					getTime(); // returns actual time of call (used for Ping)

/* 	void					addChannel(Channel *);
	void					removeChannel(Channel *channel);
	std::vector<Channel *>	getChannels();

	bool					isOperator(); // server operator: channel operators are stored in channel object
	void					setOperator(); */

private:
	std::string				_nick;
	int						_fd;
	bool					_oper;
	bool					_isRegistered;
	std::string				_pass;
	std::string				_username;
	std::string				_realname;
	std::vector<Channel *>	_channels; // list of channels the user is part of for cross-exchanging data
	struct pollfd &			_client;
};

#endif