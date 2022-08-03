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
#include "error.hpp"
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
			typedef std::map<std::string, ft::Channel>	_channel_map;

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
			_channel_map		_channels;
			cmd::m_channel_map	_c_ft;
			cmd::m_user_map		_u_ft;
			std::string			_hostname;

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
	bool isAlpha(char c);
	bool isNumeric(char c);
	bool isAlphaNumeric(char c);
	bool isNonWhite(char c);
	std::vector<std::string> split(const std::string & s, char);
	bool isChannel(const std::string& s);
};

#endif
