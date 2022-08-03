#include "../commands.hpp"
#include "../../irc.hpp"

bool checkNick(std::string nick)
{
	for (size_t x = 0; x < nick.length(); x ++)
	{
		if (!ft::isAlpha(nick[x]))
			return (false);
	}
	return (true);
}

void cmd::nick(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	if (msg.parameters.size() != 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NONICKNAMEGIVEN);
		return ;
	}
	if (msg.parameters.at(0).empty() || !checkNick(msg.parameters.at(0)))
	{
		client.sendErrMsg(irc._hostname, ERR_ERRONEUSNICKNAME, msg.parameters.at(0));
		return ;
	}
	if (irc._connections.find(msg.parameters.at(0)) != irc._connections.end())
	{
		// replacement for network-wide ERR_NICKCOLLISION
		client.sendErrMsg(irc._hostname, ERR_NICKNAMEINUSE, msg.parameters.at(0));
		return ;
	}
	client.setNick(msg.parameters.at(0));
	if (client.getUser().empty())
		return;
	client._pi = true;
	for(ft::IRC::connection_map::iterator it = irc._connections.begin(); it != irc._connections.end(); it++) {
		if (it->second.getSocket() == client.getSocket()) {
			cmd::welcome(msg, client, irc);
			irc._connections.insert(std::make_pair(client.getNick(), ft::Client(client)));
			irc._connections.erase(it);
			irc._breakloop = true;
			break;
		}
	}
}
