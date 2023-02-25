#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <poll.h>
#include <sstream>
#include <signal.h>

#include "server.hpp"
#include "Message.hpp"

int main(int argc, char** argv)
{
	std::string	sample_input = "/ping    ";
	Message	*test = new Message(sample_input);

	std::cout << "isCommand: " << test->getIsCommand() << ", isValid: " << test->getIsValid() << ", isChat: " << test->getIsChat() << std::endl;
	if (sample_input.at(0) == '/' && sample_input.at(1) != ' ')
	{
		std::cout << "Command: $" << test->getCommand() << "$" << std::endl;
		std::cout << "Params: ";
		// for (std::vector<std::string>::iterator it = test->getParams().begin(); it != test->getParams().end(); it++)
		// 	std::cout << "$" << *it << "$ " << std::endl;
		//std::cout << "$" << *(test->getParams().begin()) << "$ ";
		//std::cout << "$" << *(test->getParams().begin() + 1) << "$ ";
		std::cout << std::endl;
		int	iterDiff = (test->getParams().end() - test->getParams().begin());
		std::cout << "iterDiff: " << iterDiff << std::endl;
		std::cout << "params.size(): " << test->getParams().size();
		std::cout << std::endl;
	}
	else
		std::cout << "freetext: $" << test->getBuffer() << "$" << std::endl;

	delete test;
	return (0);
}
