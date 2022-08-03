#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "../message/message.hpp"

namespace ft {
	class Client
	{
		private:
			int			_socket;
			std::string	_nickname;
			std::string	_username;
			std::string	_fullname;
			std::string	_ip;

		public:
			Client();
			Client(const int& socket, const std::string& nick, const std::string& user, const std::string& full);
			Client(const Client& client);
			Client& operator=(const Client& client);
			~Client();

			std::string getNick(void) const;
			std::string getUser(void) const;
			std::string getFull(void) const;
			std::string getFullId(void) const;
			int getSocket(void) const;
			std::string getIp(void) const;
			void setNick(const std::string& nick);
			void setUser(const std::string& user);
			void setFull(const std::string& full);
			void setSocket(const int& socket);
			void setIp(struct sockaddr_in *addr);
			void sendmsg(const ft::Message& msg);
			void sendErrMsg(const std::string& hostname, const std::string& err);

			bool	_pi; //autheticated, Good Nick
			bool	_raspberry; //authorised, Good Pass
			bool	_operator; //standart false should this go here of into channel hpp?
			bool	_invis;	//standart false
			bool	_wall;	//standart true
			bool	_snote;	//standart false
			bool	_here;	//standart true
	};
}

#endif
