#include <iostream>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	(void)argv;
	try
	{
		if (argc != 3 || ft_strlen(argv[1]) == 0 || ft_strlen(argv[2]) == 0)
			throw std::runtime_error("Please execute the binary as follows: ./ircserv <port> <password>");
	}
	catch (const std::exception &exception)
	{
		std::cerr << exception.what() << std::endl;
		return (1);
	}
	return (0);
}
