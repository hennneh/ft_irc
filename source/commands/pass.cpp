#include "commands.hpp"
#include "../irc.hpp"
#include <iostream>

void cmd::pass(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() != 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS);
		return ;
	}
	if (client._raspberry)
	{
		client.sendErrMsg(irc._hostname, ERR_ALREADYREGISTRED);
		return ;
	}
	if (msg.parameters.at(0) == irc.getPass())
		client._raspberry = true;
	std::cout << "Client._raspberry = " << client._raspberry << std::endl;
	return ;
}
