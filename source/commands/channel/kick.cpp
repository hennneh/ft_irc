#include "../commands.hpp"
#include "../../irc.hpp"


void cmd::kick(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() < 2 || msg.parameters.size() > 3)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return;
	}
	std::vector<std::string> _v_chnl = ft::split(msg.parameters.at(0), ',');
	std::vector<std::string> _v_usr = ft::split(msg.parameters.at(1), ',');
	if (_v_chnl.size() != _v_usr.size())
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return;
	}
	std::string command = "No reason given";
	if (msg.parameters.size() == 3)
		command = msg.parameters.at(2);
	for (size_t x = 0; x != _v_chnl.size(); x ++)
	{
		ft::IRC::_channel_map::iterator i_chnl = irc._channels.find(_v_chnl[x]);
		if (i_chnl == irc._channels.end())
		{
			client.sendErrMsg(irc._hostname, ERR_NOSUCHCHANNEL, _v_chnl[x]);
			return;
		}
		ft::Channel _chnl = i_chnl->second;
		ft::Channel::clients_map::iterator i_clnt = _chnl._clients.find(client.getNick());
		if (i_clnt == _chnl._clients.end())
		{
			client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, _v_chnl[x]);
			return;
		}
		ft::ChannelUser _clnt = i_clnt->second;
		if (_clnt.op_priv == false)
		{
			client.sendErrMsg(irc._hostname, ERR_CHANOPRIVSNEEDED, _v_chnl[x]);
			return;
		}
		i_clnt = _chnl._clients.find(_v_usr[x]);
		if (i_clnt == _chnl._clients.end())
		{
			client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, _v_chnl[x]);
			return;
		}
		ft::ChannelUser _usr = i_clnt->second;
		_usr.client.sendMsg(ft::Message("You have been kicked for :" + command));
		_usr.client.sendMsg(ft::Message(client.getNick(), "PART", _chnl.getName()));
		_chnl.sendMsg(ft::Message(client.getNick(), "NOTICE", _usr.client.getNick() + " Kicked for:" + command)); // NOT SURE ABOUT THIS
	}
}
