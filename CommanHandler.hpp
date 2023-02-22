#ifndef COMMANHANDLER_HPP
# define COMMANHANDLER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "server.hpp"

class User;
// class Command;
class Message;
class Server;

class CommanHandler
{
	private:
		// std::map<std::string, Command*> _commandos;

	public:
		CommanHandler();
		CommanHandler(const CommanHandler& obj);
		CommanHandler& operator=(const CommanHandler& obj);
		~CommanHandler();

		void start(User* user, const std::string& message);


};

#endif