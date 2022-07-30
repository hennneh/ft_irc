#include "commands.hpp"

bool checkNick(std::string nick)
{
	if (!((nick[0] >= 'a' && nick[0] <= 'z') || (nick[0] >= 'A' && nick[0] <= 'Z')))
		return (false);
	return (true);
}

void cmd::nick(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	if (!client._raspberry)
	{
		//client.sendmsg(ft::Message(":127.0.0.1 462 :Unauthorized command (already registered)")); //ERR_ALREADYREGISTRED
		return ;
	}
	if (msg.parameters.size() != 1)
	{
		client.sendmsg(ft::Message(":127.0.0.1 431 :No nickname given")); //ERR_NONICKNAMEGIVEN
		return ;
	}
	if (msg.parameters.at(0).empty() || !checkNick(msg.parameters.at(0)))
	{
		client.sendmsg(ft::Message(":127.0.0.1 432 :Erroneus nickname")); //ERR_ERRONEUSNICKNAME
		return ;
	}
	if (irc._connections.find(msg.parameters.at(0)) != irc._connections.end())
	{
		// replacement for network-wide ERR_NICKCOLLISION 
		client.sendmsg(ft::Message(":127.0.0.1 433 :Nickname is already in use")); //ERR_NICKNAMEINUSE
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
