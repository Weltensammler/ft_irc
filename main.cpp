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

void siginthandler(int signum)
{
	close(ourSever.ft_server);
	exit(1);
}

int main()
{
	if (argc != 4)
	{
		std::cout << "Please enter the right amount of arguments" << std::endl
	}
	std::string serverPass(argv[1]);
	int	port = atoi(argv[2]);
	std::string serverName(argv[3]);

	Server ourServer(serverPass, port, serverName);
    ourServer.createserver();
	// fd_global = ourServer.fd_server;
	signal(SIGINT, siginthandler);
	signal(SIGQUIT, siginthandler);
	initClient();
	ourServer.clients[0].fd = ourServer.fd_server;
	ourServer.clients[0].events = POLLIN;
	ourServer.pollLoop();

	close(ourServer.fd_server);
	return (0);
}
