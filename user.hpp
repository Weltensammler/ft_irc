#ifndef USER_HPP
 #define USER_HPP

#include <string>
#include <vector>
#include "channel.hpp"
#include "server.hpp"

class Channel;

class User {
public:
	User();
	User(int);
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
	const std::string		getUsername() const;
	
	void					setRealname(std::string realname);
	const std::string		getRealname() const;

	void					addChannel(Channel *);
	void					removeChannel(Channel *channel);
	std::vector<Channel *>	getChannels();

	bool					isOperator(); // server operator: channel operators are stored in channel object
	void					setOperator();

private:
	std::string				_nick;
	int						_fd;
	bool					_oper;
	std::string				_pass;
	std::string				_username;
	std::string				_realname;
	std::vector<Channel *>	_channels; // list of channels the user is part of for cross-exchanging data
	struct pollfd &_client;
};

#endif