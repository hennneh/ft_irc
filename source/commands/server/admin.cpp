
#include "../commands.hpp"
#include "../../irc.hpp"


void cmd::admin(const ft::Message & msg, ft::Client & client, ft::IRC & irc)
{
	if (msg.parameters.size() > 1 )
	{
		client.sendErrMsg(irc._hostname, ERR_NOSUCHSERVER);
		return ;
	}
	if (msg.parameters.size() == 1 && msg.parameters.at(0) != irc._hostname)
	{
		client.sendErrMsg(irc._hostname, ERR_NOSUCHSERVER);
		return ;
	}
	client.sendErrMsg(irc._hostname, RPL_ADMINME, irc._hostname);
	client.sendErrMsg(irc._hostname, RPL_ADMINLOC1, "Wolfsburg, Niedersachsen, Germany");
	client.sendErrMsg(irc._hostname, RPL_ADMINLOC2, "42Wolfsburg. TroubleMaker Department");
	client.sendErrMsg(irc._hostname, RPL_ADMINEMAIL, "henneforpresident@gmail.com");
}
