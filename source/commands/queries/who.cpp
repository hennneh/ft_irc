#include "../commands.hpp"
#include "../../irc.hpp"

static void send_client_who(const std::string& channel, ft::Client client, const std::string& hostname)
{
	std::vector<std::string> args;
	args.push_back(client.getNick());
	args.push_back(channel);
	args.push_back(client.getUser());
	args.push_back(client.getIp());
	args.push_back(hostname);
	args.push_back(client.getNick());
	args.push_back("H");
	args.push_back("1 " + client.getFull());
	client.sendmsg(ft::Message(hostname, "352", args));
}

void cmd::who(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() == 0)
	{
		// Return all users on the server
		for(ft::IRC::connection_map::iterator it = irc._connections.begin(); it != irc._connections.end(); it++)
		{
			send_client_who("*", it->second, irc._hostname);
		}
		client.sendmsg(":" + irc._hostname + " 315 " + client.getNick() + " :End of WHO list");
		return;
	}
	ft::IRC::_channel_map::iterator it = irc._channels.find(msg.parameters.at(0));
	if (it != irc._channels.end())
	{
		// Send Stuff about channel
		for(std::vector<ft::Client>::iterator clnt = it->second._clients.begin(); clnt != it->second._clients.end(); clnt++)
		{
			send_client_who(it->first, *clnt, irc._hostname);
		}
		client.sendmsg(":" + irc._hostname + " 315 " + client.getNick() + " " + msg.parameters.at(0) + " :End of WHO list");
		return;
	}
	ft::IRC::connection_map::iterator clnt = irc._connections.find(msg.parameters.at(0));
	if (clnt != irc._connections.end())
	{
		// Send Stuff about user
		send_client_who("*", clnt->second, irc._hostname);
		client.sendmsg(":" + irc._hostname + " 315 " + client.getNick() + " " + msg.parameters.at(0) + " :End of WHO list");
		return;
	}
	client.sendErrMsg(irc._hostname, ERR_NOSUCHSERVER, msg.parameters.at(0));
}
