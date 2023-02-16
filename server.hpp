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
	public:
		Server();
		~Server();
		Server(std::string pass, int port, std::string serverName);
		// Server&					operator=(const Server &src);   // Copy Assigment Constructor
		void	Server::initClient();
		void	Server::pollLoop();

		int				fd_server;

	private:
		void		createserver(void);
		void		readinput(int clientfd, pollfd *clients, vector<User> *userList);
		void		acceptcall(int server, pollfd *client, vector<User> *userList);


		std::string		_pass;
		int				_port;
		std::string		_serverName;
		struct pollfd 			clients[1024];
		std::vector<User> 		userList;
		std::vector<Channel> 	channelList;
}
#endif