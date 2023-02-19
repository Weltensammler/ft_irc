#ifndef MESSAGE_HPP
# define MESSAGE_HPP "Message.hpp"

# include "server.hpp"

typedef struct	s_prefix
{
	std::string	nick;
	std::string	user;
	std::string	server;
}				t_prefix;

class Message
{
	private:
		const std::vector<std::string>	known_commands{"PASS", "QUIT", "NICK", "NOTICE", "USER", "PART", "MODE", "JOIN", "PRIVMSG", "PING", "PONG", "KICK", "BAN"};
		t_prefix						prefix;
		std::string						command;
		std::vector<std::string>		flags;
		std::vector<std::string>		params;
		std::string						freetext;

	public:
		Message();
		Message(std::string message_raw);
		Message(const Message &original);
		~Message();

		Message	&operator=(const Message &original);

		t_prefix					getPrefix(void) const;
		std::string					getCommand(void) const;
		std::vector<std::string>	getFlags(void) const;
		std::vector<std::string>	getParams(void) const;
		std::string					getFreetext(void) const;
		void	setPrefix(std::string newNick, std::string newUser, std::string newServer);
		void	setCommand(std::string newCommand);
		void	setFlags(std::vector<std::string> newFlags);
		void	setParams(std::vector<std::string> newParams);
		void	setFreetext(std::string newFreetext);
};

#endif
