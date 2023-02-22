#ifndef COMMANDHANDLER_HPP
# define COMMANDHANDLER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "user.hpp"

class User;

class CommandHandler
{
	public:
		CommandHandler();
		CommandHandler(const CommandHandler& obj);
		CommandHandler& operator=(const CommandHandler& obj);
		~CommandHandler();

		void start(User* user, const std::string& message);


};

#endif