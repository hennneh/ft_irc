#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::away(const ft::Message & msg, ft::Client & client, ft::IRC & irc)
{
	if (msg.parameters.empty())
	{
		client.sendErrMsg(irc._hostname, RPL_UNAWAY);
		client._awayMsg = "";
		return ;
	}
	for (std::vector<std::string>::const_iterator it = msg.parameters.begin(); it != msg.parameters.end(); it++)
	{
		client._awayMsg += *it + " ";
	}
	client.sendErrMsg(irc._hostname, RPL_NOWAWAY);
}
