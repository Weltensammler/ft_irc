#include "channel.hpp"

Channel::Channel(std::string newName) : _channelName(newName), _maxClients(60) {
	std::cout << "New channel created with name " << _channelName << std::endl;
}

Channel&	Channel::operator=(const Channel &src) {
	this->channelName = src.channelName;
	this->_bannedList = src._bannedList;
	this->_operatorList = src._operatorList;
	return (*this);
}

Channel::~Channel() {
	std::cout << "Channel destroyed" << std::endl;
}


void	Channel::addCreator(User* creator) {
	this->_creatorUser = creator;
	this->setOperator(creator);
}

std::vector<User*>	Channel::getOperators() {
	return (this->_operatorList);
}

void	Channel::setOperator(User* newOp) {
	this->_operatorList.push_back(newOp);
}


void	Channel::addBanned(User* toBan) {
	this->_bannedList.push_back(toBan);
}

bool	Channel::ifBanned(User* ifBan) {
	std::vector<User*>::iterator itr;
	for (itr=begin(this->_bannedList); itr != end(this->_bannedList); ++itr) {
		if ((char *)ifBan->getHost() == *(*itr)->getHost())
			return true;
	}
	std::cerr << "User not found as banned" << std::endl;
	return false;
}


const std::string* Channel::getName()
{
	return (&this->_channelName);
}

size_t Channel::getMaxClients() const
{
	return (this->_maxClients);
}

size_t	Channel::getClientCount() const
{
	return (this->_countClients);
}

void	Channel::addUser(User* user)
{
	this->_userLogList.push_back(user);
}

/* void Channel::notify_others(const std::string& msg, User* skip)
{
	std::vector<User*>::iterator start = this->_userLogList.begin();
	std::vector<User*>::iterator end = this->_userLogList.end();

	while (start != end)
	{
		if ((*start)->getNick().compare(skip->getNick) == 0)
		{
			continue;
		}
		(*start)->write_msg(msg);
		start++;
	}
} */
