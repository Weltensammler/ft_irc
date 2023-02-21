#include "channel.hpp"

const std::string& Channel::getName()
{
	return (this->channelName);
}

size_t Channel::getMaxClients() const
{
	return (this->max_clients;)
}

size_t	Channel::getClientCount() const
{
	return (this->count_clients);
}

void	Channel::addUser(User* user)
{
	this->_userLogList.push_back(user);
}

void Channel::notify_others(const std::string& msg, User* skip)
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
}

User* Channel::getAdmin() const
{
	return (this->_admin);
}

const User* Channel::get_user_if_in(const std::string& user_name) const
{
	std::vector<User*>::iterator start = *this->_userLogList.begin();
	std::vector<User*>::iterator end = *this->_userLogList.end();

	while (start != end)
	{
		if ((*start)->getNick().compare(user_name) == 0)
		{
			return ((*start));
		}
		start++;
	}

	return (NULL);
}

void Channel::delete_user(User* user)
{
	std::vector<User*>::iterator start = this->_userLogList.begin();
	std::vector<User*>::iterator end = this->_userLogList.end();

	if (this->_userLogList.size() == 0)
	{
		return;
	}

	while (start != end)
	{
		if ((*start)->getNick().compare(user->getNick()) == 0)
		{
			this->_userLogList.erase(start);
		}
		start++;
	}

	if (this->_admin == user)
	{
		_admin = *this->_userLogList.begin();
		std::cout << _admin->getNick() << " is now admin of channel: " << this->getName() << std::endl;
	}
}
