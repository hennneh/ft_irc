
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
	client.sendMsg(ft::Message(":Option op_priv:"));
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
	client.sendMsg(ft::Message(":Option prvt:"));
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
	client.sendMsg(ft::Message(":Option scrt:"));
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
	client.sendMsg(ft::Message(":Option invt:"));
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
	client.sendMsg(ft::Message(":Option topic:"));
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
	client.sendMsg(ft::Message(":Option clsd:"));
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
	client.sendMsg(ft::Message(":Option ban_msk:"));
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
	client.sendMsg(ft::Message(":Option speak:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
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
	//check usr/channel permissions  ERR_CHANOPRIVSNEEDED
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
	cmd_itr->second(client, irc, iter->second, sign, args);
}

void cmd::mode(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() < 1) // pretty sure that if no params are given a reply is expected; usrMode is now built for at least 1 param(Nick), channelmode is not built for that yet
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, "MODE");
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
}

/*
ERR_NEEDMOREPARAMS		DONE
RPL_CHANNELMODEIS
ERR_CHANOPRIVSNEEDED
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
