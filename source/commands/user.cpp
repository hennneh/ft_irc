#include "commands.hpp"

#define SPACE ' '
#define NUL '\0'
#define CR '\r'
#define LF '\n'

bool nonwhite(char c)
{
	if (c == SPACE)
		return (false);
	if (c == NUL)
		return (false);
	if (c == CR)
		return (false);
	if (c == LF)
		return (false);
	return (true);
}

bool checkUser(std::string usr)
{
	for (size_t x = 0; x < usr.length(); x ++)
	{
		if (nonwhite(usr[x]))
			return (false);
	}
	return (true);
}

void cmd::user(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	if (msg.parameters.size() != 4)
	{
		client.sendmsg(ft::Message(":127.0.0.1 461 :Not enough parameters")); //ERR_NEEDMOREPARAMS
		return ;
	}
	if (client.getUser().empty() == false || !client._raspberry)
	{
		client.sendmsg(ft::Message(":127.0.0.1 462 :Unauthorized command (already registered)")); //ERR_ALREADYREGISTRED
		return ;
	}
	if (!checkUser(msg.parameters.at(0))) //No error num?
		return ;
	client.setUser(msg.parameters.at(0));
	client.setFull(msg.parameters.at(3));
	if (!client._pi)
		return;
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
