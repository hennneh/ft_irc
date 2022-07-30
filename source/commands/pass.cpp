#include "commands.hpp"
#include <iostream>

void cmd::pass(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() != 1)
	{
		client.sendmsg(ft::Message(":127.0.0.1 461 :Not enough parameters")); //ERR_NEEDMOREPARAMS
		return ;
	}
	if (client._raspberry)
	{
		client.sendmsg(ft::Message(":127.0.0.1 462 :Unauthorized command (already registered)")); //ERR_ALREADYREGISTRED
		return ;
	}
	if (msg.parameters.at(0) == irc.getPass())
		client._raspberry = true;
	std::cout << "Client._raspberry = " << client._raspberry << std::endl;
	return ;
}