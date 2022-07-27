#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "../message/message.hpp"
# include "../client/client.hpp"
# include "../irc.hpp"

namespace ft {
	class IRC;
}

namespace cmd {
	void user(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void motd(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void nick(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void ping(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void privmsg(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void quit(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void welcome(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
}

#endif
