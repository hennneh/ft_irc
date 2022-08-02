#include "../commands.hpp"
#include "../..irc.hpp"
#include <unistd.h>

void cmd::quit(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)msg;
	close(client.getSocket());
	std::cout << "Client " << client.getNick() << " disconnected!" << std::endl;
	if (irc._connections.erase(client.getNick()) < 1)
	{
		// Manual delete from map, because before NICK/USER the lookup via nickname doesn't work
		for (ft::IRC::connection_map::iterator it = irc._connections.begin(); it != irc._connections.end(); it++)
		{
			if (it->second.getSocket() == client.getSocket())
			{
				irc._connections.erase(it);
				break;
			}
		}
	}
	irc._breakloop = true;
}
