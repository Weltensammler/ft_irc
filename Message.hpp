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
		const std::vector<std::string>	known_commands{"/PASS", "/QUIT", "/NICK", "/NOTICE", "/USER", "/PART", "/MODE", "/JOIN", "/PRIVMSG", "/PING", "/PONG", "/KICK", "/BAN"};
		const std::vector<std::string>	min_params_one{"/NICK", "/JOIN", "/PING", "/BAN", "/KICK"};
		const std::vector<std::string>	min_params_two{"/NOTICE"};
		const std::vector<std::string>	max_single_strings_one{"/NICK", "/JOIN", "/PING", "/NOTICE", "/KICK", "/PART"};
		const std::vector<std::string>	max_single_strings_two{"/BAN"};
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

		void	parse_command(std::string message_raw);
		void	parse_params(std::string message_raw);

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
		int							getNumOfParams(void) const;
		std::string					getCommand(void) const;
		std::vector<std::string>	getFlags(void) const;
		std::vector<std::string>	getParams(void) const;
		std::string					getBuffer(void) const;
		void	setPrefix(std::string newNick, std::string newUser, std::string newChannel, std::string newServer);
		void	setIsCommand(bool verdict);
		void	setIsValid(bool verdict);
		void	setIsChat(bool verdict);
		void	setNumOfParams(int newNum);
		void	setCommand(std::string newCommand);
		void	setFlags(std::vector<std::string> newFlags);
		void	setParams(std::vector<std::string> newParams);
		void	setBuffer(std::string newBuffer);
};

#endif
