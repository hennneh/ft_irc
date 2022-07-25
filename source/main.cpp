#include "irc.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (ft::error("invalid number of arguments"));
	std::string port(argv[1]);
	std::string passwd(argv[2]);
	if (port.length() == 0 || !ft::isStringNumber(port))
		return (ft::error("port needs to be a number"));
	if (ft::stoi(port) < 0 || ft::stoi(port) > 65535)
		return (ft::error("port needs to be between 0 and 65535"));
	return (0);
}
