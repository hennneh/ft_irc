#include <iostream>

int	main(int argc, char **argv)
{
	(void)argv;
	try
	{
		if (argc != 3)
			throw std::runtime_error("Please execute the binary as follows: ./ircserv <port> <password>");
	}
	catch (const std::exception &exception)
	{
		std::cerr << exception.what() << std::endl;
		return (1);
	}
	return (0);
}
