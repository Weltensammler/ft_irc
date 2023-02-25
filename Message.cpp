# include "Message.hpp"

Message::Message()
{
	this->setPrefix("", "", "", "");
	this->isCommand = false;
	this->isValid = false;
	this->isChat = true;
	this->min_params = 0;
	this->max_single_strs = 0;
	this->command = std::string("");
	this->flags = std::vector<std::string>();
	this->params = std::vector<std::string>();
	this->buffer = std::string("");
	std::cout << "Default empty Message constructed." << std::endl;
}

Message::Message(std::string message_raw)
{
	// Might use private parsing function(s)... OR NOT...
	this->setPrefix("", "", "", "");
	this->isCommand = false;
	this->isValid = false;
	this->isChat = true;
	this->min_params = 0;
	this->max_single_strs = 0;
	this->command = std::string("");
	this->flags = std::vector<std::string>();
	this->params = std::vector<std::string>();
	this->buffer = std::string(message_raw);

	int	message_index = 0;

	parse_command(message_raw);

	if (this->isCommand && this->isValid)
	{
		message_index = message_index + this->command.length();
		parse_params(message_raw);
	}
	// // Parse command
	// int	message_index = 0;
	// int	command_category = 0;

	// if (message_raw.length() > 4 && message_raw.at(message_index) == '/' && message_raw.at(message_index + 1) != ' ')
	// {
	// 	std::string	cmd_string;

	// 	while (message_raw.at(message_index) != ' ' && message_raw.at(message_index) != '\t')
	// 	{
	// 		cmd_string.push_back(message_raw.at(message_index));
	// 		message_index++;
	// 	}

	// 	for (int i = 0; i < cmd_string.length(); i++)
	// 		this->command.push_back(std::toupper(cmd_string.at(i)));

	// 	// Searching through the first category of commands
	// 	for (std::vector<std::string>::const_iterator it = this->known_commands_one.begin(); it != this->known_commands_one.end(); it++)
	// 	{
	// 		if (*it == this->command)
	// 		{
	// 			command_category = 1;
	// 			break ;
	// 		}
	// 	}
	// 	// if (command_category == 0)
	// 	// ... further for-loops through other vectors of known commands ...

	// 	switch (command_category)
	// 	{
	// 		case 1: // Specifically for NICK, JOIN, PING or QUIT! Commands with only one parameter in the form of a single string.
	// 		{
	// 			std::string	param_string;

	// 			while (message_raw.at(message_index) == ' ' || message_raw.at(message_index) == '\t')
	// 				message_index++;
	// 			while (message_raw.at(message_index) != ' ' && message_raw.at(message_index) != '\t')
	// 			{
	// 				param_string.push_back(message_raw.at(message_index));
	// 				message_index++;
	// 			}
	// 			this->params.push_back(param_string);
	// 		}
	// 		default:
	// 			break ;
	// 	}

	// 	// Parse flags
	// 	// while (message_raw.at(message_index) == ' ' || message_raw.at(message_index) == '\t')
	// 	// 	message_index++;
	// }
	// else // At this point, the message is identified as being just plain freetext.
	// {
	// 	this->command = std::string("");
	// 	this->flags = std::vector<std::string>();
	// 	this->params = std::vector<std::string>();
	// 	this->freetext = message_raw;
	// }
}

Message::Message(const Message &original)
{
	this->setPrefix(original.getPrefix().nick, original.getPrefix().user, original.getPrefix().channel, original.getPrefix().server);
	this->isCommand = original.getIsCommand();
	this->isValid = original.getIsValid();
	this->isChat = original.getIsChat();
	this->max_single_strs = original.getNumOfParams();
	this->command = original.getCommand();
	this->flags = original.getFlags();
	this->params = original.getParams();
	this->buffer = original.getBuffer();
	std::cout << "Copied Message constructed." << std::endl;
}

Message::~Message()
{
	std::cout << "Message destroyed." << std::endl;
}

Message	&Message::operator=(const Message &original)
{
	this->setPrefix(original.getPrefix().nick, original.getPrefix().user, original.getPrefix().channel, original.getPrefix().server);
	this->isCommand = original.getIsCommand();
	this->isValid = original.getIsValid();
	this->isChat = original.getIsChat();
	this->max_single_strs = original.getNumOfParams();
	this->command = original.getCommand();
	this->flags = original.getFlags();
	this->params = original.getParams();
	this->buffer = original.getBuffer();
	std::cout << "Copied Message constructed." << std::endl;
	return (*this);
}

t_prefix	Message::getPrefix(void) const
{
	return (this->prefix);
}

bool	Message::getIsCommand(void) const
{
	return (this->isCommand);
}

bool	Message::getIsValid(void) const
{
	return (this->isValid);
}

bool	Message::getIsChat(void) const
{
	return (this->isChat);
}

int		Message::getNumOfParams(void) const
{
	return (this->max_single_strs);
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

std::string	Message::getBuffer(void) const
{
	return (this->buffer);
}

void	Message::setPrefix(std::string newNick, std::string newUser, std::string newChannel, std::string newServer)
{
	this->prefix.nick = newNick;
	this->prefix.user = newUser;
	this->prefix.channel = newChannel;
	this->prefix.server = newServer;
}

void	Message::setIsCommand(bool verdict)
{
	this->isCommand = verdict;
}

void	Message::setIsValid(bool verdict)
{
	this->isValid = verdict;
}

void	Message::setIsChat(bool verdict)
{
	this->isChat = verdict;
}

void	Message::setNumOfParams(int newNum)
{
	this->max_single_strs = newNum;
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

void	Message::setBuffer(std::string newBuffer)
{
	this->buffer = newBuffer;
}

void	Message::parse_command(std::string message_raw)
{
	// this->command = std::string("");
	int	message_index = 0;

	if (message_raw.length() > 4 && message_raw.at(message_index) == '/' && message_raw.at(message_index + 1) != ' ')
	{
		std::string	cmd_string;

		setIsCommand(true);
		setIsValid(false);
		setIsChat(false);
		while (message_raw.at(message_index) != ' ' && message_raw.at(message_index) != '\t')
		{
			cmd_string.push_back(message_raw.at(message_index));
			message_index++;
		}

		for (int i = 0; i < cmd_string.length(); i++)
			this->command.push_back(std::toupper(cmd_string.at(i)));
		for (std::vector<std::string>::const_iterator it = this->known_commands.begin(); it != this->known_commands.end(); it++)
		{
			if (*it == this->command)
			{
				setIsValid(true);
				break ;
			}
		}
	}
	// else // At this point, the message is identified as being just plain freetext.
	// {
	// 	for (int i = 0; i < message_raw.length(); i++)
	// 		this->buffer.push_back(message_raw.at(i));
	// }
}

void	Message::parse_params(std::string message_raw)
{
	int	message_index = 0;
	// Moving past the whitespaces after the /COMMANDNAME
	while (message_index < message_raw.length() && message_raw.at(message_index) != ' ' && message_raw.at(message_index) != '\t')
		message_index++;
	while (message_index < message_raw.length() && (message_raw.at(message_index) == ' ' || message_raw.at(message_index) == '\t'))
		message_index++;
std::cout << "params size: " << params.size() << std::endl;
	if (message_index < message_raw.length())
		this->params.push_back(std::string(""));
std::cout << "params size: " << params.size() << std::endl;
	// if (this->command == "/QUIT")
	// {
	// 	while (message_index < message_raw.length())
	// 	{
	// 		this->params.at(0).push_back(message_raw.at(message_index));
	// 		message_index++;
	// 	}
	// 	return ;
	// }

	for (std::vector<std::string>::const_iterator it = this->min_params_one.begin(); it != this->min_params_one.end(); it++)
	{
		if (*it == this->command)
		{
			this->min_params = 1;
			break ;
		}
	}

	for (std::vector<std::string>::const_iterator it = this->min_params_two.begin(); it != this->min_params_two.end(); it++)
	{
		if (*it == this->command)
		{
			this->min_params = 2;
			break ;
		}
	}

	for (std::vector<std::string>::const_iterator it = this->max_single_strings_two.begin(); it != this->max_single_strings_two.end(); it++)
	{
		if (*it == this->command)
		{
			this->max_single_strs = 2;
			break ;
		}
	}

	for (std::vector<std::string>::const_iterator it = this->max_single_strings_one.begin(); it != this->max_single_strings_one.end(); it++)
	{
		if (*it == this->command)
		{
			this->max_single_strs = 1;
			// int	current_param = 0;

			// while (message_index < message_raw.length())
			// {
			// 	if ((message_raw.at(message_index) == ' ' || message_raw.at(message_index) == '\t') && current_param < this->max_single_strs /* or 1 */)
			// 	{
			// 		while (message_raw.at(message_index) == ' ' || message_raw.at(message_index) == '\t')
			// 			message_index++;
			// 		this->params.push_back(std::string(""));
			// 		current_param++;
			// 	}
			// 	this->params.at(current_param).push_back(message_raw.at(message_index));
			// 	message_index++;
			// }
			// if (current_param < this->min_params)
			// 	setIsValid(false);
			break ;
		}
	}

	if (this->params.size() < this->min_params)
		setIsValid(false);

	int	current_param = 0;

	while (message_index < message_raw.length())
	{
		if ((message_raw.at(message_index) == ' ' || message_raw.at(message_index) == '\t') && current_param < this->max_single_strs /* or 1 */)
		{
			while (message_index < message_raw.length() && (message_raw.at(message_index) == ' ' || message_raw.at(message_index) == '\t'))
				message_index++;
			if (message_index < message_raw.length())
			{
				this->params.push_back(std::string(""));
				current_param++;
			}
			else
				break ;
		}
		std::cout << "params size: " << params.size() << std::endl;
std::cout << "current_param: " << current_param << ", min_params: " << min_params << std::endl;
std::cout << "message_raw[" << message_index << "]: " << message_raw[message_index] << std::endl;
		this->params.at(current_param).push_back(message_raw.at(message_index));
		message_index++;
	}
	if (current_param < this->min_params - 1)
		setIsValid(false);
	else
		setIsValid(true);
}
