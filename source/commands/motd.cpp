#include "commands.hpp"
#include "../irc.hpp"

void cmd::motd(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	(void)msg;
	client.sendmsg(":" + irc._hostname + " 375 " + client.getNick() + " :-- Message of the day --");
	client.sendmsg(":" + irc._hostname + " 372 " + client.getNick() + " :-    Hello People!     -");
	client.sendmsg(":" + irc._hostname + " 376 " + client.getNick() + " :-- Message of the day --");
}
