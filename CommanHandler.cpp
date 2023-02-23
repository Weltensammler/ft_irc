#include "CommanHandler.hpp"

/*
* getline(): gets a line until delimitor;
* message: the message read in by the servers file descriptor
* client needs to be initizalied with the fd of the server
*/
void CommanHandler::start(User* user, const std::string& message) // client = user // testing
{
	std::string line;
	std::stringstream s_stream(message);
	std::string cmd_name;

	std::cout << "Reached debugging point 3" << std::endl;
	while (std::getline(s_stream, line))
	{
		if (line[line.length() -1] == '\r') // irc messages are terminated with \r carriage return 
		{
			line = line.substr(0, line[line.length() - 1]);
			cmd_name = line.substr(0, line.find(32)); // 32 == space
			//std::remove_if(cmd_name.begin(), cmd_name.end(), isspace); remove spaces befor/after
		}
		try
		{
			// Command *cmd = this->_commandos.at(cmd_name); // where/when filled ?

			std::vector<std::string> cmd_args;

			std::string buffer;
			std::stringstream s_stream_args(line.substr(cmd_name.length(), line.length())); // end of cmd_name till eol

			while (s_stream_args >> buffer) // read args of the cmd in as whole string;
			{
				cmd_args.push_back(buffer);
			}

			// if (user->isRegistered() == false && cmd->authy_needed() == true)
			// {
			// 	user->reply(ERR_NOTREGISTERED(user->getNick())); // errormsg from documentation
			// 	return;
			// }
			// cmd->execute(user, cmd_args);
			if (cmd_name.compare("JOIN") == 0)
			{
				user->execute_join_cmd(user, cmd_name, cmd_args);
				std::cout << "reached debugging point 4 - JOIN cmd" << std::endl;
			}
			// else if (cmd_name.compare("KICK") == 0)
			// {
			// 	user->execute_kick_cmd(user, cmd_name, cmd_args);
			// }
			// else if (cmd_name.compare("NICK") == 0)
			// {
			// 	user->execute_nick_cmd(user, cmd_name, cmd_args);
			// }
			// else if (cmd_name.compare("PING") == 0)
			// {
			// 	user->execute_ping_cmd(cmd_name, cmd_args);
			// }
			// else if (cmd_name.compare("QUIT") == 0)
			// {
			// 	user->execute_quit_cmd(cmd_name, cmd_args);
			// }
			// else if (cmd_name.compare("INVITE") == 0)
			// {
			// 	execute_invite_cmd(user, cmd_name, cmd_args);
			// }
			// else if (cmd_name.compare("USER") == 0)
			// {
			// 	execute_user_cmd()
			// }
		}
		catch (const std::out_of_range& e) // thrown by vector or string
		{
			// user->reply(ERR_UNKNOWNCOMMAND(cmd_name));
			std::cout << "CommanHandler catch" << std::endl;
		}
	}
}
