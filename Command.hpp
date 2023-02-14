#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>

class Command
{
	private:


	public:
		Command();
		Command(const Command& obj);
		Command& operator=(const Command& obj);
		~Command();

};

#endif