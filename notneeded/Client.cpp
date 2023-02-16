#include "Client.hpp"

Client::Client()
{

}

Client::Client(const Client& obj)
{

}

Client& Client::operator=(const Client& obj)
{

}

Client::~Client()
{

}

const std::string& Client::getNick() const
{
	return (this->_nick);
}

const std::string& Client::getUser() const
{
	return (this->_user);
}

const std::string& Client::getHostname() const
{
	return (this->_hostname);
}

const std::string& Client::getRealname() const
{
	return (this->_realname);
}

/*
*	Use of the extended prefix (['!' <user> ] ['@' <host> ]) must
	not be used in server to server communications and is only
	intended for server to client messages in order to provide
	clients with more useful information about who a message is
	from without the need for additional queries.
	-> calling start in server leading to here.
*/
void Client::reply(const std::string& reply_msg)
{
	std::string return_msg = this->getNick();

	if (this->_user.size() != 0)
	{
		return_msg += "!" + this->getUser()
		if (this->_hostname.size() != 0)
		{
			return_msg += "@" + this->getHostname();
		}
	}
	return (return_msg);
}
