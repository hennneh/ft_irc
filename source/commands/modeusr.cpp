
#include "commands.hpp"
#include "../irc.hpp"

/*USER FLAGS
[+|-] - Not 100% sure what the differance is
i - marks a users as invisible;
s - marks a user for receipt of server notices;
w - user receives wallops;
o - operator flag.
*/


void m_user::invis(ft::Client& client, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	(void) client;
	(void) channel;
	(void) sign;
	(void) args;
}

void m_user::servnote(ft::Client& client, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	(void) client;
	(void) channel;
	(void) sign;
	(void) args;
}

void m_user::w_all_op(ft::Client& client, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	(void) client;
	(void) channel;
	(void) sign;
	(void) args;
}

void m_user::operant(ft::Client& client, ft::Channel& channel, bool sign, std::vector<std::string> args)
{
	(void) client;
	(void) channel;
	(void) sign;
	(void) args;
}


void cmd::modeUsr(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (irc._connections.find(msg.parameters.at(0)) != irc._connections.end())
	{
		// replacement for network-wide ERR_NICKCOLLISION 
		client.sendmsg(ft::Message(":127.0.0.1 401 :No such nick/channel")); //ERR_NOSUCHNICK
		return ;
	}
	return ;
}

void cmd::reg_ft(m_user_map & _u_ft , const char opt, m_user_ft f)
{
	_u_ft.insert(std::make_pair(opt, f));
}

void cmd::mk_map(m_user_map & _u_ft)
{
	cmd::reg_ft(_u_ft, 'i', m_user::invis);
	cmd::reg_ft(_u_ft, 's', m_user::servnote);
	cmd::reg_ft(_u_ft, 'w', m_user::w_all_op);
	cmd::reg_ft(_u_ft, 'o', m_user::operant);
}

/*
ERR_NEEDMOREPARAMS		DONE
RPL_CHANNELMODEIS
ERR_CHANOPRIVSNEEDED
ERR_NOSUCHNICK			DONE
ERR_NOTONCHANNEL
ERR_KEYSET
RPL_BANLIST
RPL_ENDOFBANLIST
ERR_UNKNOWNMODE
ERR_NOSUCHCHANNEL
ERR_USERSDONTMATCH
RPL_UMODEIS
ERR_UMODEUNKNOWNFLAG
*/