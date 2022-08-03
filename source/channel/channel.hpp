#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../client/client.hpp"
#include <string>
#include <vector>
#include <map>

namespace ft
{
	class Channel
	{
		typedef std::map<std::string, bool> _rights; // map of (nick <-> flag)
		private:

		public:
			std::string				_name;
			std::string				_password;
			bool					_private;
			bool					_secret;
			bool					_invite_only;
			unsigned int			_user_limit;
			bool					_moderated;
			bool					__topic;
			bool					_clsd;
			std::vector<ft::Client>	_clients;
			_rights					op_priv;	//standart false
			_rights					bannd;	//standart false
			_rights					speak;	//standart true
			_rights					invis;	//standart false
			_rights					wall;	//standart true
			_rights					snote;	//standart true

			Channel(const std::string & name, const std::string & password);
			~Channel();
			void setName(const std::string & name);
			void setPassword(const std::string & password);
			std::string getName(void) const;
			std::string getPassword() const;
	};
}

#endif
