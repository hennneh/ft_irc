#include "commands.hpp"

void cmd::welcome(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	client.sendmsg(client.getIp() + " 001 " + client.getNick() + " :Welcome to the Internet Relay Network " + client.getNick() + "!" + client.getUser() + "@127.0.0.1");
	client.sendmsg(client.getIp() + " 002 " + client.getNick() + " :Your host is 127.0.0.1, running version ft_irc0.1");
	client.sendmsg(client.getIp() + " 003 " + client.getNick() + " :This server was created 2022-07-25");
	client.sendmsg(client.getIp() + " 004 " + client.getNick() + " 127.0.0.1 ft_irc0.1 iswo opsitnmlbvk");
	cmd::motd(msg, client, irc);
}
