#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::list(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() > 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NOSUCHSERVER);
		return ;
	}
	if (msg.parameters.size() == 2 && msg.parameters.at(1) != irc._hostname)
	{
		client.sendErrMsg(irc._hostname, ERR_NOSUCHSERVER);
		return ;
	}
	client.sendErrMsg(irc._hostname, RPL_LISTSTART);
	if (msg.parameters.empty())
	{
		for (ft::IRC::_channel_map::iterator _i_chnl = irc._channels.begin(); _i_chnl != irc._channels.end(); _i_chnl ++)
		{
			std::vector<std::string> rpl;
			ft::Channel _chnl = _i_chnl->second;
			rpl.push_back(_chnl.getName());
			if (_chnl._private == false || _chnl._secret == false)
			{
				rpl.push_back("Visible");
				rpl.push_back(_chnl._topic);
			}
			else
			{
				rpl.push_back("Prv");
				if (_chnl._secret)
					rpl.at(1) = "Secret";
				ft::Channel::clients_map::iterator _i_usr = _chnl._clients.find(client.getNick());
				if (_i_usr == _chnl._clients.end())
				{
					if (_chnl._secret)
						continue;
					rpl.push_back("");
				}
				else
					rpl.push_back(_chnl._topic);
			}
			client.sendErrMsg(irc._hostname, RPL_LIST, rpl);
		}
		client.sendErrMsg(irc._hostname, RPL_LISTEND);
		return ;
	}
	std::vector<std::string> v_chnl = ft::split(msg.parameters.at(0), ',');
	for (size_t x = 0; x < v_chnl.size(); x ++)
	{
		ft::IRC::_channel_map::iterator i_chnl = irc._channels.find(v_chnl[x]);
		if (i_chnl == irc._channels.end())
		{
			client.sendErrMsg(irc._hostname, ERR_NOSUCHCHANNEL, v_chnl[x]);
			return;
		}
		ft::Channel chnl = i_chnl->second;
		std::vector<std::string> rpl;
		rpl.push_back(chnl.getName());
		if (chnl._private == false || chnl._secret == false)
		{
			rpl.push_back("Visible");
			rpl.push_back(chnl._topic);
		}
		else
		{
			rpl.push_back("Prv");
			if (chnl._secret)
				rpl.at(1) = "Secret";
			ft::Channel::clients_map::iterator _i_usr = chnl._clients.find(client.getNick());
			if (_i_usr == chnl._clients.end())
			{
				if (chnl._secret)
					continue;
				rpl.push_back("");
			}
			else
				rpl.push_back(chnl._topic);
		}
		client.sendErrMsg(irc._hostname, RPL_LIST, rpl);
	}
	client.sendErrMsg(irc._hostname, RPL_LISTEND);
	return ;
}
