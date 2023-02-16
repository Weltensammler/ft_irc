#include "CommandHandler.hpp"

/*
* getline(): gets a line until delimitor;
*/
void start(Client* client, const std::string& message)
{
	std::string line;
	std::stringstream s_stream(message);
	std::string cmd_name;

	while (std::getline(s_stream, line))
	{
		if (line[line.length -1] == '\r') // in case last car is \r 
		{
			line = line.substr(0, line[line.length() - 1]);
			cmd_name = line.substr(0, line.find(32)); // 32 == space
			//std::remove_if(cmd_name.begin(), cmd_name.end(), isspace); remove spaces befor/after
		}
		try
		{
			Command *cmd = this->_commandos.at(cmd_name); // where/when filled ?

			std::vector<std::string> cmd_args;

			std::string buffer;
			std::stringstream s_stream_args(line.substr(cmd_name.length(), line.length())); // end of cmd_name till eol

			while (s_stream_args >> buffer) // read args of the cmd in as whole string;
			{
				cmd_args.push_back(buffer);
			}



		}
		catch ()
		{

		}
	}
}