#include "commands.hpp"
#include <unistd.h>

void cmd::quit(const ft::Message& msg, ft::Client& client, ft::IRC& irc)
{
	(void)msg;
	close(client.getSocket());
	irc._connections.erase(client.getNick());
	std::cout << "Client " << client.getNick() << " disconnected!" << std::endl;
}
