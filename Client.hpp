#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <iostream>

class CLient
{
	private:
		std::string _nick;
		std::string _user;
		std::string _realname;
		std::string _hostname;


	public:
		Client();
		Client(const Client& obj);
		Client& operator=(const Client& obj);
		~Client();

		const std::string& getNick() const;
		const std::string& getUser() const;
		const std::string& getHostname() const;
		const std::string& getRealname() const;
		void reply()
	

}