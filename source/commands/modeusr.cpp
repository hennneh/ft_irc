
#include "commands.hpp"

/*USER FLAGS
[+|-] - Not 100% sure what the differance is
i - marks a users as invisible;
s - marks a user for receipt of server notices;
w - user receives wallops;
o - operator flag.
*/

void cmd::modeUsr(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (irc._connections.find(msg.parameters.at(0)) != irc._connections.end())
	{
		// replacement for network-wide ERR_NICKCOLLISION 
		client.sendmsg(ft::Message(":127.0.0.1 401 :No such nick/channel")); //ERR_NOSUCHNICK
		return ;
	}
	return ;
}

/*
ERR_NEEDMOREPARAMS		DONE
RPL_CHANNELMODEIS
ERR_CHANOPRIVSNEEDED
ERR_NOSUCHNICK			DONE
ERR_NOTONCHANNEL
ERR_KEYSET
RPL_BANLIST
RPL_ENDOFBANLIST
ERR_UNKNOWNMODE
ERR_NOSUCHCHANNEL
ERR_USERSDONTMATCH
RPL_UMODEIS
ERR_UMODEUNKNOWNFLAG
*/