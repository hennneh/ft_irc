#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::oper(const ft::Message & msg, ft::Client & client, ft::IRC & irc)
{
	if (msg.parameters.empty() || msg.parameters.size() > 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return ;
	}
	if (client.getNick() != msg.parameters.at(0))
	{
		client.sendErrMsg(irc._hostname, ERR_USERSDONTMATCH);
		return ;
	}
	if (msg.parameters.size() < 2 || msg.parameters.at(1) != irc._op_password)
	{
		client.sendErrMsg(irc._hostname, ERR_PASSWDMISMATCH);
		return ;
	}
	client._operator = true;
	client.sendErrMsg(irc._hostname, RPL_YOUREOPER);
	cmd::mode(ft::Message("", "MODE", client.getNick()), client, irc);
}
