#ifndef COMMANDHANDLER_HPP
# define COMMANDHANDLER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include "Command.hpp"
#include <map>

class Command;

class CommandHandler
{
	private:
		std::map<std::string, Command*> _commandos;

	public:
		CommandHandler();
		CommandHandler(const CommandHandler& obj);
		CommandHandler& operator=(const CommandHandler& obj);
		~CommandHandler();


};

#endif