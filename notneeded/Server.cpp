#include "Server.hpp"

Server::Server
{

}

Server::Server(const Server& obj)
{
	*this = obj;
}

Server& Server::operator=(const Server& obj)
{
	this->_port = obj._port,


	return (*this);
}

Server::Server(int n_port, ) : _port(n_port)
{

}

/*
* setsocktopt: sets certain options when using the associated socket
* SOL_SOCKET: indicates we are setting options at socket level
* SO_REUSEADDR: allows the socket to be bound to an address that is already in use
* &opt:
* sizeof(opt) :
*********************************************************************
* fcntl(): manipulates filedescriptors;
* O_NONBLOCK: Do not block an open, a read, or a write on the file (do not wait for terminal input)
*/
int Server::make_socket()
{
	int new_sockfd;
	int opt = 1;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		std::cerr  << "error: socket was not created\n";
		exit(EXIT_FAILURE);
	}
	if (setsockopt (sockfd, SOL_SOCKET, SO_REUSEADDR, &opt , sizeof(opt)) != 0)
	{
		std::cerr << "error: setsockopt error\n";
		exit (EXIT_FAILURE);
	}

	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "error: can't set to nonblocking mode\n";
		exit (EXIT_FAILURE);
	}

	struct sockaddr_in server_addy;
	bezero(&server_addy, sizeof(server_addy));
	server_addy.sin_family = AF_INET; // IPv4 only
	server_addy.sin_addr = INADDR_ANY; // puts host IP
	server_addy.sin_port = htons(std::stoi(this->_port));

	if (bind (sockfd, (struct sockaddr*) &server_addy, sizeof(server_addy)) < 0)
	{
			std::cerr << "error: binding failed\n";
	}

	if (listen(sockfd, 5) < 0)
	{
		std::cerr << "error: listen()\n";
		exit(EXIT_FAILURE);
	}

	return (sockfd);
}

