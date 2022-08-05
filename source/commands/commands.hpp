#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "../message/message.hpp"
# include "../client/client.hpp"
# include "../channel/channel.hpp"
# include <map>

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
	void moderate(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
	void key(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
	void limit(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
}

namespace m_user {
	void reply(ft::Client& client, ft::IRC& irc, bool sign, std::vector<std::string> args);
	void invis(ft::Client& client, ft::IRC& irc, bool sign, std::vector<std::string> args);
	void servnote(ft::Client& client, ft::IRC& irc, bool sign, std::vector<std::string> args);
	void w_all_op(ft::Client& client, ft::IRC& irc, bool sign, std::vector<std::string> args);
	void operant(ft::Client& client, ft::IRC& irc, bool sign, std::vector<std::string> args);
	void away(ft::Client& client, ft::IRC& irc, bool sign, std::vector<std::string> args);
}

namespace cmd {

	typedef void (*m_channel_ft)(ft::Client& client, ft::IRC& irc, ft::Channel& channel, bool sign, std::vector<std::string> args);
	typedef std::map<char, m_channel_ft>		m_channel_map;

	typedef void (*m_user_ft)(ft::Client& client, ft::IRC& irc, bool sign, std::vector<std::string> args);
	typedef std::map<char, m_user_ft>		m_user_map;

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
	void who(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void notice(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void topic(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void names(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
	void part(const ft::Message & msg, ft::Client & client, ft::IRC & irc);
	void invite(const ft::Message & msg, ft::Client& client, ft::IRC & irc);
	void timer(const ft::Message & msg, ft::Client & client, ft::IRC & irc);
	void oper(const ft::Message & msg, ft::Client & client, ft::IRC & irc);
	void version(const ft::Message & msg, ft::Client & client, ft::IRC & irc);
	void ison(const ft::Message & msg, ft::Client & client, ft::IRC & irc);

	void reg_ft(m_channel_map & _c_ft , const char opt, m_channel_ft f);
	void mk_map(m_channel_map & _c_ft);

	void reg_ft(m_user_map & _u_ft , const char opt, m_user_ft f);
	void mk_map(m_user_map & _u_ft);
}

#endif
