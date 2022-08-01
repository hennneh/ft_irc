#include "commands.hpp"

void cmd::join(const ft::Message & msg, ft::Client& client, ft::IRC & irc)
{
	if (msg.parameters.empty() || msg.parameters.size() > 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS);
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
			client.sendErrMsg(irc._hostname, ERR_NOSUCHCHANNEL);
			return ;
		}
		ft::IRC::_channel_map::iterator iter = irc._channels.find(channels.at(i));
		if (iter == irc._channels.end())
		{
			std::string pass = "";
			if (i < passwords.size())
				pass = passwords.at(i);
			irc._channels.insert(std::make_pair(channels.at(i), ft::Channel(channels.at(i), pass)));
		}
		else
		{
			if (i < passwords.size())
			{
				if (passwords.at(i) != iter->second._password)
				{
						client.sendErrMsg(irc._hostname, ERR_BADCHANNELKEY);
						return ;
				}
			}
			iter->second._clients.push_back(client);
		}
	}
}
