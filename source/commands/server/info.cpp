#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::info(const ft::Message & msg, ft::Client & client, ft::IRC & irc)
{
	if (msg.parameters.size() > 1 )
	{
		client.sendErrMsg(irc._hostname, ERR_NOSUCHSERVER);
		return ;
	}
	if (msg.parameters.size() == 1 && msg.parameters.at(0) != irc._hostname)
	{
		client.sendErrMsg(irc._hostname, ERR_NOSUCHSERVER);
		return ;
	}
	client.sendErrMsg(irc._hostname, RPL_INFO, irc._hostname);
	client.sendErrMsg(irc._hostname, RPL_INFO, VERSION);
	client.sendErrMsg(irc._hostname, RPL_INFO, COMPILED);
	client.sendErrMsg(irc._hostname, RPL_INFO, PATCHLEVEL);
	client.sendErrMsg(irc._hostname, RPL_INFO, STARTED);
	client.sendErrMsg(irc._hostname, RPL_ENDOFINFO);
}
