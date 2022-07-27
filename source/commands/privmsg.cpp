#include "commands.hpp"

void cmd::privmsg(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() < 2)
		return;
	ft::IRC::connection_map::iterator conn_itr = irc._connections.find(msg.parameters.at(0));
	if (conn_itr == irc._connections.end())
		return;
	ft::Client target(conn_itr->second);
	std::vector<std::string> params;
	params.push_back(target.getNick());
	params.insert(params.end(), msg.parameters.begin() + 1, msg.parameters.end());
	ft::Message answer(client.getNick() + "!" + client.getUser() + "@127.0.0.1", "PRIVMSG", params);
	target.sendmsg(answer);
}
