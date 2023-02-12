#include "Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "error: wrong number of arguments\n";
		exit(EXIT_FAILURE);
	}
	else
	{
		Server (av[1], av[2]);
		Server.start();



		return (0);
	}
}
