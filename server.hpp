#ifndef SERVER_HPP
#define SERVER_HPP

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
#include <stdlib.h>
// #include <signal.h>
#include <vector>

#include "user.hpp"
/* #include "channel.hpp" */

#define MAX_USER 1024
#define WAIT_TIME 42000

class Channel;
class User;

class Server
{
public:
	Server();
	~Server();
	Server(std::string pass, int port);
	// Server&					operator=(const Server &src);   // Copy Assigment Constructor

	void createServer();
	void initClient();
	void pollLoop();

	int fd_server;
	struct pollfd clients[MAX_USER];

private:
	void readInput(int client_no);
	void acceptCall();

	std::string _pass;
	int _port;
	std::string _serverName;
	std::vector<User *> userList;
	std::vector<Channel *> channelList;
};

#endif