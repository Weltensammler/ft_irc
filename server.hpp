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
		Server(std::string pass, int port);
		~Server();

		int						createServer();
		void					initClient();
		void					pollLoop();
		void					pingClient();

		void					setPass(std::string pass);
		std::string				getPass() const;

		int						isUserInServer(std::vector<User *> _userList, char* host); // checks if user has already been registered before

		User*					findByFd(int clientFd); // finds user by FD
		User*					findByNick(std::string nick); // finds user by nickname
		Channel*				findChannel(std::string name); // finds a channel by name
		bool					authUser(User* activeUser); // checks if user is authed, meaning: pass, nick and username provided
		void					kickUser(User* toBeKicked);

		int						fd_server;
		struct pollfd 			clients[1024]; // each client has unique fd

	private:
		int						readInput(int client_no);
		void					acceptCall();

		int						_port;
		std::string				_pass;
		std::string				_serverName;
		std::vector<User*> 		_userList;
		std::vector<Channel*> 	_channelList;

		std::vector<std::string>	parseIncomingMsg(std::string buffer);
};

#endif