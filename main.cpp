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


int fd_global;

void siginthandler(int signum)
{
	close(fd_global);
	exit(1);
}


int argumentParser()


int main()
{
	signal(SIGINT, siginthandler);
	signal(SIGQUIT, siginthandler);
	if (argc != 4)
	{
		std::cout << "Please enter the right amount of arguments" << std::endl
	}
	std::string serverPass(argv[1]);
	int	port = atoi(argv[2]);
	std::string serverName(argv[3]);

	Server ourServer(serverPass, port, serverName);
    ourServer.createserver();

	struct pollfd clients[1024];

	fd_global = server;
	for (int i = 0; i < 1024; i++)
	{
		clients[i].fd = -1;
		clients[i].events = 0;
		clients[i].revents = 0;
	}
	clients[0].fd = server;
	clients[0].events = POLLIN;
	// TODO create mainloop here
	while (1)
	{
		switch (poll(clients, 1024, 10000))
		{
		case 0:
			std::cout << "Should not be possible" << std::endl;
			break;
		case -1:
			std::cout << "could not be possible" << std::endl;
			break;
		default:
			// std::cout << "begin of the default switch" << std::endl;
			acceptcall(server, clients);
			// readinput(clients);
			break;
		}
	}
	// Close the listening socket
	close(server); //! should we close it ?
	return (0);
}
