#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::part(const ft::Message & msg, ft::Client & client, ft::IRC & irc)
{
	if (msg.parameters.empty() || msg.parameters.size() > 1)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return ;
	}
	std::vector<std::string> c = ft::split(msg.parameters.at(0), ',');
	for (size_t i = 0; i < c.size(); i++)
	{
		bool erased = false;
		ft::IRC::_channel_map::iterator it = irc._channels.find(c.at(i));
		if (it == irc._channels.end())
		{
			client.sendErrMsg(irc._hostname, ERR_NOSUCHCHANNEL, c.at(i));
			continue ;
		}
		std::vector<ft::Client>::iterator it_client = it->second._clients.begin();
		for (; it_client < it->second._clients.end(); ++it_client)
		{
			if (it_client->getNick() == client.getNick())
			{
				it->second._clients.erase(it_client);
				client.sendMsg(std::string(":" + client.getFullId() + " " + msg.command + " " + c.at(i)));
				it->second.sendMsg(std::string(":" + client.getFullId() + " " + msg.command + " " + c.at(i)));
				erased = true;
				break ;
			}
		}
		if (erased == false)
			client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, c.at(i));
	}
}
