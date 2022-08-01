#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../client/client.hpp"
#include "../irc.hpp"
#include <string>
#include <vector>

namespace ft
{
	class Channel
	{
		private:

		public:
			Channel(const std::string name, const std::string password);
			~Channel();
			std::string _name;
			std::string _password;
			bool _private;
			bool _secret;
			bool _invite-only;
			unsigned int _user-limit;
			bool _moderated;
			std::vector<ft::client&> _clients;
	}
}

#endif
