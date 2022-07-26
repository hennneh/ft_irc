#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//US INCLUDE
#include "parse/message.hpp"

#define TXT_FAT		"\e[1m"
#define TXT_RED		"\e[31m"
#define TXT_NUL		"\e[0m"

namespace ft
{
	class IRC {
		protected:
			const int			_port;
			const std::string	_password;
			static const int	_buffersize = 1024;
			struct sockaddr_in	_address;
			int					_server;
			std::vector<int>	_connections;

		public:
			IRC(const int& port, const std::string& password);
			~IRC();
			void	run();
	};
	bool isStringNumber(const std::string & s);
	int error(const std::string & s);
	int stoi(const std::string & s);
};

#endif
