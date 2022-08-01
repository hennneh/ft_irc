#include "commands.hpp"
#include "../irc.hpp"

void cmd::welcome(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	client.sendmsg(":" + irc._hostname + " 001 " + client.getNick() + " :Welcome to the Internet Relay Network " + client.getFullId());
	client.sendmsg(":" + irc._hostname + " 002 " + client.getNick() + " :Your host is " + irc._hostname + ", running version ft_irc0.1");
	client.sendmsg(":" + irc._hostname + " 003 " + client.getNick() + " :This server was created 2022-07-25");
	client.sendmsg(":" + irc._hostname + " 004 " + client.getNick() + " " + irc._hostname + " ft_irc0.1 iswo opsitnmlbvk");
	cmd::motd(msg, client, irc);
}
