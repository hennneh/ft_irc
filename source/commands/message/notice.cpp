
#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::notice(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
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
	ft::IRC::connection_map::iterator conn_itr = irc._connections.find(msg.parameters.at(0));
	if (conn_itr == irc._connections.end())
	{
		client.sendErrMsg(irc._hostname, ERR_NOSUCHNICK, msg.parameters.at(1));
		return;
	}
	ft::Client target(conn_itr->second);
	std::vector<std::string> params;
	params.push_back(target.getNick());
	params.insert(params.end(), msg.parameters.begin() + 1, msg.parameters.end());
	ft::Message answer(client.getFullId(), msg.command, params);
	target.sendmsg(answer);
}
