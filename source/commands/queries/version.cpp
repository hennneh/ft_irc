#include "../commands.hpp"
#include "../../irc.hpp"

/*
 * client side may handle this in a weird way as not all RPL
 * are being handled by ADIUM
 */

void cmd::version(const ft::Message & msg, ft::Client & client, ft::IRC & irc)
{
	(void) msg;

	client.sendErrMsg(irc._hostname, RPL_VERSION, VERSION);
}
