#ifndef MESSAGE_HPP
# define MESSAGE_HPP "Message.hpp"

# include "server.hpp"

typedef struct	s_prefix
{
	std::string	nick;
	std::string	user;
	std::string	channel;
	std::string	server;
}				t_prefix;

class Message // CURRENT STATUS: Can only generate Messages with commands NICK, JOIN, PING and QUIT (NOT TESTED YET)
{
	private:
		static const char* known_commands[13];// = {"/PASS", "/QUIT", "/NICK", "/NOTICE", "/USER", "/PART", "/MODE", "/JOIN", "/PRIVMSG", "/PING", "/PONG", "/KICK", "/BAN"};
		static const char* min_params_one[6];// = {"/NICK", "/JOIN", "/PING", "/BAN", "/KICK", "/MODE"};
		static const char* min_params_two[2];// = {"/NOTICE", "/PRIVMSG"};
		static const char* max_single_strings_one[7];// = {"/NICK", "/JOIN", "/PING", "/NOTICE", "/KICK", "/PART", "/PRIVMSG"};
		static const char* max_single_strings_two[2];// = {"/BAN", "/MODE"};
		// const std::vector<std::string>	known_commands;// = {"/PASS", "/QUIT", "/NICK", "/NOTICE", "/USER", "/PART", "/MODE", "/JOIN", "/PRIVMSG", "/PING", "/PONG", "/KICK", "/BAN"};
		// static const std::vector<std::string>	min_params_one;// = {"/NICK", "/JOIN", "/PING", "/BAN", "/KICK"};
		// static const std::vector<std::string>	min_params_two;// = {"/NOTICE"};
		// static const std::vector<std::string>	max_single_strings_one;// = {"/NICK", "/JOIN", "/PING", "/NOTICE", "/KICK", "/PART"};
		// static const std::vector<std::string>	max_single_strings_two;// = {"/BAN"};
		t_prefix						prefix;		// CURRENT STATUS: DOES NOT GET POPULATED
		bool							isCommand;
		bool							isValid;
		bool							isChat;
		int								min_params;
		int								max_single_strs;
		std::string						command;	// CURRENT STATUS: IMPLEMENTED
		std::vector<std::string>		flags;		// CURRENT STATUS: DOES NOT GET POPULATED
		std::vector<std::string>		params;		// CURRENT STATUS: IMPLEMENTED
		std::string						buffer;	// CURRENT STATUS: DOES NOT GET POPULATED

		void		parse_command(std::string message_raw);
		std::string	parse_flags(std::string message_raw);
		void		parse_params(std::string message_raw);

	public:
		Message();
		Message(std::string message_raw);
		Message(const Message &original);
		~Message();

		Message	&operator=(const Message &original);

		t_prefix					getPrefix(void) const;
		bool						getIsCommand(void) const;
		bool						getIsValid(void) const;
		bool						getIsChat(void) const;
		int							getMinParams(void) const;
		int							getMaxSingleStrs(void) const;
		std::string					getCommand(void) const;
		std::vector<std::string>	getFlags(void) const;
		std::vector<std::string>	getParams(void) const;
		std::string					getBuffer(void) const;
		void	setPrefix(std::string newNick, std::string newUser, std::string newChannel, std::string newServer);
		void	setIsCommand(bool verdict);
		void	setIsValid(bool verdict);
		void	setIsChat(bool verdict);
		void	setMinParams(int newNum);
		void	setMaxSingleStrs(int newNum);
		void	setCommand(std::string newCommand);
		void	setFlags(std::vector<std::string> newFlags);
		void	setParams(std::vector<std::string> newParams);
		void	setBuffer(std::string newBuffer);
};

std::ostream &operator<<(std::ostream& os, const Message& msg);

#endif
