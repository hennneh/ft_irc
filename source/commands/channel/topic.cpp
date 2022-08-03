#include "../commands.hpp"
#include "../../irc.hpp"

//TODO
void cmd::topic(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() < 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS);
		return;
	}
	// Check privileges
	// Check if on channel
	// Check if Topic
	client.sendErrMsg(irc._hostname, RPL_TOPIC, msg.parameters.at(0), "No topic is set");
}
