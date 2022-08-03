#include "../commands.hpp"
#include "../../irc.hpp"

//TODO
void cmd::topic(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() < 1 || msg.parameters.size() > 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS);
		return;
	}
	
	if (!ft::isChannel(msg.parameters.at(0)))
	{
		client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, msg.parameters.at(0));
		return ;
	}
	ft::IRC::_channel_map::iterator iter = irc._channels.find(msg.parameters.at(0));
	if (iter == irc._channels.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, msg.parameters.at(0));
		return ;
	}
	// Check if on channel
	//ERR_NOTONCHANNEL
	bool t = true;
	ft::Channel channel = iter->second;
	// if (msg.parameters.size() == 1)
	// {
	// 		if(NO TOPIC)
	if (t)
	{
	//	RPL_NOTOPIC
	//	return ;
		std::vector<std::string> params;
		params.push_back(client.getNick());
		params.push_back(msg.parameters.at(0));
		params.push_back("No topic is set");
		client.sendMsg(ft::Message(irc._hostname, "331", params));
		return ;
	}
	// 	}
	// 	RPL_TOPIC
	// 	return ;
	// }
	
	if (channel.__topic_op) // && !channel.client.op_priv) Check privileges
	{
		client.sendErrMsg(irc._hostname, ERR_CHANOPRIVSNEEDED, msg.parameters.at(0));
		return ;
	}
	channel._topic = msg.parameters.at(1);
}
