
#include "../commands.hpp"
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
	bool sign = false;
	(void) sign;
	// ft::IRC::_user_map::iterator iter = irc._users.find(msg.parameters.at(0));
	// if (iter == irc._users.end())
	// {
	// 	client.sendErrMsg(irc._hostname, ERR_NOSUCHuser);
	// 	return ;
	// }
	// //check usr/user permissions  ERR_CHANOPRIVSNEEDED
	// if (msg.parameters.at(1)[0] == '+')
	// 	sign = true;
	// else if (msg.parameters.at(1)[0] != '-')
	// {
	// 	client.sendErrMsg(irc._hostname, ERR_UMODEUNKNOWNFLAG);
	// 	return ;
	// }
	// cmd::m_user_map::iterator cmd_itr = irc._c_ft.find(msg.parameters.at(1)[1]);
	// if (cmd_itr == irc._c_ft.end())
	// {
	// 	client.sendErrMsg(irc._hostname, ERR_UNKNOWNMODE);
	// 	return ;
	// }
	// std::vector<std::string> args (msg.parameters.begin() + 1, msg.parameters.end());
	// cmd_itr->second(client, irc, iter->second, sign, args);
	if (irc._connections.find(msg.parameters.at(0)) != irc._connections.end())
	{
		// replacement for network-wide ERR_NICKCOLLISION
		client.sendErrMsg(irc._hostname, ERR_NOSUCHNICK);
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
