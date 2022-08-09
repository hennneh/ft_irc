#include "../commands.hpp"
#include "../../irc.hpp"

std::string list_names(const ft::ChannelUser& target, const ft::Channel& chan, ft::Client& client, ft::IRC& irc)
{
	if (target.client.getNick() != client.getNick())
	{
		// Don't display if user on channel or server invis
		if (target.invis || target.client._invis)
			return "";
	}
	std::vector<std::string> params;
	if (chan._private)
		params.push_back("*");
	else if (chan._secret)
		params.push_back("@");
	else
		params.push_back("=");
	params.push_back(chan._name); // Channel name
	// Has the Client Operator privileges
	if (target.op_priv == true)
		params.push_back("@" + target.client.getNick() + " ");
	// Has the Client voice rights
	else if (target.speak == true)
		params.push_back("+" + target.client.getNick() + " ");
	else
		params.push_back(target.client.getNick() + " ");
	client.sendErrMsg(irc._hostname, RPL_NAMREPLY, params);
	return target.client.getNick();
}

void cmd::names(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() > 1)
	{
		// Not officially in the RFC
		client.sendErrMsg(irc._hostname, ERR_TOOMANYCHANNELS);
	}
	if (msg.parameters.size() == 0)
	{
		std::set<std::string> usersIveSeen;
		for (ft::IRC::_channel_map::iterator chan = irc._channels.begin(); chan != irc._channels.end(); chan++)
		{
			if (chan->second._private || chan->second._secret)
			{
				// Secret or private and client not on channel prints nothing
				if (chan->second._clients.find(client.getNick()) == chan->second._clients.end())
					continue;
			}
			for (ft::Channel::clients_map::iterator cclnt = chan->second._clients.begin(); cclnt != chan->second._clients.end(); cclnt++)
			{
				usersIveSeen.insert(list_names(cclnt->second, chan->second, client, irc));
			}
		}
		for (ft::IRC::connection_map::iterator clnt = irc._connections.begin(); clnt != irc._connections.end(); clnt++)
		{
			if (usersIveSeen.find(clnt->second.getNick()) == usersIveSeen.end())
			{
				if (clnt->second._invis && clnt->second.getNick() != client.getNick())
					continue;
				// If we haven't seen the user yet
				std::vector<std::string> params;
				params.push_back("=");
				params.push_back("*");
				params.push_back(clnt->second.getNick() + " ");
				client.sendErrMsg(irc._hostname, RPL_NAMREPLY, params);
			}
		}
		return;
	}
	std::vector<std::string> channels = ft::split(msg.parameters.at(0), ',');
	for (std::vector<std::string>::iterator itr = channels.begin(); itr != channels.end(); itr++)
	{
		ft::IRC::_channel_map::iterator chan = irc._channels.find(*itr);
		if (chan == irc._channels.end())
		{
			client.sendErrMsg(irc._hostname, ERR_NOSUCHCHANNEL, *itr);
			return;
		}
		if (chan->second._private || chan->second._secret)
		{
			// Secret or private and client not on channel prints nothing
			if (chan->second._clients.find(client.getNick()) == chan->second._clients.end())
				continue;
		}
		for(ft::Channel::clients_map::iterator itr = chan->second._clients.begin(); itr != chan->second._clients.end(); itr++)
		{
			list_names(itr->second, chan->second, client, irc);
		}
		std::vector<std::string> params;
		params.push_back(*itr);
		params.push_back("End of /NAMES list.");
		client.sendErrMsg(irc._hostname, RPL_ENDOFNAMES, params);
	}
}
