
#include "../commands.hpp"
#include "../../irc.hpp"

/*USER FLAGS
[+|-] add remove status bool
i - marks a users as invisible;
s - marks a user for receipt of server notices;
w - user receives wallops;
o - operator flag.
*/

void m_user::reply(ft::Client& client, ft::IRC& irc, bool sign, std::vector<std::string> args)
{
	
	(void)irc;
	(void)sign;
	(void)args;
	std::string flags;
	if (client._invis)
		flags += "+i";
	if (client._operator)
		flags += "+o";
	if (client._snote)
		flags += "+s";
	if (client._wall)
		flags += "+w";
	client.sendErrMsg(irc._hostname, RPL_UMODEIS, flags);
}

void m_user::invis(ft::Client& client, ft::IRC& irc, bool sign, std::vector<std::string> args)
{
	(void) irc;
	(void) args;
	if (sign)
		client._invis = true;
	else
		client._invis = false;
}

void m_user::servnote(ft::Client& client, ft::IRC& irc, bool sign, std::vector<std::string> args)
{
	(void) irc;
	(void) args;
	if (sign)
		client._snote = true;
	else
		client._snote = false;
}

void m_user::w_all_op(ft::Client& client, ft::IRC& irc, bool sign, std::vector<std::string> args)
{
	(void) irc;
	(void) args;
	if (sign)
		client._wall = true;
	else
		client._wall = false;
}

void m_user::operant(ft::Client& client, ft::IRC& irc, bool sign, std::vector<std::string> args)
{
	(void) irc;
	(void) args;
	if (!sign)
		client._operator = false;
}

void cmd::modeUsr(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	ft::IRC::connection_map::iterator iter = irc._connections.find(msg.parameters.at(0));
	if (iter == irc._connections.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOSUCHNICK, msg.parameters.at(0));
		return ;
	}
	if (msg.parameters.at(0) != client.getNick())
	{
		client.sendErrMsg(irc._hostname, ERR_USERSDONTMATCH);
		return ;
	}
	unsigned int	i = 1;
	bool sign = false;
	if (msg.parameters.size() == 1)
	{
		m_user::reply(client, irc, sign, std::vector<std::string> (msg.parameters.begin() + i, msg.parameters.end()));
		return ;
	}
	cmd::m_user_map::iterator cmd_itr;
	do
	{
		sign = false;
		if (msg.parameters.at(i)[0] == '+')
			sign = true;
		else if (msg.parameters.at(i)[0] != '-')
		{
			client.sendErrMsg(irc._hostname, ERR_UMODEUNKNOWNFLAG);
			return ;
		}
		cmd_itr = irc._u_ft.find((msg.parameters.at(i))[1]);
		if (cmd_itr == irc._u_ft.end())
		{
			client.sendErrMsg(irc._hostname, ERR_UNKNOWNMODE); //ERR_UMODEUNKNOWNFLAG
			return ;
		}
		std::vector<std::string> args (msg.parameters.begin() + i, msg.parameters.end());
		cmd_itr->second(client, irc, sign, args);
	}while ((msg.parameters.size()) - 1 > i++);
	return ;
}

void cmd::reg_ft(m_user_map & _u_ft, const char opt, m_user_ft f)
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

/* 	ERR_NEEDMOREPARAMS 		Done
	ERR_UMODEUNKNOWNFLAG	Done
	ERR_UNKNOWNMODE			Done
	ERR_NOSUCHNICK			Done
	ERR_USERSDONTMATCH		Done
	RPL_UMODEIS				Done

	ERR_CHANOPRIVSNEEDED
	ERR_NOTONCHANNEL
	ERR_KEYSET
	ERR_NOSUCHCHANNEL

	RPL_BANLIST
	RPL_ENDOFBANLIST
	RPL_CHANNELMODEIS
*/
