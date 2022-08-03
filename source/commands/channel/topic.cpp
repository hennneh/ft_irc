#include "../commands.hpp"
#include "../../irc.hpp"

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
	ft::Channel channel = iter->second;
	if (msg.parameters.size() == 1)
	{
		if(channel._topic.empty())
		{
			client.sendErrMsg(irc._hostname, RPL_NOTOPIC, msg.parameters.at(0));
			return ;
		}
		client.sendErrMsg(irc._hostname, RPL_TOPIC, msg.parameters.at(0), channel._topic);
		return ;
	}
	if (channel.__topic_op) // && !channel.client.op_priv) Check privileges
	{
		client.sendErrMsg(irc._hostname, ERR_CHANOPRIVSNEEDED, msg.parameters.at(0));
		return ;
	}
	channel._topic = msg.parameters.at(1);
}
