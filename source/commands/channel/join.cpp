#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::join(const ft::Message & msg, ft::Client& client, ft::IRC & irc)
{
	if (msg.parameters.empty() || msg.parameters.size() > 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return ;
	}
	std::vector<std::string> channels = ft::split(msg.parameters.at(0), ',');
	std::vector<std::string> passwords;
	if (msg.parameters.size() == 2)
		passwords = ft::split(msg.parameters.at(1), ',');
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels.at(i)[0] != '#' && channels.at(i)[0] != '&')
		{
			client.sendErrMsg(irc._hostname, ERR_NOSUCHCHANNEL, channels.at(i));
			return ;
		}
		ft::IRC::_channel_map::iterator iter = irc._channels.find(channels.at(i));
		if (iter == irc._channels.end())
		{
			std::string pass = "";
			if (i < passwords.size())
				pass = passwords.at(i);
			iter = irc._channels.insert(std::make_pair(channels.at(i), ft::Channel(channels.at(i), pass))).first;
			iter->second._clients.insert(std::make_pair(client.getNick(), ft::ChannelUser(client)));
			ft::Channel::clients_map::iterator citer = iter->second._clients.begin();
			citer->second.op_priv = true;
		}
		else
		{
			for (ft::Channel::uniqString::iterator it = iter->second._ban_list.begin(); it != iter->second._ban_list.end(); it++)
			{
				if (ft::wildcardMatch(*it, client.getFullId()))
				{
					client.sendErrMsg(irc._hostname, ERR_BANNEDFROMCHAN, iter->second._name);
					return ;
				}
			}
			if (iter->second._invitelist.find(client.getNick()) != iter->second._invitelist.end())
			{
				// when invited to a channel the client being invited issues a JOIN which ends here
				// depending on wether we want invites to circumvent bans too change the position of this block
				iter->second._invitelist.erase(client.getNick());
			}
			else if (iter->second._invite_only)
			{
				client.sendErrMsg(irc._hostname, ERR_INVITEONLYCHAN, channels.at(i));
				return ;
			}
			else if (iter->second._password.empty() == false) //If channel password is not empty
			{
				if (i < passwords.size() && passwords.at(i) == iter->second._password)
				{
					client.sendMsg(":" + irc._hostname + " NOTICE " + client.getNick() + " :Channel Key correct");
				}
				else
				{
					client.sendErrMsg(irc._hostname, ERR_BADCHANNELKEY, channels.at(i));
					return ;
				}
			}
			iter->second._clients.insert(std::make_pair(client.getNick(), ft::ChannelUser(client)));
		}
		client.sendMsg(std::string(":" + client.getFullId() + " " + msg.command + " " + channels.at(i)));
		iter->second.sendMsg(std::string(":" + client.getFullId() + " " + msg.command + " " + channels.at(i)));
		cmd::topic(ft::Message(msg.prefix, "TOPIC", channels.at(i)), client, irc);
		cmd::names(ft::Message(msg.prefix, "NAMES", channels.at(i)), client, irc);
	}
}
