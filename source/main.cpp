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

	try
	{
		ft::IRC irc(ft::stoi(port), passwd);
		irc.reg_cmd("INVITE", cmd::invite);
		irc.reg_cmd("JOIN", cmd::join);
		irc.reg_cmd("KICK", cmd::kick);
		irc.reg_cmd("LIST", cmd::list);
		irc.reg_cmd("MODE", cmd::mode);
		irc.reg_cmd("NAMES", cmd::names);
		irc.reg_cmd("PART", cmd::part);
		irc.reg_cmd("TOPIC", cmd::topic);

		irc.reg_cmd("AWAY", cmd::away);
		irc.reg_cmd("NICK", cmd::nick);
		irc.reg_cmd("PASS", cmd::pass);
		irc.reg_cmd("QUIT", cmd::quit);
		irc.reg_cmd("USER", cmd::user);

		irc.reg_cmd("NOTICE", cmd::notice);
		irc.reg_cmd("PING", cmd::ping);
		irc.reg_cmd("PRIVMSG", cmd::privmsg);

		irc.reg_cmd("WHO", cmd::who);
		irc.reg_cmd("WHOIS", cmd::whois);

		irc.reg_cmd("TIME", cmd::timer);
		irc.reg_cmd("OPER", cmd::oper);
		irc.reg_cmd("VERSION", cmd::version);

		irc.reg_cmd("ADMIN", cmd::admin);
		irc.reg_cmd("INFO", cmd::info);

		irc.reg_cmd("ISON", cmd::ison);
		irc.reg_cmd("DIE", cmd::dummy);

		cmd::mk_map(irc._c_ft);
		cmd::mk_map(irc._u_ft);
		irc.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << TXT_RED << "[IRC] ERROR: " << e.what() << TXT_NUL << std::endl;
	}
}
