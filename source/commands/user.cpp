#include "commands.hpp"

void cmd::user(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	if (msg.parameters.size() != 4)
		return;
	client.setUser(msg.parameters.at(0));
	client.setFull(msg.parameters.at(3));
	if (client.getNick().empty())
		return;
	for(ft::IRC::connection_map::iterator it = irc._connections.begin(); it != irc._connections.end(); it++) {
		if (it->second.getSocket() == client.getSocket()) {
			irc._connections.erase(it);
			irc._connections.insert(std::make_pair(client.getNick(), client));
			cmd::welcome(msg, client, irc);
			break;
		}
	}
}
