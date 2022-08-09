#include "../commands.hpp"
#include "../../irc.hpp"

static void rplWhoIs(ft::Client& target, ft::Client& client, const std::string& hostname)
{
	std::vector<std::string> params;
	// USER
	params.push_back(target.getNick());
	params.push_back(target.getUser());
	params.push_back(target.getIp());
	// the '*' is added automatically by the reply
	params.push_back(target.getFull());
	client.sendErrMsg(hostname, RPL_WHOISUSER, params);
	params.clear();
	// Server
	params.push_back(target.getNick());
	params.push_back(hostname);
	params.push_back("42wob IRC server");
	client.sendErrMsg(hostname, RPL_WHOISSERVER, params);
	params.clear();
	// Operator
	if (target._operator)
		client.sendErrMsg(hostname, RPL_WHOISOPERATOR, target.getNick());
	// Away
	if (target._awayMsg.empty() == false)
	{
		params.push_back(target.getNick());
		params.push_back(target._awayMsg);
		client.sendErrMsg(hostname, RPL_AWAY, params);
		params.clear();
	}
	client.sendErrMsg(hostname, RPL_ENDOFWHOIS, target.getNick());
}

void cmd::whois(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.empty() || msg.parameters.size() > 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return ;
	}
	std::string pattern = msg.parameters.at(0);
	if (msg.parameters.at(0).find('.') != std::string::npos)
	{
		if (msg.parameters.at(0) != irc._hostname)
		{
			client.sendErrMsg(irc._hostname, ERR_NOSUCHSERVER, msg.parameters.at(0));
			return ;
		}
		if (msg.parameters.size() != 2)
		{
			client.sendErrMsg(irc._hostname, ERR_NONICKNAMEGIVEN);
			return ;
		}
		pattern = msg.parameters.at(1);
	}
	if (pattern.find('*') != std::string::npos)
	{
		for (ft::IRC::connection_map::iterator clnt = irc._connections.begin(); clnt != irc._connections.end(); clnt++)
		{
			if (ft::wildcardMatch(pattern, clnt->second.getNick()) == false)
				continue;
			rplWhoIs(clnt->second, client, irc._hostname);
		}
	}
	else
	{
		ft::IRC::connection_map::iterator clnt = irc._connections.find(pattern);
		if (clnt == irc._connections.end())
		{
			client.sendErrMsg(irc._hostname, ERR_NOSUCHNICK, pattern);
			return ;
		}
		rplWhoIs(clnt->second, client, irc._hostname);
	}
}
