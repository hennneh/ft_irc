#include "commands.hpp"

void cmd::nick(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	client.setNick(msg.parameters.at(0));
	if (client.getUser().empty())
		return;
	for(ft::IRC::connection_map::iterator it = irc._connections.begin(); it != irc._connections.end(); it++) {
		if (it->second.getSocket() == client.getSocket()) {
			cmd::welcome(msg, client, irc);
			irc._connections.insert(std::make_pair(client.getNick(), ft::Client(client)));
			irc._connections.erase(it);
			irc._breakloop = true;
			break;
		}
	}
}