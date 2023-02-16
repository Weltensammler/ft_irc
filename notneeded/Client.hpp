#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sys/poll.h>
#include <sys/socket.h>

enum ClientStatus
{
	HANDSHAKE, LOGIN, PLAY, DISCONNECT
};

class Client
{
	private:
		std::string 
		


	public:
		Client();
		Client(const Client& obj);
		Client& operator=(const Client& obj);
		~Client();

		const std::string& getNick() const;
		const std::string& getUser() const;
		const std::string& getHostname() const;
		const std::string& getRealname() const;
		void reply(const std::string& reply_msg);

		bool is_registered() const
		{

		};
		bool authy_needed();
	

}