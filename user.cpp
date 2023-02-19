#include <iostream>
#include <algorithm>
#include "user.hpp"
#include "server.hpp"

/* User::User() {
	this->_client;
	std::cout << "Default user constructor called" << std::endl;
} */

User::User(pollfd &client) : _client(client) {
	this->_client = client;
	this->_fd = this->_client.fd;
	// new _nick = size(char) * 9;
	// this->_nick = NULL;
	this->_oper = false;
	std::cout << "Default user constructor called with Client Input" << std::endl;
}

User &User::operator=(const User &src) {
	this->_fd = src.getFd();
	this->_nick = src.getNick();
	return (*this);
}

User::~User() {
	// delete _nick 
	std::cout << "User deconstructor called" << std::endl;
}

void	User::setFd(int new_fd) {
	this->_fd = new_fd;
}

int	User::getFd() const {
	return (this->_fd);
}

void	User::setNick(std::string nick) {
	std::transform(nick.begin(), nick.end(), nick.begin(), ::tolower); // sure that tolower won't create problems like this later?
	this->_nick = nick;
}

std::string	User::getNick() const {
	return (this->_nick);
}

void	User::setUsername(std::string username) {
	this->_username = username;
}

std::string	User::getUsername() const {
	return (this->_username);
}

void	User::setRealname(std::string realname) {
	this->_username = realname;
}

std::string	User::getRealname() const {
	return (this->_realname);
}

bool	User::isRegistered() {
	return (this->_isRegistered);
}

time_t	User::getTime() {
	return (std::time(NULL));
}

// -----------------------

std::string User:getPrefix() const
 {
	std::string return_msg = this->getNick();

	if (this->_user.size() != 0)
	{
		return_msg += "!" + this->getUsername()
		if (this->_hostname.size() != 0)
		{
			return_msg += "@" + this->getHostname(); // no hostname func yet
		}
	}
	return(return_msg);
 }

/*
*	Use of the extended prefix (['!' <user> ] ['@' <host> ]) must
	not be used in server to server communications and is only
	intended for server to client messages in order to provide
	clients with more useful information about who a message is
	from without the need for additional queries.
	-> calling start in server leading to here.
*/
void User::reply(const std::string& reply_msg)
{
	write(":" + getPrefix() + " " + reply_msg);
}

/*
* format: JOIN <channel>{,<channel>} [<key>{,<key>}]
*/
void User::execute_join_cmd(User* user, const std::string& cmd_name, std::vector<std::string> args)
{
	if (args.empty() == true)
	{
		user->reply(ERR_NEEDMOREPARAMS(user->getNick(), cmd_name ))
		return ;
	}
	
	std::string channel_name = args[0];
	if (args.size() > 1)
	{
		std::string password = args[1];
	}

	// maximum of 20 channels per conenction
	if (user->_channels.size() >= 20)
	{
		user->reply(ERR_TOOMANYCHANNELS(user->getNick(), channel_name));
		return ;
	}

	Channel* channel = _server->getChannel(channel_name); // still needs _server in user
	if (!channel)
	{
		_server->createChannel(some params) // need create channel in server
	}

	if (channel->getClientsCount() >= channel->getMaxClients())
	{
		user->reply(ERR_CHANNELISFULL(user->getNick(), channel_name));
		return ;
	}

	if (channel->getPWD().compare(password) != 0)
	{
		user->reply(ERR_BADCHANNELKEY(user->getNick(), channel_name));
		return ;
	}
	// actual joining
	channel->addUser(user);
	_channels.push_back(channel);

	std::string user_list;
	std::vector<User*>::iterator start = channel->_userLogList.begin();
	std::vector<User*>::iterator end = channel->_userLogList.end();

	while (start != end)
	{
		user_list.append((*start)->getNick());
		start++;
	}

	reply(RPL_NAMEREPLY(user->getNick(), channel->getName(), user_list));
	reply(RPL_ENDOFNAMES(user->getNick(), channel->getName()));

	channel->notify_others(RPL_JOIN(getPrefix(), channel->getName()));
	std::cout << user->getNick() << " has joined channel " << channel->getName() << std::endl;
}

void User::write_msg(const std::string& msg) const
{
	std::string new_msg = msg + "\r\n"; // per documentation definition line in irc end with \r
	if (send(_fd, new_msg.c_str(), new_msg.length(), 0) < 0) // c_str =copy of the string is sent
	{
		std::cerr << "error when notifying memebers of channell about someone joining\n";
	}
}
