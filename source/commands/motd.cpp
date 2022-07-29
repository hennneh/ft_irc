#include "commands.hpp"

void cmd::motd(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	(void)msg;
	client.sendmsg(":127.0.0.1 375 " + client.getNick() + " :-- Message of the day --");
	client.sendmsg(":127.0.0.1 372 " + client.getNick() + " :-    Hello People!     -");
	client.sendmsg(":127.0.0.1 376 " + client.getNick() + " :-- Message of the day --");
}
