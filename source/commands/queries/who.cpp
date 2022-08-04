#include "../commands.hpp"
#include "../../irc.hpp"

static void send_client_who(ft::Client& client, const std::string& channel, ft::Client target, const std::string& hostname)
{
	std::vector<std::string> args;
	args.push_back(channel);
	args.push_back(target.getUser());
	args.push_back(target.getIp());
	args.push_back(hostname);
	args.push_back(target.getNick());
	args.push_back("H");
	args.push_back("0");
	args.push_back(target.getFull());
	client.sendErrMsg(hostname, RPL_WHOREPLY, args);
}

void cmd::who(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() == 0)
	{
		// Return all users on the server
		for(ft::IRC::connection_map::iterator it = irc._connections.begin(); it != irc._connections.end(); it++)
		{
			send_client_who(client, "*", it->second, irc._hostname);
		}
		client.sendErrMsg(irc._hostname, RPL_ENDOFWHO, msg.parameters.at(0));
		return;
	}
	ft::IRC::_channel_map::iterator it = irc._channels.find(msg.parameters.at(0));
	if (it != irc._channels.end())
	{
		// Send Stuff about channel
		for(ft::Channel::clients_map::iterator clnt = it->second._clients.begin(); clnt != it->second._clients.end(); clnt++)
		{
			send_client_who(client, it->second._name, clnt->second.client, irc._hostname);
		}
		client.sendErrMsg(irc._hostname, RPL_ENDOFWHO, msg.parameters.at(0));
		return;
	}
	ft::IRC::connection_map::iterator clnt = irc._connections.find(msg.parameters.at(0));
	if (clnt != irc._connections.end())
	{
		// Send Stuff about user
		send_client_who(client, "*", clnt->second, irc._hostname);
		client.sendErrMsg(irc._hostname, RPL_ENDOFWHO, msg.parameters.at(0));
		return;
	}
	client.sendErrMsg(irc._hostname, ERR_NOSUCHSERVER, msg.parameters.at(0));
}
