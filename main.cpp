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

// int fd_global;

/* void siginthandler(int signum)
{
	close(ourSever.ft_server);
	exit(1);
} */

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout << "Please enter the right amount of arguments" << std::endl;
	}
	std::string serverPass(argv[2]);
	int	port = atoi(argv[1]);
	std::cout << "port " << port << " password " << serverPass << "\n";
	Server ourServer(serverPass, port);
	return (0);
}
