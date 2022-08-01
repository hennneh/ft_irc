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
	typedef void (*m_channel_ft)(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
	typedef std::map<char, m_channel_ft>		m_channel_map;

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
	
	m_channel_map	_c_ft;
	
	void reg_ft(const char opt, m_channel_ft f)
	{
		_c_ft.insert(std::make_pair(opt, f));
	}
	void mk_map(void)
	{
		reg_ft('o', m_channel::op_priv);
		reg_ft('p', m_channel::prvt);
		reg_ft('s', m_channel::scrt);
		reg_ft('i', m_channel::invt);
		reg_ft('t', m_channel::topic);
		reg_ft('n', m_channel::clsd);
		reg_ft('b', m_channel::ban_msk);
		reg_ft('v', m_channel::speak);
	}
	
}

#endif
