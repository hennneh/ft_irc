#include "../commands.hpp"
#include "../../irc.hpp"

/*
Command: INVITE
Parameters: < nickname > < channel >
*/

void cmd::invite(const ft::Message & msg, ft::Client& client, ft::IRC & irc)
{
	if (msg.parameters.size() != 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return;
	}
	ft::IRC::connection_map::iterator iter_invt = irc._connections.find(msg.parameters.at(0));
	if (iter_invt == irc._connections.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOSUCHNICK, msg.parameters.at(0));
		return ;
	}
	ft::IRC::_channel_map::iterator iter_chan = irc._channels.find(msg.parameters.at(1));
	if (iter_chan == irc._channels.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOSUCHCHANNEL, msg.parameters.at(1));
		return ;
	}
	ft::Channel& _channel = iter_chan->second;
	ft::Channel::clients_map::iterator iter_clnt = _channel._clients.find(client.getNick());
	if (iter_clnt == _channel._clients.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, _channel.getName());
		return ;
	}
	if (_channel._clients.find(msg.parameters.at(0)) != _channel._clients.end())
	{
		client.sendErrMsg(irc._hostname, ERR_USERONCHANNEL, msg.parameters.at(0), _channel.getName());
		return ;
	}
	ft::ChannelUser _host = iter_clnt->second;
	if (_host.op_priv == false)
	{
		client.sendErrMsg(irc._hostname, ERR_CHANOPRIVSNEEDED, msg.parameters.at(0), _channel.getName());
		return ;
	}
	if (!iter_invt->second._awayMsg.empty())
	{
		client.sendErrMsg(iter_invt->second.getFullId(), RPL_AWAY, iter_invt->second.getNick(), iter_invt->second._awayMsg); 
		return ;
	}
	_channel._clients.insert(std::make_pair(msg.parameters.at(0), ft::ChannelUser(iter_invt->second)));
}

/*
RPL_INVITING
*/
