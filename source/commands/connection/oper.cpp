#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::oper(const ft::Message & msg, ft::Client & client, ft::IRC & irc)
{
	if (msg.parameters.empty() || msg.parameters.size() > 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return ;
	}
	if (irc._op_password.empty() == false && msg.parameters.at(1) != irc._op_password)
	{
		client.sendErrMsg(irc._hostname, ERR_PASSWDMISMATCH, msg.command);
		return ;
	}
	client._operator = true;
	client.sendErrMsg(irc._hostname, RPL_YOUREOPER);
}
