#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::welcome(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	std::vector<std::string> args;
	args.push_back(client.getNick());
	args.push_back(client.getUser());
	args.push_back(client.getIp());
	client.sendErrMsg(irc._hostname, RPL_WELCOME, args);
	args.clear();
	client.sendErrMsg(irc._hostname, RPL_YOURHOST, irc._hostname, irc._version);
	client.sendErrMsg(irc._hostname, RPL_CREATED, "2022-07-25");
	args.push_back(irc._hostname);
	args.push_back(irc._version);
	args.push_back("iswo");
	args.push_back("opsitnmlbvk");
	client.sendErrMsg(irc._hostname, RPL_MYINFO, args);
	cmd::motd(msg, client, irc);
}
