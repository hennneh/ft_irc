#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::oper(const ft::Message & msg, ft::Client & client, ft::IRC & irc)
{
	if (msg.parameters.empty() || msg.parameters.size() > 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return ;
	}
	ft::Client _user;
	for (ft::IRC::connection_map::iterator i_clnt = irc._connections.begin(); i_clnt != irc._connections.end(); i_clnt ++)
	{
		_user = i_clnt->second;
		if (msg.parameters.at(0) == _user.getUser())
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
	_user._operator = true;
	_user.sendErrMsg(irc._hostname, RPL_YOUREOPER);
}
