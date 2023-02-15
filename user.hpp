#ifndef USER_HPP
 #define USER_HPP

#include <string>
#include <vector>
#include "Channel.hpp"

class Channel;

class User {
public:
	User();
	User(int);
	/* User(User &src); */ // can't make copy, because all users have to be unique?
	User&					operator=(const User &src);
	~User();

	int						setFd();
	int 					getFd() const;

	void 					setNick(std::string nick); // set in lowercase / convert
	std::string				getNick() const;

	void					setUsername(const std::string &username);
	const std::string		&getUsername() const;
	
	void					setRealname(const std::string &realname);
	const std::string		&getRealname() const;

	void					addChannel(Channel *);
	void					removeChannel(Channel *channel);
	std::vector<Channel *>	&getChannels();

	bool					isOperator(); // server operator: channel operators are stored in channel object
	void					setOperator();

private:
	std::string				_nick;
	int						_fd;
	bool					_oper;
	std::string				_username;
	std::string				_realname;
	std::vector<Channel *>	_channels;
};

#endif