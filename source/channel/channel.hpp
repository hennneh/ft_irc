#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../client/client.hpp"

namespace ft
{
	class Channel
	{
		public:
			std::vector<ft::Client> _clients;
			std::string _name;
			std::string _password;

			Channel(const std::string & name, const std::string & password);
			~Channel();
			void setName(const std::string & name);
			void setPassword(const std::string & password);
			std::string getName(void) const;
			std::string getPassword() const;
	};
}

#endif
