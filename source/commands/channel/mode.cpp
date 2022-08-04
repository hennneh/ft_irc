
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
	(void)irc;
	client.sendMsg(ft::Message("NOTICE :Option op_priv:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
}

/**
 * @brief p - private channel flag;
*/
void m_channel::prvt(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendMsg(ft::Message("NOTICE :Option prvt:"));
	if (!args.empty())
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
	(void)irc;
	client.sendMsg(ft::Message("NOTICE :Option scrt:"));
	if (!args.empty())
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
	(void)irc;
	client.sendMsg(ft::Message("NOTICE :Option invt:"));
	if (!args.empty())
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
	(void)irc;
	client.sendMsg(ft::Message("NOTICE :Option topic:"));
	if (!args.empty())
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
	(void)irc;
	client.sendMsg(ft::Message("NOTICE :Option clsd:"));
	if (!args.empty())
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE");
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
	(void)irc;
	client.sendMsg(ft::Message("NOTICE :Option ban_msk:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
}

/**
 * @brief v - give/take the ability to speak on a moderated channel;
*/
void m_channel::speak(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendMsg(ft::Message("NOTICE :Option speak:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
}

/**
 * @brief m - give/take moderated channel;
*/
void m_channel::moderate(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendMsg(ft::Message("NOTICE :Option Moderate:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
}

/**
 * @brief k - set channel Key;
*/
void m_channel::key(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendMsg(ft::Message("NOTICE :Option key:"));
	if (args.size() != 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE");
		return ;
	}
	if (sign)
		channel.setPassword(args.at(0));
	else 
		channel.setPassword(args.at(0));
	channel.sendMsg(ft::Message("NOTICE :Key is now " + channel.getPassword()));
	return ;
}

/**
 * @brief l - set user limit on channel;
*/
void m_channel::limit(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendMsg(ft::Message("NOTICE :Option limit:"));
	if (args.size() != 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE");
		return ;
	}
	if (sign)
	{
		int num = ft::stoi(args.at(0));
		if (num < 0)
		{
			client.sendErrMsg(irc._hostname, ERR_UNKNOWNMODE, args.at(0));
			return ;
		}
		channel._user_limit = num;
	}
	else
		channel._user_limit = NOT;
	return ;
	//send something on succes ?
}

void modeChannel(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	bool sign = false;
	ft::IRC::_channel_map::iterator iter = irc._channels.find(msg.parameters.at(0));
	if (iter == irc._channels.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOSUCHCHANNEL, msg.parameters.at(0));
		return ;
	}
	ft::Channel _channel = iter->second;
	ft::Channel::clients_map::iterator iter_client = _channel._clients.find(client.getNick());
	if (iter_client == _channel._clients.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, msg.parameters.at(0));
		return ;
	}
	if (msg.parameters.size() == 1)
	{
		client.sendErrMsg(irc._hostname, RPL_CHANNELMODEIS, msg.parameters.at(0));
		return ;
	}
	ft::ChannelUser _user = iter_client->second;
	if (_user.op_priv == false)
	{
		client.sendErrMsg(irc._hostname, ERR_CHANOPRIVSNEEDED, msg.parameters.at(0));
		return ;
	}
	if (msg.parameters.at(1)[0] == '+')
		sign = true;
	else if (msg.parameters.at(1)[0] != '-')
	{
		client.sendErrMsg(irc._hostname, ERR_UMODEUNKNOWNFLAG);
		return ;
	}
	cmd::m_channel_map::iterator cmd_itr = irc._c_ft.find(msg.parameters.at(1)[1]);
	if (cmd_itr == irc._c_ft.end())
	{
		client.sendErrMsg(irc._hostname, ERR_UNKNOWNMODE, std::string(&(msg.parameters.at(1)[1]), 1));
		return ;
	}
	std::vector<std::string> args (msg.parameters.begin() + 1, msg.parameters.end());
	cmd_itr->second(client, irc, _channel, sign, args);
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
