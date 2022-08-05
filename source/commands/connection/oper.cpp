#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::oper(const ft::Message & msg, ft::Client & client, ft::IRC & irc)
{
	if (msg.parameters.empty() || msg.parameters.size() > 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return ;
	}
	ft::IRC::connection_map::iterator i_clnt;
	for (i_clnt = irc._connections.begin(); i_clnt != irc._connections.end(); i_clnt ++)
	{
		if (msg.parameters.at(0) == i_clnt->second.getUser())
			break ;
		if (i_clnt == --irc._connections.end())
		{
			client.sendErrMsg(irc._hostname, ERR_NOOPERHOST);
			return ;
		}
	}
	if (irc._op_password.empty() == false && msg.parameters.at(1) != irc._op_password)
	{
		client.sendErrMsg(irc._hostname, ERR_PASSWDMISMATCH, msg.command);
		return ;
	}
	i_clnt->second._operator = true;
	i_clnt->second.sendErrMsg(irc._hostname, RPL_YOUREOPER);
}
