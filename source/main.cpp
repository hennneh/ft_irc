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

	ft::IRC irc(ft::stoi(port), passwd);
	irc.reg_cmd("USER", cmd::user);
	irc.reg_cmd("NICK", cmd::nick);
	irc.reg_cmd("PING", cmd::ping);
	irc.reg_cmd("PRIVMSG", cmd::privmsg);
	irc.reg_cmd("QUIT", cmd::quit);
	irc.run();
}

