# include "Message.hpp"

Message::Message()
{
	this->setPrefix("", "", "");
	this->command = std::string("");
	this->flags = std::vector<std::string>();
	this->params = std::vector<std::string>();
	this->freetext = std::string("");
	std::cout << "Default empty Message constructed." << std::endl;
}

Message::Message(std::string message_raw)
{
	// Would use private parsing function(s)
	this->setPrefix("", "", "");

	// Parse command
	int	message_index = 0;

	while (message_raw.at(message_index) == ' ' || message_raw.at(message_index) == '\t')
		message_index++;
	if (message_raw.at(message_index) == '/')
	{
		std::string	cmd_string;

		while (message_raw.at(message_index) != ' ' && message_raw.at(message_index) != '\t')
		{
			cmd_string.push_back(message_raw.at(message_index));
			message_index++;
		}
		this->command = cmd_string;

		// Parse flags
	}
	else
	{
		this->command = std::string("");
		this->flags = std::vector<std::string>();
		this->params = std::vector<std::string>();
		this->freetext = message_raw;
	}
}

Message::Message(const Message &original)
{
	this->setPrefix(original.getPrefix().nick, original.getPrefix().user, original.getPrefix().server);
	this->command = original.getCommand();
	this->flags = original.getFlags();
	this->params = original.getParams();
	this->freetext = original.getFreetext();
	std::cout << "Copied Message constructed." << std::endl;
}

Message::~Message()
{
	std::cout << "Message destroyed." << std::endl;
}

Message	&Message::operator=(const Message &original)
{
	this->setPrefix(original.getPrefix().nick, original.getPrefix().user, original.getPrefix().server);
	this->command = original.getCommand();
	this->flags = original.getFlags();
	this->params = original.getParams();
	this->freetext = original.getFreetext();
	std::cout << "Copied Message constructed." << std::endl;
}

t_prefix	Message::getPrefix(void) const
{
	return (this->prefix);
}

std::string	Message::getCommand(void) const
{
	return (this->command);
}

std::vector<std::string>	Message::getFlags(void) const
{
	return (this->flags);
}

std::vector<std::string>	Message::getParams(void) const
{
	return (this->params);
}

std::string	Message::getFreetext(void) const
{
	return (this->freetext);
}

void	Message::setPrefix(std::string newNick, std::string newUser, std::string newServer)
{
	this->prefix.nick = newNick;
	this->prefix.user = newUser;
	this->prefix.server = newServer;
}

void	Message::setCommand(std::string newCommand)
{
	this->command = newCommand;
}

void	Message::setFlags(std::vector<std::string> newFlags)
{
	for (std::vector<std::string>::iterator it = newFlags.begin(); it != newFlags.end(); it++)
		this->flags.push_back(*it);
}

void	Message::setParams(std::vector<std::string> newParams)
{
	for (std::vector<std::string>::iterator it = newParams.begin(); it != newParams.end(); it++)
		this->params.push_back(*it);
}

void	Message::setFreetext(std::string newFreetext)
{
	this->freetext = newFreetext;
}
