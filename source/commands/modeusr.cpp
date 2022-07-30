
#include "commands.hpp"

/*USER FLAGS
[+|-] - Not 100% sure what the differance is
i - marks a users as invisible;
s - marks a user for receipt of server notices;
w - user receives wallops;
o - operator flag.
*/

void modeUsr(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	return ;
}

/*
ERR_NEEDMOREPARAMS		DONE
RPL_CHANNELMODEIS
ERR_CHANOPRIVSNEEDED
ERR_NOSUCHNICK
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