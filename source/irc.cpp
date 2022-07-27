#include "irc.hpp"
#include <string>
#include <sstream>

// Constructor
ft::IRC::IRC(const int& port, const std::string& password): _port(port), _password(password) {
	struct protoent		*prtdb;
	int					opt = 1;

	prtdb = getprotobyname("TCP");
	this->_server = socket(PF_INET, SOCK_STREAM, prtdb->p_proto);
	if (this->_server == 0)
		throw std::runtime_error("Could not open socket fd");
	int optreturn = setsockopt(this->_server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (optreturn != 0)
		throw std::runtime_error("Could not set socket options");
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = htonl(INADDR_ANY);
	this->_address.sin_port = htons(this->_port);

	int bindreturn = bind(this->_server, (struct sockaddr*)&(this->_address), sizeof(this->_address));
	if (bindreturn < 0)
		throw std::runtime_error("Could not bind");
	int listenreturn = listen(this->_server, 3);
	if (listenreturn < 0)
		throw std::runtime_error("Could not listen");
	fcntl(this->_server, F_SETFL, O_NONBLOCK);
}

// Destructor
ft::IRC::~IRC() {
	std::cout << TXT_FAT << "Shutting down server" << TXT_NUL << std::endl;
	for(connection_map::iterator it = this->_connections.begin(); it != this->_connections.end(); it++)
	{
		close(it->second.getSocket());
		std::cout << TXT_FAT << "Client " << it->second.getNick() << " disconnected!" << TXT_NUL << std::endl;
	}
	this->_connections.clear();
	shutdown(this->_server, SHUT_RDWR);
}

void	ft::IRC::run() {
	bool	done = false;

	while(!done) {
		int	addrlen = sizeof(this->_address);
		while (true)
		{
			int socket = accept(this->_server, (struct sockaddr*)&(this->_address), (socklen_t*)&addrlen);
			if (socket == -1)
				break;
			std::pair<connection_map::iterator, bool> status = this->_connections.insert(std::make_pair("uniqueid", ft::Client(socket, "", "", "")));
			if (status.second == false)
				std::cout << TXT_RED << "Duplicate Key" << TXT_NUL << std::endl;
			else
				std::cout << TXT_FAT << "Client " << this->_connections.size() - 1 << " connected" << TXT_NUL << std::endl;
		}
		struct pollfd fds[this->_connections.size()];
		size_t i = 0;
		for(connection_map::iterator it = this->_connections.begin(); it != this->_connections.end(); it++, i++)
		{
			fds[i].fd = it->second.getSocket();
			fds[i].events = POLLRDNORM;
		}
		int pollreturn = poll(fds, this->_connections.size(), 0);
		if (pollreturn == -1)
			throw std::runtime_error("Poll failed");
		if (pollreturn == 0) // No ready files
			continue;
		i = 0;
		size_t savesize = this->_connections.size();
		for(connection_map::iterator it = this->_connections.begin(); it != this->_connections.end(); it++, i++)
		{
			if ((fds[i].revents & POLLRDNORM) == 0)
				continue;
			int status = this->__check_client(it->second);
			if (status == 1) {
				this->_connections.erase(it);
				break;
			}
			if (status == 2) {
				done = true;
				break;
			}
			if (savesize != this->_connections.size())
			{
				// The number of connections has changed since starting the loop.
				// For safety (actually avoid segfaults) we stop the loop here
				// and continue on the next iteration
				break;
			}
		}
	}
}

void	ft::IRC::reg_cmd(const std::string& cmd, cmd_func f) {
	this->_commands.insert(std::make_pair(cmd, f));
}

int	ft::IRC::__check_client(ft::Client& client)
{
	char	buffer[this->_buffersize];

	std::cout << TXT_FAT << "Client " << client.getNick() << " has pending data"<< TXT_NUL << std::endl;
	int readval = recv(client.getSocket(), buffer, this->_buffersize, 0);
	if (readval == -1)
		throw std::runtime_error("Reading message failed");
	std::string buf(buffer, readval);
	if (buf.length() == 0) {
		std::cout << TXT_FAT << "Client " << client.getNick() << " connection lost!" << TXT_NUL << std::endl;
		return 1;
	}
	std::vector<ft::Message> all_msg = ft::parse(buf);
	for(std::vector<ft::Message>::iterator msg = all_msg.begin(); msg != all_msg.end(); msg++) {
		std::map<std::string, cmd_func>::iterator cmd_itr = this->_commands.find(msg->command);
		std::cout << TXT_FAT << "Client " << client.getNick() << ": " << TXT_NUL << msg->serialize() << std::endl;
		if (client.getNick().empty() || client.getUser().empty()) {
			if (msg->command != "NICK" && msg->command != "USER" && msg->command != "PASS")
				return 4;
		}
		if (msg->command == "DIE") {
			return 2;
		}
		if (cmd_itr == this->_commands.end()) {
			std::cout << TXT_FAT << "Invalid message" << TXT_NUL << std::endl;
			return 3;
		}
		cmd_itr->second(*msg, client, *this);
	}
	return 0;
}
