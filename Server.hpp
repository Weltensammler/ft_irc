#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <poll.h>
#include <fcntl.h>

class Server
{
	private:
		std::string _port;

	public:
		Server();
		Server(const Server& obj);
		Server& operator=(const Server& obj);
		~Server();

		Server(int n_port, )

		void start();
		int make_socket();
		


};

#endif
