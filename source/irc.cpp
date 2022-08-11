#include "irc.hpp"
#include "error.hpp"
#include <string>
#include <sstream>

// Constructor
ft::IRC::IRC(const int& port, const std::string& password): _port(port), _password(password) {
	struct protoent		*prtdb;
	int					opt = 1;

	this->_version = "ft_irc0.1";
	this->_motd = "Hello People!";
	this->_op_password = "vinnysucks";

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

	char hstnme[256]; // 255 is maxlen for hostname according to manpages
	gethostname(hstnme, 256);
	this->_hostname = std::string(hstnme);
	std::cout << "IRC Server running on " << this->_hostname;
	std::cout << " on port " << this->_port;
	if (!this->_password.empty())
		std::cout << " with password authentication enabled";
	std::cout << std::endl;
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
	close(this->_server);
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
			ft::Client client(socket, "", "", "");
			client.setIp(&(this->_address));
			client._raspberry = this->_password.empty(); // If no password for server, clients don't need to send PASS
			std::pair<connection_map::iterator, bool> status = this->_connections.insert(std::make_pair(client.getIp() + ft::itos(client.getSocket()), client));
			if (status.second == false)
				std::cout << TXT_RED << "Duplicate Key" << TXT_NUL << std::endl;
			else
				std::cout << TXT_FAT << "Client " << this->_connections.size() - 1 << " connected from " << client.getIp() << TXT_NUL << std::endl;
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
		this->_breakloop = false;
		for(connection_map::iterator it = this->_connections.begin(); it != this->_connections.end(); it++, i++)
		{
			if ((fds[i].revents & POLLRDNORM) == 0)
				continue;
			int status = this->__check_client(it->second);
			if (status == 2) {
				done = true;
				break;
			}
			if (this->_breakloop)
				break;
		}
	}
}

const std::string ft::IRC::getPass( void ) const
{
	return (this->_password);
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
	if (buf.length() == 0)
	{
		// Send quit on behalf of the lost client
		cmd::quit(ft::Message("", "QUIT", "Client connection lost!"), client, *this);
		return 1;
	}
	client._recvbuffer += buf;
	size_t end = client._recvbuffer.find_last_of("\r\n");
	if (end == std::string::npos)
	{
		std::cout << TXT_FAT << "Couldn't find \\r\\n, storing partial for later" << TXT_NUL << std::endl;
		return 6;
	}
	else
	{
		std::cout << TXT_FAT << "Got everything for a new message, continuing" << TXT_NUL << std::endl;
		buf = client._recvbuffer.substr(0, end);
		client._recvbuffer.erase(0, end);
	}
	std::vector<ft::Message> all_msg = ft::parse(buf);
	for(std::vector<ft::Message>::iterator msg = all_msg.begin(); msg != all_msg.end(); msg++) {
		std::map<std::string, cmd_func>::iterator cmd_itr = this->_commands.find(msg->command);
		std::cout << TXT_FAT << "Client " << client.getNick() << ": " << TXT_NUL << msg->serialize() << std::endl;
		// TODO maybe implement the correct client return values
		if (msg->command == "QUIT")
		{
			// Client can always Quit
			cmd::quit(*msg, client, *this);
			return 4;
		}
		if ((!client._raspberry) && msg->command != "PASS")
		{
			// Until Client has correct password, can't do anything else
			std::cout << "CMD is not PASS" << std::endl;
			client.sendErrMsg(this->_hostname, ERR_NOTREGISTERED);
			return 4;
		}
		if (client._raspberry && (!client._pi) && msg->command != "NICK" && msg->command != "USER")
		{
			// Until Client has sent NICK/USER, can't do anything else
			std::cout << "CMD is not NICK/USER" << std::endl;
			client.sendErrMsg(this->_hostname, ERR_NOTREGISTERED);
			return 4;
		}
		if (msg->command == "DIE" && client._operator == true)
		{
			//Kill the server
			return 2;
		}
		if (cmd_itr == this->_commands.end())
		{
			// Haven't found command
			client.sendErrMsg(this->_hostname, ERR_UNKNOWNCOMMAND, msg->command);
			return 3;
		}
		cmd_itr->second(*msg, client, *this);
	}
	return 0;
}
