#include "../commands.hpp"
#include "../../irc.hpp"
#include <numeric>

void cmd::ison(const ft::Message & msg, ft::Client & client, ft::IRC & irc)
{
	if (msg.parameters.size() < 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return;
	}
	std::vector<std::string> online;
	for (std::vector<std::string>::const_iterator it = msg.parameters.begin(); it != msg.parameters.end(); it++) {
		ft::IRC::connection_map::iterator clnt = irc._connections.find(*it);
		if (clnt == irc._connections.end())
			continue;
		online.push_back(*it);
	}
	std::string reply;
	for (std::vector<std::string>::iterator user_on = online.begin(); user_on != online.end(); user_on++)
		reply = reply + *user_on + " ";
	if (reply.empty())
		reply = " ";
	client.sendErrMsg(irc._hostname, RPL_ISON, reply);
}
