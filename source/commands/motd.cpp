#include "commands.hpp"
#include "../irc.hpp"

void cmd::motd(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	(void)msg;
	client.sendErrMsg(irc._hostname, RPL_MOTDSTART, irc._hostname);
	client.sendErrMsg(irc._hostname, RPL_MOTD, irc._motd);
	client.sendErrMsg(irc._hostname, RPL_ENDOFMOTD);
}
