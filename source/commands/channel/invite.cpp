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
	if (iter_clnt->second.op_priv == false)
	{
		client.sendErrMsg(irc._hostname, ERR_CHANOPRIVSNEEDED, _channel.getName());
		return ;
	}
	if (!iter_invt->second._awayMsg.empty())
	{
		client.sendErrMsg(iter_invt->second.getFullId(), RPL_AWAY, iter_invt->second.getNick(), iter_invt->second._awayMsg);
		return ;
	}
	_channel._invitelist.insert(iter_invt->second.getNick());
	client.sendMsg(std::string(":" + irc._hostname + " 341 " + _channel.getName() + " " + iter_invt->second.getNick()));
	std::vector<std::string> argv;
	argv.push_back( iter_invt->second.getNick());
	argv.push_back(_channel.getName());
	iter_invt->second.sendMsg(ft::Message(client.getFullId(), "INVITE", argv));
}

/*
RPL_INVITING
*/
