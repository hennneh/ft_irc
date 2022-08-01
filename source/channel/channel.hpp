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
			bool _invite_only;
			unsigned int _user_limit;
			bool _moderated;
			std::vector<ft::Client&> _clients;
	}
}

#endif
