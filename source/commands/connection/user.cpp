#include "../commands.hpp"
#include "../../irc.hpp"

bool checkUser(std::string usr)
{
	for (size_t x = 0; x < usr.length(); x ++)
	{
		if (!ft::isNonWhite(usr[x]))
			return (false);
	}
	return (true);
}

void cmd::user(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	if (msg.parameters.size() != 4)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return ;
	}
	if (client.getUser().empty() == false)
	{
		client.sendErrMsg(irc._hostname, ERR_ALREADYREGISTRED);
		return ;
	}
	if (!checkUser(msg.parameters.at(0)))
		return ;
	client.setUser(msg.parameters.at(0));
	client.setFull(msg.parameters.at(3));
	if (client.getNick().empty())
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
