# include "Message.hpp"

const char* Message::known_commands[13] = {"/PASS", "/QUIT", "/NICK", "/NOTICE", "/USER", "/PART", "/MODE", "/JOIN", "/PRIVMSG", "/PING", "/PONG", "/KICK", "/BAN"};
const char* Message::min_params_one[6] = {"/NICK", "/JOIN", "/PING", "/BAN", "/KICK", "/MODE"};
const char* Message::min_params_two[2] = {"/NOTICE", "/PRIVMSG"};
const char* Message::max_single_strings_one[7] = {"/NICK", "/JOIN", "/PING", "/NOTICE", "/KICK", "/PART", "/PRIVMSG"};
const char* Message::max_single_strings_two[2] = {"/BAN", "/MODE"};

Message::Message()
{
	// const char* commands[] = {"/PASS", "/QUIT", "/NICK", "/NOTICE", "/USER", "/PART", "/MODE", "/JOIN", "/PRIVMSG", "/PING", "/PONG", "/KICK", "/BAN"};
    // int num_commands = sizeof(commands) / sizeof(commands[0]);
    // known_commands.assign(commands, commands + num_commands);
	// known_commands = std::vector<std::string>({"/PASS", "/QUIT", "/NICK", "/NOTICE", "/USER", "/PART", "/MODE", "/JOIN", "/PRIVMSG", "/PING", "/PONG", "/KICK", "/BAN"});
	// min_params_one = std::vector<std::string>{"/NICK", "/JOIN", "/PING", "/BAN", "/KICK"};
	// min_params_two = std::vector<std::string>{"/NOTICE"};
	// max_single_strings_one = std::vector<std::string>{"/NICK", "/JOIN", "/PING", "/NOTICE", "/KICK", "/PART"};
	// max_single_strings_two = std::vector<std::string>{"/BAN"};
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
		std::string	msg_noflags = parse_flags(message_raw);

		message_index = message_index + this->command.length();
		parse_params(msg_noflags);
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
	this->max_single_strs = original.getMaxSingleStrs();
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
	this->max_single_strs = original.getMaxSingleStrs();
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

int		Message::getMinParams(void) const
{
	return (this->min_params);
}

int		Message::getMaxSingleStrs(void) const
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

void	Message::setMinParams(int newNum)
{
	this->min_params = newNum;
}

void	Message::setMaxSingleStrs(int newNum)
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
		for (int i = 0; i < (sizeof(known_commands) / sizeof(known_commands[0])); i++)
		{
			if (std::string(known_commands[i]) == this->command)
			{
				setIsValid(true);
				break ;
			}
		}
		// for (std::vector<std::string>::const_iterator it = this->known_commands.begin(); it != this->known_commands.end(); it++)
		// {
		// 	if (*it == this->command)
		// 	{
		// 		setIsValid(true);
		// 		break ;
		// 	}
		// }
	}
	// else // At this point, the message is identified as being just plain freetext.
	// {
	// 	for (int i = 0; i < message_raw.length(); i++)
	// 		this->buffer.push_back(message_raw.at(i));
	// }
}

std::string	Message::parse_flags(std::string message_raw)
{
	std::string	msg_noflags;
	int	message_index = 0;

	// Moving past the whitespaces after the /COMMANDNAME
	while (message_index < message_raw.length() && message_raw.at(message_index) != ' ' && message_raw.at(message_index) != '\t')
		message_index++;
	while (message_index < message_raw.length() && (message_raw.at(message_index) == ' ' || message_raw.at(message_index) == '\t'))
		message_index++;
	
	// Moving past the whitespaces after the first parameter
	while (message_index < message_raw.length() && message_raw.at(message_index) != ' ' && message_raw.at(message_index) != '\t')
		message_index++;
	while (message_index < message_raw.length() && (message_raw.at(message_index) == ' ' || message_raw.at(message_index) == '\t'))
		message_index++;
	
	if ((message_raw.at(message_index) == '+' || message_raw.at(message_index) == '-')
		&& message_index + 1 < message_raw.length())
	{
		this->flags.push_back("");
		this->flags.at(0).push_back(message_raw.at(message_index));
		this->flags.at(0).push_back(message_raw.at(message_index + 1));

		int	erase_count = 1;
		while (message_index < message_raw.length() && message_raw.at(message_index) != ' ' && message_raw.at(message_index) != '\t')
		{
			erase_count++;
			message_index++;
		}
		message_index = message_index - erase_count;
		message_raw.erase(message_index, erase_count);
	}
	msg_noflags = message_raw;
	return (msg_noflags);
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

	for (int i = 0; i < (sizeof(min_params_one) / sizeof(min_params_one[0])); i++)
	{
		if (std::string(min_params_one[i]) == this->command)
		{
			this->min_params = 1;
			break ;
		}
	}
	// for (std::vector<std::string>::const_iterator it = this->min_params_one.begin(); it != this->min_params_one.end(); it++)
	// {
	// 	if (*it == this->command)
	// 	{
	// 		this->min_params = 1;
	// 		break ;
	// 	}
	// }

	for (int i = 0; i < (sizeof(min_params_two) / sizeof(min_params_two[0])); i++)
	{
		if (std::string(min_params_two[i]) == this->command)
		{
			this->min_params = 2;
			break ;
		}
	}
	// for (std::vector<std::string>::const_iterator it = this->min_params_two.begin(); it != this->min_params_two.end(); it++)
	// {
	// 	if (*it == this->command)
	// 	{
	// 		this->min_params = 2;
	// 		break ;
	// 	}
	// }

	for (int i = 0; i < (sizeof(max_single_strings_two) / sizeof(max_single_strings_two[0])); i++)
	{
		if (std::string(max_single_strings_two[i]) == this->command)
		{
			this->max_single_strs = 2;
			break ;
		}
	}
	// for (std::vector<std::string>::const_iterator it = this->max_single_strings_two.begin(); it != this->max_single_strings_two.end(); it++)
	// {
	// 	if (*it == this->command)
	// 	{
	// 		this->max_single_strs = 2;
	// 		break ;
	// 	}
	// }

	for (int i = 0; i < (sizeof(max_single_strings_one) / sizeof(max_single_strings_one[0])); i++)
	{
		if (std::string(max_single_strings_one[i]) == this->command)
		{
			this->max_single_strs = 1;
			break ;
		}
	}
	// for (std::vector<std::string>::const_iterator it = this->max_single_strings_one.begin(); it != this->max_single_strings_one.end(); it++)
	// {
	// 	if (*it == this->command)
	// 	{
	// 		this->max_single_strs = 1;
	// 		// int	current_param = 0;

	// 		// while (message_index < message_raw.length())
	// 		// {
	// 		// 	if ((message_raw.at(message_index) == ' ' || message_raw.at(message_index) == '\t') && current_param < this->max_single_strs /* or 1 */)
	// 		// 	{
	// 		// 		while (message_raw.at(message_index) == ' ' || message_raw.at(message_index) == '\t')
	// 		// 			message_index++;
	// 		// 		this->params.push_back(std::string(""));
	// 		// 		current_param++;
	// 		// 	}
	// 		// 	this->params.at(current_param).push_back(message_raw.at(message_index));
	// 		// 	message_index++;
	// 		// }
	// 		// if (current_param < this->min_params)
	// 		// 	setIsValid(false);
	// 		break ;
	// 	}
	// }

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
	//if (current_param < this->min_params - 1)
	if (this->getParams().size() < this->min_params || (this->command == "/MODE" && this->flags.size() == 0))
		setIsValid(false);
	else
		setIsValid(true);
}

std::ostream &operator<<(std::ostream& os, const Message& msg)
{
    os << "isCommand: " << msg.getIsCommand() << "\n";
    os << "isValid: " << msg.getIsValid() << "\n";
    os << "isChat: " << msg.getIsChat() << "\n";
    os << "min_params: " << msg.getMinParams() << "\n";
    os << "max_single_strs: " << msg.getMaxSingleStrs() << "\n";
    os << "command: $" << msg.getCommand() << "$\n";

    os << "flags: $";
	const std::vector<std::string>& temp_flags = msg.getFlags();
    for (std::vector<std::string>::const_iterator it = temp_flags.begin(); it != temp_flags.end(); ++it) {
        os << *it << "$ $";
    }
    os << "$\n";
	os << "flags.size(): " << msg.getFlags().size() << "\n";

    os << "params: $";
	const std::vector<std::string>& temp_params = msg.getParams();
    for (std::vector<std::string>::const_iterator it = temp_params.begin(); it != temp_params.end(); ++it) {
        os << *it << "$ $";
    }
    os << "$\n";
	os << "params.size(): " << msg.getParams().size() << "\n";

    os << "buffer: $" << msg.getBuffer() << "$\n";

    return os;
}
