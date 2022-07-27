#include "commands.hpp"

void cmd::ping(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	client.sendmsg("PONG " + msg.parameters.at(0));
}
