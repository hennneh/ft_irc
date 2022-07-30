
#include "commands.hpp"
/* CHANNEL FLAGS
[+|-] - Not 100% sure what the differance is
o - give/take channel operator privileges;
p - private channel flag;
s - secret channel flag;
i - invite-only channel flag;
t - topic settable by channel operator only flag;
n - no messages to channel from clients on the outside;
b - set a ban mask to keep users out;
v - give/take the ability to speak on a moderated channel;

NOT DOING?
m - moderated channel;
l - set the user limit to channel;
k - set a channel key (password).
*/


void modeChannel(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{

}

void mode(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() <= 2)
	{
		client.sendmsg(ft::Message(":127.0.0.1 461 :Not enough parameters")); //ERR_NEEDMOREPARAMS
		return ;
	}
	if (msg.parameters[0][0] == '#' || msg.parameters[0][0] == '&')
		modeChannel(msg, client, irc);
	else
		modeUsr(msg, client, irc);
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