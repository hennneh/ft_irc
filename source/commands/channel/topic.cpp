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
	std::vector<std::string> params;
	params.push_back(msg.parameters.at(0));
	params.push_back("No topic is set");
	client.sendmsg(ft::Message(irc._hostname, "331", params));
}
