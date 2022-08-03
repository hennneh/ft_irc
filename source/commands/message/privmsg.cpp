#include "../commands.hpp"
#include "../../irc.hpp"

template<typename T>
bool sendToTarget(typename std::map<std::string, T> container, const std::string& identifier, const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)irc;
	typename std::map<std::string, T>::iterator itr = container.find(identifier);
	if (itr == container.end())
	{
		return false;
	}
	T target(itr->second);
	std::vector<std::string> params;
	params.push_back(identifier);
	params.insert(params.end(), msg.parameters.begin() + 1, msg.parameters.end());
	ft::Message answer(client.getFullId(), msg.command , params);
	target.sendMsg(answer);
	return true;
}

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
	std::vector<std::string> _targets = ft::split(msg.parameters.at(0), ',');
	for (size_t x = 0; x < _targets.size(); x ++)
	{
		
		ft::Client target;
		if (ft::isChannel(_targets.at(x)))
		{
			if (!sendToTarget<ft::Channel>(irc._channels, _targets.at(x), msg, client, irc))
			{
				client.sendErrMsg(irc._hostname, ERR_CANNOTSENDTOCHAN, _targets.at(x));
				return ;
			}
		}
		else
		{
			if (!sendToTarget<ft::Client>(irc._connections, _targets.at(x), msg, client, irc))
			{
				client.sendErrMsg(irc._hostname, ERR_NOSUCHNICK, _targets.at(x));
				return ;
			}
		}
	}
}



// if (msg.parameters.size() > 2)
	// {
	// 	client.sendErrMsg(irc._hostname, ERR_TOOMANYTARGETS, msg.parameters.at(1));
	// 	return ;
	// }
