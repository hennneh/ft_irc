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
		for (size_t x = 0; x < irc._channels.size(); x ++)
		{
			if (channels.at(i) == irc._channels.at(x)._name)
			{
				if (i < passwords.size())
				{
					if (passwords.at(i) != irc._channels.at(x)._password)
					{
						client.sendErrMsg(irc._hostname, ERR_BADCHANNELKEY);
						return ;
					}
				}
				irc._channels.at(x)._clients.push_back(client);
			}
			if (x == irc._channels.size() - 1)
			{
				std::string pass = "";
				if (i < passwords.size())
					pass = passwords.at(i);
				irc._channels.push_back(ft::Channel(channels.at(i), pass));
			}
		}
	}
}
