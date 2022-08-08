#include "../commands.hpp"
#include "../../irc.hpp"
#include "../../fortune.hpp"
#include <ctime>

void cmd::privmsg(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.empty())
	{
		client.sendErrMsg(irc._hostname, ERR_NORECIPIENT, msg.command);
		return ;
	}
	if (msg.parameters.size() < 2)
	{
		client.sendErrMsg(irc._hostname, ERR_NOTEXTTOSEND);
		return ;
	}
	std::vector<std::string> targets = ft::split(msg.parameters.at(0), ',');
	for (size_t x = 0; x < targets.size(); x ++)
	{
		if (ft::isChannel(targets.at(x)))
		{
			ft::IRC::_channel_map::iterator itr = irc._channels.find(targets.at(x));
			if (itr == irc._channels.end())
			{
				client.sendErrMsg(irc._hostname, ERR_CANNOTSENDTOCHAN, targets.at(x));
				continue;
			}
			if (itr->second._clients.find(client.getNick()) == itr->second._clients.end())
			{
				client.sendErrMsg(irc._hostname, ERR_NOTONCHANNEL, targets.at(x));
				continue;
			}
			std::vector<std::string> params;
			params.push_back(targets.at(x));
			params.insert(params.end(), msg.parameters.begin() + 1, msg.parameters.end());
			ft::Message answer(client.getFullId(), msg.command , params);
			itr->second.sendMsg(answer);
		}
		else
		{
			if (targets.at(x) == "bot")
			{
				std::vector<std::string> params;
				params.push_back(client.getNick());
				if (msg.parameters.at(1) != "!fortune")
					params.push_back("Sorry, I don't know what to answer to that. Try: !fortune");
				else
				{
					time_t	rawtime;
					time(&rawtime);
					params.push_back(fortunes[rawtime % 67]);
				}
				client.sendMsg(ft::Message("bot!bot@" + irc._hostname, msg.command, params));
				continue;
			}
			ft::IRC::connection_map::iterator itr = irc._connections.find(targets.at(x));
			if (itr == irc._connections.end())
			{
				client.sendErrMsg(irc._hostname, ERR_NOSUCHNICK, targets.at(x));
				continue;
			}
			if (!itr->second._awayMsg.empty())
			{
				client.sendErrMsg(itr->second.getFullId(), RPL_AWAY, itr->second.getNick(), itr->second._awayMsg);
				continue;
			}
			std::vector<std::string> params;
			params.push_back(targets.at(x));
			params.insert(params.end(), msg.parameters.begin() + 1, msg.parameters.end());
			ft::Message answer(client.getFullId(), msg.command , params);
			itr->second.sendMsg(answer);
		}
	}
}
