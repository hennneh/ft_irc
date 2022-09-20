#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::ping(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	if (msg.parameters.size() != 1)
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS);
	else
		client.sendMsg(":" + irc._hostname + " PONG " + msg.parameters.at(0));
}
