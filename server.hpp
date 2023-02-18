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
/* #include "channel.hpp" */

class Channel;
class User;

class Server {
	public:
		Server();
		~Server();
		Server(std::string pass, int port);
		// Server&					operator=(const Server &src);   // Copy Assigment Constructor

		void		createServer();
		void		initClient();
		void		pollLoop();
		void		pingClient();

		int						fd_server;
		struct pollfd 			clients[1024];

		

	private:
		void					readInput(int client_no);
		void					acceptCall();


		int						_port;
		std::string				_pass;
		std::string				_serverName;
		std::vector<User*> 		userList;
		std::vector<Channel*> 	channelList;

		std::vector<std::string>	parseIncomingMsg(std::string buffer);
};

#endif