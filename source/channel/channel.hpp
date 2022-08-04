#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../client/client.hpp"
#include <string>
#include <vector>
#include <map>

#define NOT -1

namespace ft
{
	struct ChannelUser
	{
		public:
			bool		op_priv;
			bool		banned;
			bool		speak;
			bool		invis;
			bool		wall;
			bool		snote;
			ft::Client& client;

			ChannelUser(ft::Client& clnt): client(clnt)
			{
				this->op_priv = false;
				this->banned = false;
				this->speak = true;
				this->invis = false;
				this->wall = true;
				this->snote = true;
			}
	};

	class Channel
	{
		public:
			typedef std::map<std::string, ft::ChannelUser>	clients_map;

			std::string		_name;
			std::string		_password;
			std::string		_topic;
			bool			_private;
			bool			_secret;
			bool			_invite_only;
			int				_user_limit;
			bool			_moderated;
			bool			__topic_op;
			bool			_clsd;
			clients_map		_clients;
			std::vector<std::string>	_ban_list;

			Channel(const std::string & name, const std::string & password);
			~Channel();
			void setName(const std::string & name);
			void setPassword(const std::string & password);
			std::string getName(void) const;
			std::string getPassword() const;
			void sendMsg(const ft::Message & msg);
			void sendErrMsg(const std::string& hostname, const std::string& err);
			void sendErrMsg(const std::string& hostname, const std::string& err, const std::string& s);
			void sendErrMsg(const std::string& hostname, const std::string& err, const std::string& s, const std::string& c);
			void sendErrMsg(const std::string& hostname, const std::string& err, std::vector<std::string> args);
	};
}

#endif
