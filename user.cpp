#include <unistd.h>
#include <iostream>
#include "user.hpp"

User::User() : _nick(std::string()), _fd(-1), _oper(false) {
	std::cout << "Default user constructor called" << std::endl;
}

User::User(int fd_user) : _nick(std::string()), _fd(fd_user), 
	_oper(false) {
	std::cout << "Default user constructor called" << std::endl;
}

User::~User() {
	std::cout << "Deconstructor called" << std::endl;
}

