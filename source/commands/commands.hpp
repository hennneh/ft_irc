#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "../message/message.hpp"
# include "../client/client.hpp"
# include "../irc.hpp"
# include "../channel/channel.hpp"

namespace ft {
	class IRC;
}
namespace m_channel {
	void op_priv(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
	void prvt(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
	void scrt(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
	void invt(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
	void topic(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
	void clsd(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
	void ban_msk(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
	void speak(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
}

namespace cmd {

	void user(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void motd(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void nick(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void ping(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void privmsg(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void quit(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void welcome(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void pass(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void mode(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void modeUsr(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void join(const ft::Message & msg, ft::Client& client, ft::IRC & irc);

	void reg_ft(ft::IRC & irc, const char opt, ft::IRC::m_channel_ft f)
	{
		irc._c_ft.insert(std::make_pair(opt, f));
	}
	void mk_map(ft::IRC& irc)
	{
		reg_ft(irc, 'o', m_channel::op_priv);
		reg_ft(irc, 'p', m_channel::prvt);
		reg_ft(irc, 's', m_channel::scrt);
		reg_ft(irc, 'i', m_channel::invt);
		reg_ft(irc, 't', m_channel::topic);
		reg_ft(irc, 'n', m_channel::clsd);
		reg_ft(irc, 'b', m_channel::ban_msk);
		reg_ft(irc, 'v', m_channel::speak);
	}
	
}

#endif
