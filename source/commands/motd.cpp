#include "commands.hpp"

void cmd::motd(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	(void)msg;
	client.sendmsg(client.getIp() + " 375 " + client.getNick() + " :-- Message of the day --");
	client.sendmsg(client.getIp() + " 372 " + client.getNick() + " :-    Hello People!     -");
	client.sendmsg(client.getIp() + " 376 " + client.getNick() + " :-- Message of the day --");
}
