#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "irc.hpp"
namespace ft
{
	class Channel
	{
		private:
			std::string _name;
			std::string _password;

		public:
			Channel(const std::string name, const std::string password);
			~Channel();
			void setName(const std::string & name);
			void setPassword(const std::string & password);
			std::string getName(void) const;
			std::string getPassword() const;
			std::vector<ft::Client> _clients;
	}
}

#endif
