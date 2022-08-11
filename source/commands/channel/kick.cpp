#include "../commands.hpp"
#include "../../irc.hpp"

static void kick2(ft::Client & client, ft::Client & target, ft::Channel & channel, const std::string& reasonmsg)
{
	std::vector<std::string> arg;
	arg.push_back(channel._name);
	arg.push_back(target.getNick());
	arg.push_back(reasonmsg);
	channel.sendMsg(ft::Message(client.getFullId(), "KICK", arg));
	client.sendMsg(ft::Message(client.getFullId(), "KICK", arg));
	channel._clients.erase(target.getNick());
}
void cmd::kick(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() < 2 || msg.parameters.size() > 3)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return;
	}
	std::vector<std::string> _v_chnl = ft::split(msg.parameters.at(0), ',');
	std::vector<std::string> _v_usr = ft::split(msg.parameters.at(1), ',');
	if (_v_chnl.size() != _v_usr.size() && _v_chnl.size() != 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return;
	}
	std::string reason = "No reason given";
	if (msg.parameters.size() == 3)
		reason = msg.parameters.at(2);
	for (size_t x = 0; x != _v_chnl.size(); x++)
	{
		ft::IRC::_channel_map::iterator i_chnl = irc._channels.find(_v_chnl[x]);
		if (i_chnl == irc._channels.end())
		{
			client.sendErrMsg(irc._hostname, ERR_NOSUCHCHANNEL, _v_chnl[x]);
			return;
		}
		ft::Channel & _chnl = i_chnl->second;
		ft::Channel::clients_map::iterator me = _chnl._clients.find(client.getNick());
		if (me == _chnl._clients.end())
		{
			client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, _chnl._name);
			return ;
		}
		if (me->second.op_priv == false)
		{
			client.sendErrMsg(irc._hostname, ERR_CHANOPRIVSNEEDED, _chnl._name);
			return ;
		}
		if (_v_chnl.size() == _v_usr.size())
		{
			ft::Channel::clients_map::iterator i_clnt = _chnl._clients.find(_v_usr[x]);
			if (i_clnt == _chnl._clients.end())
			{
				client.sendErrMsg(irc._hostname, ERR_USERNOTINCHANNEL, _v_usr.at(x), _v_chnl[x]);
				return;
			}
			kick2(client, i_clnt->second.client, i_chnl->second, reason);
			return ;
		}
		for (unsigned int i = 0; i < _v_usr.size(); i++)
		{
			ft::Channel::clients_map::iterator i_clnt = _chnl._clients.find(_v_usr[x]);
			if (i_clnt == _chnl._clients.end())
			{
				client.sendErrMsg(irc._hostname, ERR_USERNOTINCHANNEL, _v_usr.at(x), _v_chnl[x]);
				return;
			}
			kick2(client, i_clnt->second.client, i_chnl->second, reason);
		}
	}
}
