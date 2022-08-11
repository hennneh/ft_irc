
#include "../commands.hpp"
#include "../../irc.hpp"
/* CHANNEL FLAGS
[+|-] - Not 100% sure what the differance is
m - moderated channel;
l - set the user limit to channel;
k - set a channel key (password).
*/

/**
 * @brief o - give/take channel operator privileges;
 */
void m_channel::op_priv(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	client.sendMsg(":" + irc._hostname + " NOTICE " + client.getNick() + " :Option op_priv:");
	if (args.size() != 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE o");
		return ;
	}
	ft::Channel::clients_map::iterator iter_client = channel._clients.find(args.at(1));
	if (iter_client == channel._clients.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, args.at(1));
		return ;
	}
	ft::ChannelUser& _user = iter_client->second;
	if (sign)
		_user.op_priv = true;
	else 
		_user.op_priv = false;
	return ;
}

/**
 * @brief p - private channel flag;
*/
void m_channel::prvt(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	client.sendMsg(":" + irc._hostname + " NOTICE " + client.getNick() + " :Option prvt:");
	if (args.size() != 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE");
		return ;
	}
	if (sign)
		channel._private = true;
	else
		channel._private = false;
	return ;
}

/**
 * @brief s - secret channel flag;
*/
void m_channel::scrt(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	client.sendMsg(":" + irc._hostname + " NOTICE " + client.getNick() + " :Option scrt:");
	if (args.size() != 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE");
		return ;
	}
	if (sign)
		channel._secret = true;
	else
		channel._secret = false;
	return ;
}

/**
 * @brief i - invite-only channel flag;
*/
void m_channel::invt(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	client.sendMsg(":" + irc._hostname + " NOTICE " + client.getNick() + " :Option invt:");
	if (args.size() != 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE");
		return ;
	}
	if (sign)
		channel._invite_only = true;
	else
		channel._invite_only = false;
	return ;
}

/**
 * @brief t - topic settable by channel operator only flag;
*/
void m_channel::topic(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	client.sendMsg(":" + irc._hostname + " NOTICE " + client.getNick() + " :Option topic:");
	if (args.size() != 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE");
		return ;
	}
	if (sign)
		channel.__topic_op = true;
	else
		channel.__topic_op = false;
	return ;
}

/**
 * @brief n - no messages to channel from clients on the outside;
*/
void m_channel::clsd(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	client.sendMsg(":" + irc._hostname + " NOTICE " + client.getNick() + " :Option clsd:");
	if (args.size() != 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE n");
		return ;
	}
	if (sign)
		channel._clsd = true;
	else
		channel._clsd = false;
	return ;
}

/**
 * @brief b - set a ban mask to keep users out;
*/
void m_channel::ban_msk(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	(void) irc;
	if (args.size() == 1 && !sign)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE -b");
		return ;
	}
	if (args.size() == 1)
	{
		for(std::set<std::string>::const_iterator it = channel._ban_list.begin(); it != channel._ban_list.end(); it++)
		{
			client.sendErrMsg(irc._hostname, RPL_BANLIST, channel.getName(), *it);
		}
		client.sendErrMsg(irc._hostname, RPL_ENDOFBANLIST, channel.getName());
		return ;
	}
	for(std::vector<std::string>::const_iterator it = args.begin() + 1; it != args.end(); it++)
	{
		if (sign)
			channel._ban_list.insert(*it);
		else
		{
			if (channel._ban_list.find(*it) != channel._ban_list.end())
				channel._ban_list.erase(channel._ban_list.find(*it));
		}
	}
	channel.sendMsg(ft::Message(client.getFullId(), "MODE", args));
	client.sendMsg(ft::Message(client.getFullId(), "MODE", args));
	return ;
}

/**
 * @brief v - give/take the ability to speak on a moderated channel;
*/
void m_channel::speak(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	client.sendMsg(":" + irc._hostname + " NOTICE " + client.getNick() + " :Option speak:");
	if (args.size() != 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE v");
		return ;
	}
	ft::Channel::clients_map::iterator iter_client = channel._clients.find(args.at(1));
	if (iter_client == channel._clients.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, args.at(1));
		return ;
	}
	ft::ChannelUser& _user = iter_client->second;
	if (sign)
		_user.speak = true;
	else 
		_user.speak = false;
	return ;
}

/**
 * @brief m - give/take moderated channel;
*/
void m_channel::moderate(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	client.sendMsg(":" + irc._hostname + " NOTICE " + client.getNick() + " :Option Moderate:");
	if (args.size() != 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE");
		return ;
	}
	if (sign)
		channel._moderated = true;
	else 
		channel._moderated = false;
	return ;
}

/**
 * @brief k - set channel Key;
*/
void m_channel::key(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	client.sendMsg(":" + irc._hostname + " NOTICE " + client.getNick() + " :Option key:");
	if (!sign)
	{
		if (args.size() != 1 )
		{
			client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE -k");
			return ;
		}
		channel.setPassword("");
	}
	else
	{
		if (args.size() != 2 )
		{
			client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE +k");
			return ;
		}
		channel.setPassword(args.at(1));
	}
	channel.sendErrMsg(irc._hostname, RPL_INFO, "Key is now " + channel.getPassword()); // doesnt send to everyone
	return ;
}

/**
 * @brief l - set user limit on channel;
*/
void m_channel::limit(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	client.sendMsg(":" + irc._hostname + " NOTICE " + client.getNick() + " :Option limit:");
	if (sign == false)
	{
		if (args.size() != 1)
		{
			client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE -l");
			return ;
		}
		else
			channel._user_limit = NOT;
	}
	else
	{
		if (args.size() != 2)
		{
			client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE +l");
			return ;
		}
		int num = ft::stoi(args.at(1));
		if (num < 0)
		{
			client.sendErrMsg(irc._hostname, ERR_UNKNOWNMODE, args.at(1));
			return ;
		}
		channel._user_limit = num;
	}
	
	return ;
	//send something on succes ?
}

void modeChannel(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	ft::IRC::_channel_map::iterator iter = irc._channels.find(msg.parameters.at(0));
	if (iter == irc._channels.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOSUCHCHANNEL, msg.parameters.at(0));
		return ;
	}
	ft::Channel& _channel = iter->second;
	ft::Channel::clients_map::iterator iter_client = _channel._clients.find(client.getNick());
	if (iter_client == _channel._clients.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, msg.parameters.at(0));
		return ;
	}
	ft::ChannelUser _user = iter_client->second;
	if (msg.parameters.size() == 1)
	{
		// client.sendErrMsg(irc._hostname, RPL_CHANNELMODEIS, msg.parameters.at(0));
		// this is not what its supposed to do? 
		// isn't this supposed to reply whit the modes currently applied to the channel?
		if (_channel._private)
			client.sendErrMsg(irc._hostname, RPL_CHANNELMODEIS, _channel.getName(), "+p", "");
		if (_channel._secret)
			client.sendErrMsg(irc._hostname, RPL_CHANNELMODEIS, _channel.getName(), "+s", "");
		if (_channel._invite_only)
			client.sendErrMsg(irc._hostname, RPL_CHANNELMODEIS, _channel.getName(), "+i", "");
		if (_channel._user_limit)
			client.sendErrMsg(irc._hostname, RPL_CHANNELMODEIS, _channel.getName(), "+l", std::to_string(_channel._user_limit));
		if (_channel._moderated)
			client.sendErrMsg(irc._hostname, RPL_CHANNELMODEIS, _channel.getName(), "+m", "");
		if (!(_channel._ban_list.empty()))
		{
			std::string masks = "|";
			for(std::set<std::string>::const_iterator it = _channel._ban_list.begin(); it != _channel._ban_list.end(); it++)
				masks = masks + *it + "|";
			client.sendErrMsg(irc._hostname, RPL_CHANNELMODEIS, _channel.getName(), "+b", masks);
		}
		// topic_op?
		// clsd?
		return ;
	}
	if (_user.op_priv == false)
	{
		client.sendErrMsg(irc._hostname, ERR_CHANOPRIVSNEEDED, msg.parameters.at(0));
		return ;
	}
	unsigned int	i = 1;
	unsigned int	j = 1;
	bool			sign = false;
	cmd::m_channel_map::iterator cmd_itr;
	do // loop parser begin
	{
		sign = false;
		if (msg.parameters.at(i)[0] == '+')
			sign = true;
		else if (msg.parameters.at(i)[0] != '-')
		{
			client.sendErrMsg(irc._hostname, ERR_UMODEUNKNOWNFLAG);
			return ;
		}
		cmd_itr = irc._c_ft.find(msg.parameters.at(i)[1]);
		if (cmd_itr == irc._c_ft.end())
		{
			client.sendErrMsg(irc._hostname, ERR_UNKNOWNMODE, std::string(&(msg.parameters.at(1)[1]), 1));
			return ;
		}
		j = i + 1;
		while (msg.parameters.begin() + j != msg.parameters.end() && msg.parameters.at(j)[0] != '+' && msg.parameters.at(j)[0] != '-')
			j++;
		std::vector<std::string> args (msg.parameters.begin() + i, msg.parameters.begin() + j);
		i = j;
		cmd_itr->second(client, irc, _channel, sign, args);
	} while ((msg.parameters.size()) - 1 > i);
}

void cmd::mode(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() < 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return ;
	}
	if (msg.parameters.at(0)[0] == '#' || msg.parameters.at(0)[0] == '&')
		modeChannel(msg, client, irc);
	else
		cmd::modeUsr(msg, client, irc);
}

void cmd::reg_ft(m_channel_map & _c_ft , const char opt, m_channel_ft f)
{
	_c_ft.insert(std::make_pair(opt, f));
}

void cmd::mk_map(m_channel_map & _c_ft)
{
	cmd::reg_ft(_c_ft, 'o', m_channel::op_priv);
	cmd::reg_ft(_c_ft, 'p', m_channel::prvt);
	cmd::reg_ft(_c_ft, 's', m_channel::scrt);
	cmd::reg_ft(_c_ft, 'i', m_channel::invt);
	cmd::reg_ft(_c_ft, 't', m_channel::topic);
	cmd::reg_ft(_c_ft, 'n', m_channel::clsd);
	cmd::reg_ft(_c_ft, 'b', m_channel::ban_msk);
	cmd::reg_ft(_c_ft, 'v', m_channel::speak);
	cmd::reg_ft(_c_ft, 'm', m_channel::moderate);
	cmd::reg_ft(_c_ft, 'k', m_channel::key);
	cmd::reg_ft(_c_ft, 'l', m_channel::limit);
}

/*
ERR_NEEDMOREPARAMS		DONE
RPL_CHANNELMODEIS
ERR_CHANOPRIVSNEEDED	DONE
ERR_NOSUCHNICK			USR
ERR_NOTONCHANNEL		USR
ERR_KEYSET
RPL_BANLIST
RPL_ENDOFBANLIST
ERR_UNKNOWNMODE
ERR_NOSUCHCHANNEL		DONE
ERR_USERSDONTMATCH
RPL_UMODEIS
ERR_UMODEUNKNOWNFLAG
*/
