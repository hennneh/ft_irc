#include "../commands.hpp"
#include "../../irc.hpp"

void list_names(ft::Channel& chan, ft::Client& client, ft::IRC& irc)
{
	for(ft::Channel::clients_map::iterator itr = chan._clients.begin(); itr != chan._clients.end(); itr++)
	{
		std::vector<std::string> params;
		if (chan._private)
			params.push_back("*");
		else if (chan._secret)
			params.push_back("@");
		else
			params.push_back("=");
		params.push_back(chan._name); // Channel name
		// Has the Client voice rights
		if (itr->second.speak == true)
			params.push_back("+" + itr->second.client.getNick() + " ");
		// Has the Client Operator privileges
		else if (itr->second.op_priv == true)
			params.push_back("@" + itr->second.client.getNick() + " ");
		else
			params.push_back(itr->second.client.getNick() + " ");
		client.sendErrMsg(irc._hostname, RPL_NAMREPLY, params);
	}
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
		// Display for all channels and then all users not on a visible channel
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
		list_names(chan->second, client, irc);
		std::vector<std::string> params;
		params.push_back(*itr);
		params.push_back("End of /NAMES list.");
		client.sendErrMsg(irc._hostname, RPL_ENDOFNAMES, params);
	}
}
