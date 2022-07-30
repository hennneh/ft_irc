#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
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
#include "message/message.hpp"
#include "client/client.hpp"
#include "commands/commands.hpp"
#include "channel/channel.hpp"

#define TXT_FAT		"\e[1m"
#define TXT_RED		"\e[31m"
#define TXT_NUL		"\e[0m"

namespace ft
{
	class IRC {
		public:
			typedef void (*cmd_func)(const ft::Message& msg, ft::Client& client, ft::IRC& irc);
			typedef std::map<std::string, ft::Client>	connection_map;
			typedef std::map<std::string, cmd_func>		commands_map;

		protected:
			const int			_port;
			const std::string	_password;
			static const int	_buffersize = 1024;
			struct sockaddr_in	_address;
			int					_server;
			commands_map		_commands;

		public:
			connection_map		_connections;
			bool				_breakloop;

			IRC(const int& port, const std::string& password);
			~IRC();
			void	run();
			void	reg_cmd(const std::string& cmd, cmd_func);
			const std::string getPass( void ) const;

		private:
			int		__check_client(ft::Client& client);
	};
	bool isStringNumber(const std::string & s);
	int error(const std::string & s);
	int stoi(const std::string & s);
	bool ft::isAlpha(char c);
	bool ft::isNumeric(char c);
	bool ft::isAlphaNumeric(char c);
	bool ft::isNonWhite(char c);
};

#endif
