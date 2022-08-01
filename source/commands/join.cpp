#include "commands.hpp"

void cmd::join(const ft::Message & msg, ft::Client& client, ft::IRC & irc);
{
	if (msg.parameters.empty() || msg.parameters.size() > 2)
	{
		client.sendErrMsg(ERR_NEEDMOREPARAMS);
		return ;
	}
	std::vector<std::string> channels = ft::split(msg.parameters.at(0), ',');
	std::vector<std::strings> passwords = 0;
	if (msg.parameters.size() == 2)
		passwords = ft::split(msg.parameters.at(1), ',');
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels.at(i)[0] != '#' && channels.at(i)[0] != '&')
		{
			client.sendErrMsg(ERR_NOSUCHCHANNEL);
			return ;
		}
		for (size_t x = 0; x < irc._channels.size(); x ++)
		{
			if (channel.at(i) == irc.channels.at(x)._name)
			{
				if (i < passwords.size())
				{
					if (password.at(i) != irc.channels.at(x)._password)
					{
						client.sendErrMsg(ERR_BADCHANNELKEY);
						return ;
					}
				}
				irc.channels.at(x)._clients.pushback(client);
			}
			if (x == irc._channels.size() - 1)
			{
				std::string pass = "";
				if (i < passwords.size())
					pass = passwords.at(i);
				irc._channels.pushback(ft::Channel(channels.at(i), pass));
			}
		}
	}
}
