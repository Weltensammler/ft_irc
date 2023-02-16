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
// #include <signal.h>
#include <vector>

#include "user.hpp"
#include "channel.hpp"

class Channel;
class User;

class Server {
	private:
		Server();
		~Server();
		Server(std::string _pass, int _port, std::string _serverName);

	private:
		std::string		_pass;
		int				_port;
		std::string		_serverName;
		
		struct pollfd 			clients[1024];
		std::vectorUser> 		userList;
		std::vector<Channel> 	channelList;

	int createserver(void)
	void readinput(int clientfd, pollfd *clients, vector<User> *userList)
	void acceptcall(int server, pollfd *client, vector<User> *userList)






#endif