#include <iostream>
#include "user.hpp"

User::User() : _nick(std::string()), _fd(-1), _oper(false) {
	std::cout << "Default user constructor called" << std::endl;
}

User::User(int new_fd) : _nick(std::string()), _fd(new_fd), _oper(false) {
	std::cout << "Default user constructor called with FD input" << std::endl;
}

User &User::operator=(const User &src) {
	this->_fd = src.getFd();
	this->_nick = src.getNick();
	return (*this);
}

User::~User() {
	std::cout << "User deconstructor called" << std::endl;
}

void	User::setFd(int new_fd) {
	this->_fd = new_fd;
}

int	User::getFd() {
	return (this->_fd);
}

void	User::setPass(std::string pass) {
	this->_pass = pass;
}

std::string	User::getPass() const {
	return (this->_pass);
}


void	User::setNick(std::string nick) {
	std::transform(nick.begin(), nick.end(), nick.begin(), ::tolower); // sure that tolower won't create problems like this later?
	this->_nick = nick;
}

int	User::getNick() {
	return (this->_nick);
}

void	User::setUsername(std::string username) {
	this->_username = username;
}

int	User::getUsername() {
	return (this->_username);
}

void	User::setRealname(std::string realname) {
	this->_username = realname;
}

int	User::getRealname() {
	return (this->_realname);
}

