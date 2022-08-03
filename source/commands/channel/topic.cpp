#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::topic(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() < 1 || msg.parameters.size() > 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS);
		return;
	}
	ft::IRC::_channel_map::iterator iter = irc._channels.find(msg.parameters.at(0));
	if (iter == irc._channels.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, msg.parameters.at(0));
		return ;
	}
	ft::Channel& channel = iter->second;
	ft::Channel::clients_map::iterator iter_clients = channel._clients.find(client.getNick());
	if (iter_clients == channel._clients.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, msg.parameters.at(0));
		return ;
	}
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
	if (channel.__topic_op)
	{
		ft::ChannelUser& user = iter_clients->second;
		if(!user.op_priv)
		{
			client.sendErrMsg(irc._hostname, ERR_CHANOPRIVSNEEDED, msg.parameters.at(0));
			return ;
		}
	}
	channel._topic = msg.parameters.at(1);
	channel.sendErrMsg(irc._hostname, RPL_TOPIC, msg.parameters.at(0), channel._topic);
}
