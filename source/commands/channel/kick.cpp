#include "../commands.hpp"
#include "../../irc.hpp"
/*
Command: KICK
Parameters: < channel > < user > [< comment >]
*/
void cmd::kick(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	if (msg.parameters.size() < 2 || msg.parameters.size() > 3)
	{
		client.sendErrMsg(irc._hostname, ERR_NEEDMOREPARAMS, msg.command);
		return;
	}
	std::vector<std::string> _v_chnl = ft::split(msg.parameters.at(0), ',');
	std::vector<std::string> _v_usr = ft::split(msg.parameters.at(1), ',');
	return ;
}

/*
ERR_NEEDMOREPARAMS
ERR_NOSUCHCHANNEL
ERR_BADCHANMASK
ERR_CHANOPRIVSNEEDED
           ERR_NOTONCHANNEL
		   */