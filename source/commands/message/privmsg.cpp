#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::privmsg(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.empty())
	{
		client.sendErrMsg(irc._hostname, ERR_NORECIPIENT, msg.command);
		return ;
	}
	if (msg.parameters.size() < 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NOTEXTTOSEND);
		return ;
	}
	std::vector<std::string> _targets = ft::split(msg.parameters.at(0), ',');
	for (size_t x = 0; x < _targets.size(); x ++)
	{
		ft::IRC::connection_map::iterator conn_itr = irc._connections.find(_targets.at(x));
		if (conn_itr == irc._connections.end())
		{
			client.sendErrMsg(irc._hostname, ERR_NOSUCHNICK, _targets.at(x));
			return;
		}
		ft::Client target(conn_itr->second);
		std::vector<std::string> params;
		params.push_back(target.getNick());
		params.insert(params.end(), msg.parameters.begin() + 1, msg.parameters.end());
		ft::Message answer(client.getFullId(), msg.command , params);
		target.sendmsg(answer);
	}
}

// if (msg.parameters.size() > 2)
	// {
	// 	client.sendErrMsg(irc._hostname, ERR_TOOMANYTARGETS, msg.parameters.at(1));
	// 	return ;
	// }
