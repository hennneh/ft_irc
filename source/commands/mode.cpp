
#include "commands.hpp"
/* CHANNEL FLAGS
[+|-] - Not 100% sure what the differance is
o - give/take channel operator privileges;
p - private channel flag;
s - secret channel flag;
i - invite-only channel flag;
t - topic settable by channel operator only flag;
n - no messages to channel from clients on the outside;
b - set a ban mask to keep users out;
v - give/take the ability to speak on a moderated channel;

NOT DOING?
m - moderated channel;
l - set the user limit to channel;
k - set a channel key (password).
*/

void m_channel::op_priv(ft::Client& client, ft::IRC& irc, const std::string channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendmsg(ft::Message(":Option op_priv:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
}
void m_channel::prvt(ft::Client& client, ft::IRC& irc, const std::string channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendmsg(ft::Message(":Option prvt:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
}
void m_channel::scrt(ft::Client& client, ft::IRC& irc, const std::string channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendmsg(ft::Message(":Option scrt:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
}
void m_channel::invt(ft::Client& client, ft::IRC& irc, const std::string channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendmsg(ft::Message(":Option invt:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
}
void m_channel::topic(ft::Client& client, ft::IRC& irc, const std::string channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendmsg(ft::Message(":Option topic:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
}
void m_channel::clsd(ft::Client& client, ft::IRC& irc, const std::string channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendmsg(ft::Message(":Option clsd:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
}
void m_channel::ban_msk(ft::Client& client, ft::IRC& irc, const std::string channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendmsg(ft::Message(":Option ban_msk:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
}
void m_channel::speak(ft::Client& client, ft::IRC& irc, const std::string channel, bool sign, std::vector<std::string> args)
{
	(void)irc;
	client.sendmsg(ft::Message(":Option speak:"));
	(void)channel;
	(void)sign;
	(void)args;
	return ;
}


void modeChannel(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	bool sign = false;
	std::string _client = msg.parameters.at(0).substr(1, msg.parameters.at(0).length() - 1);
	if (irc._connections.find(_client) != irc._connections.end()) // change to search channel names
	{
		client.sendErrMsg(ERR_NOSUCHCHANNEL);
		return ;
	}
	//check usr/channel permissions
	
}

void mode(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() <= 2)
	{
		client.sendmsg(ft::Message(":127.0.0.1 461 :Not enough parameters")); //ERR_NEEDMOREPARAMS
		return ;
	}
	if (msg.parameters.at(0)[0] == '#' || msg.parameters.at(0)[0] == '&')
		modeChannel(msg, client, irc);
	else
		cmd::modeUsr(msg, client, irc);
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