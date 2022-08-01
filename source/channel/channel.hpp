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
			std::vector<ft::Client> _clients;
			std::string _name;
			std::string _password;
			bool _private;
			bool _secret;
			bool _invite_only;
			unsigned int _user_limit;
			bool _moderated;
			std::vector<ft::Client&> _clients;

			Channel(const std::string & name, const std::string & password);
			~Channel();
			void setName(const std::string & name);
			void setPassword(const std::string & password);
			std::string getName(void) const;
			std::string getPassword() const;
	};
}

#endif
