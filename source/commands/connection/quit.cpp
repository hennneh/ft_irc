#include "../commands.hpp"
#include "../../irc.hpp"
#include <unistd.h>

void cmd::quit(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	ft::Message quitmsg(client.getFullId(), "QUIT", msg.parameters);
	if (msg.parameters.empty())
		quitmsg.parameters.push_back("Leaving.");
	std::set<std::string> toerase;
	for (ft::IRC::_channel_map::iterator chan_itr = irc._channels.begin(); chan_itr != irc._channels.end(); chan_itr++)
	{
		ft::Channel::clients_map::iterator usr_itr = chan_itr->second._clients.find(client.getNick());
		if (usr_itr == chan_itr->second._clients.end())
			continue;
		chan_itr->second.sendMsg(quitmsg);
		chan_itr->second._clients.erase(usr_itr);
		if (chan_itr->second._clients.empty())
			toerase.insert(chan_itr->second._name);
	}
	for (std::set<std::string>::iterator it = toerase.begin(); it != toerase.end(); it++)
		irc._channels.erase(*it);
	client.sendMsg(quitmsg);
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
