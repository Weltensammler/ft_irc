#include <errno.h>
#include "server.hpp"

Server::Server(std::string serverPass, int port) : _pass(serverPass), _port(port)
{
	this->createServer();
	this->initClient();
	this->pollLoop();
}

Server::~Server()
{
	for (size_t i = 0; i < MAX_USER; i++)
	{
		close(this->clients[i].fd);
	}
	
	std::cout << "Deconstructor Called" << std::endl;
}

void Server::createServer(void)
{
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	//? check what the sockets are
	if (listening == -1)
	{
		std::cerr << "Can't create a socket!" << std::endl;
		return;
	}
	// TODO add setsockopt function and research
	/* Bind the socket to a IP / Port */
	/* INADDR_ANY is a macro to get the IP address of the host machine (server)
	   you could also use inet_addr("127.0.0.1") to assign it manually */
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_addr.s_addr = htonl(INADDR_ANY);
	// inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
	hint.sin_port = htons(this->_port); // here we should do the byteorder network/host using htons and htonl
	if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1)
	{
		std::cerr << "Can't bind to IP/Port!" << std::endl;
		return;
	}
	// Mark the socket for listening in
	if (listen(listening, SOMAXCONN) == -1)
	{
		std::cerr << "Can't listen!" << std::endl;
		return;
	}
	this->fd_server = listening;
}

void Server::readInput(int clientfd)
{
	// While receiving display message, echo message
	char buf[4096];
	// while (i <= 10)
	// {
	// Clear the buffer
	memset(buf, 0, 4096);
	// Wait for a message
	int bytesRecv = recv(clientfd, buf, 4096, 0);
	if (bytesRecv == -1)
	{
		std::cerr << "There was a connection issue!" << std::endl;
	}
	else if (bytesRecv == 0)
	{
		if (close(clientfd) == -1)
			std::cerr << "close!" << std::endl;
		std::cerr << "The Client disconnected!" << std::endl;
		clientfd *= -1; // it will be ignored in future
	}
	else // data from client
	{
		// Display message
		std::cout << "Received: " << std::string(buf, 0, bytesRecv) << std::endl;
	}

	// Send message
	// std::string nick = "mjpro";
	std::string user = "mj_nick";
	std::string channel = "#ch1";
	std::string message = buf;

	std::ostringstream cmd;
	cmd //<< "NICK " << nick << "\r\n"
		<< "USER " << user << "\r\n"
		// 	// << "JOIN " << channel << "\r\n"
		<< "PRIVMSG " << channel << " :" << message << "\r\n";
	std::string cmd_str = cmd.str();
	for (int i = 1; i < MAX_USER; i++)
	{
		if (clients[i].fd != -1)
		{
			send(clients[i].fd, cmd_str.c_str(), cmd_str.size(), 0);
			// std::cout << "Message: " << buf << std::endl;
		}
	}
	// std::cout << "Message is as:" << message << "$\n";
	// send(clientfd, buf, bytesRecv + 1, 0);
	// }
}

/* Accepting a call */
void Server::acceptCall()
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if ((this->clients[i].revents & POLLIN) == POLLIN) // fd is ready fo reading
		{
			if (this->clients[i].fd == this->fd_server) // request for new connection
			{

				std::cout << "New Connection " << std::endl;
				sockaddr_in user;
				socklen_t userSize = sizeof(user);
				char host[NI_MAXHOST];
				char service[NI_MAXSERV];
				memset(host, 0, NI_MAXHOST);
				memset(service, 0, NI_MAXSERV);
				int userSocket = accept(this->fd_server, (sockaddr *)&user, &userSize);
				if (userSocket == -1)
				{
					std::cerr << "Problem with client connecting!" << std::endl;
					return;
				}

				// TODO the next 10 lines are not needed, just there for testing purpose
				int result = getnameinfo((sockaddr *)&user, userSize, host, NI_MAXHOST, service, NI_MAXSERV, 0);
				if (result)
				{
					std::cout << host << " connected on " << service << std::endl;
				}
				else
				{
					inet_ntop(AF_INET, &user.sin_addr, host, NI_MAXHOST);
					std::cout << host << " connected on " << ntohs(user.sin_port) << std::endl;
				}
				int j = 0;
				for (; j < MAX_USER; j++)
					if (this->clients[j].fd == -1)
						break;
				if (j < MAX_USER)
				{
					this->clients[j].fd = userSocket;
					this->clients[j].events = POLLIN; //? do we need this line
					this->clients[j].revents = 0;
					User	*newUser = new User(clients[j]);
					/* User newUser(clients[j]); */
					this->userList.push_back(newUser);
				}
				else
				{
					close(userSocket);
				}
			}
			else // data from an existing connection, recieve it
			{
				this->readInput(this->clients[i].fd);
			}
		}
	}
}

void Server::initClient()
{
	for (int i = 0; i < MAX_USER; i++)
	{
		this->clients[i].fd = -1;
		this->clients[i].events = 0;
		this->clients[i].revents = 0;
	}
	this->clients[0].fd = this->fd_server;
	this->clients[0].events = POLLIN;
}

void Server::pollLoop()
{
	while (1)
	{
		switch (poll(clients, MAX_USER, WAIT_TIME))
		{
		case 0:
			std::cout << "Should not be possible" << std::endl;
			break;
		case -1:
			std::cout << "could not be possible" << std::endl;
			break;
		default:
			// std::cout << "begin of the default switch" << std::endl;
			this->acceptCall();
			// readinput(clients);
			break;
		}
	}
}