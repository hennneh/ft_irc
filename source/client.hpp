#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "irc.hpp"

class Client
{
	public:
		Client();
		~Client();
		std::string getNick(void);
		std::string getUser(void);
		std::string getFull(void);
		void setNick(std::string nick);
		void setUser(std::string user);
		void setFull(std::string full);

	private:
		std::string _nickname;
		std::string _username;
		std::string _fullname;
};

#endif
