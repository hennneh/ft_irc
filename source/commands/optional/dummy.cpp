#include "../commands.hpp"
#include "../../irc.hpp"

void cmd::dummy(const ft::Message & msg, ft::Client & client, ft::IRC & irc)
{
	// the die function is in irc.cpp though for not catching it as unknown command heres this empty one
	(void)msg;
	(void)client;
	(void)irc;
}
