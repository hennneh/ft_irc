#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::ping(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	client.sendMsg(":" + irc._hostname + " PONG " + msg.parameters.at(0));
}
