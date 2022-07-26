#include "irc.hpp"
#include <string>
#include <sstream>

void ft_sendmsg(int socketfd, std::string msg) {
	msg = ":127.0.0.1 " + msg;
	send(socketfd, (msg + "\r\n").c_str(), msg.length() + 2, 0);
	std::cout << "Sending: '" << msg << "\\r\\n'" << std::endl;
}

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
	for(size_t j = 0;j < this->_connections.size(); j++) {
		send(this->_connections[j], "bye!\n", 5, 0);
		close(this->_connections[j]);
		std::cout << TXT_FAT << "Client " << j << " disconnected!" << TXT_NUL << std::endl;
	}
	this->_connections.clear();
	shutdown(this->_server, SHUT_RDWR);
}

void	ft::IRC::run() {
	char	buffer[this->_buffersize];
	bool	done = false;

	while(!done) {
		int	addrlen = sizeof(this->_address);
		int socket = accept(this->_server, (struct sockaddr*)&(this->_address), (socklen_t*)&addrlen);
		if (socket != -1) {
			this->_connections.push_back(socket);
			std::cout << TXT_FAT << "Client " << this->_connections.size() - 1 << " connected" << TXT_NUL << std::endl;
		}
		size_t connlen = this->_connections.size();
		struct pollfd fds[connlen];
		for(size_t i = 0; i < connlen; i++) {
			fds[i].fd = this->_connections[i];
			fds[i].events = POLLRDNORM;
		}
		int pollreturn = poll(fds, connlen, 0);
		if (pollreturn == -1)
			throw std::runtime_error("Poll failed");
		if (pollreturn > 0) {
			for(size_t i = 0; i < connlen; i++) {
				if ((fds[i].revents & POLLRDNORM) > 1) {
					std::cout << TXT_FAT << "Client " << i << " has pending data"<< TXT_NUL << std::endl;
					int readval = recv(this->_connections[i], buffer, this->_buffersize, 0);
					if (readval == -1)
						throw std::runtime_error("Reading message failed");
					std::string buf(buffer, readval);
					if (buf.length() == 0) {
						std::cout << TXT_FAT << "Client " << i << " connection lost!" << TXT_NUL << std::endl;
						this->_connections.erase(this->_connections.begin() + i);
						continue;
					}
					buf.replace(std::remove(buf.begin(), buf.end(), '\r'), buf.end(), "\n"); // Change to std::vector<Message>
					std::string msg;
					std::stringstream bufstream(buf);
					while(std::getline(bufstream, msg, '\n')) {
						msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());
						if (msg.length() == 0)
							continue;
						std::cout << TXT_FAT << "Client " << i << ": " << TXT_NUL << msg << std::endl;
						if (msg.compare(0, 4, "NICK") == 0) {
							std::string username(msg.substr(5, msg.length() - 5));
							ft_sendmsg(this->_connections[i], "001 " + username + " :Welcome to the Internet Relay Network " + username + "!*@127.0.0.1");
							ft_sendmsg(this->_connections[i], "002 " + username + " :Your host is 127.0.0.1, running version ft_irc0.1");
							ft_sendmsg(this->_connections[i], "003 " + username + " :This server was created 2022-07-25");
							ft_sendmsg(this->_connections[i], "004 " + username + " 127.0.0.1 ft_irc0.1 iswo opsitnmlbvk");
							ft_sendmsg(this->_connections[i], "375 " + username + " :-- Message of the day --");
							ft_sendmsg(this->_connections[i], "372 " + username + " :-    Hello People!     -");
							ft_sendmsg(this->_connections[i], "376 " + username + " :-- Message of the day --");
							continue;
						}
						if (msg.compare(0, 4, "USER") == 0)
							continue;
						if (msg.compare(0, 4, "PING") == 0) {
							std::string token(msg.substr(5, msg.length() - 5));
							ft_sendmsg(this->_connections[i], "PONG " + token);
							continue;
						}
						if (msg.compare(0, 4, "PONG") == 0)
							continue;
						if (msg.compare(0, 4, "QUIT") == 0) {
							send(this->_connections[i], "bye!\n", 5, 0);
							close(this->_connections[i]);
							std::cout << TXT_FAT << "Client " << i << " disconnected!" << TXT_NUL << std::endl;
							this->_connections.erase(this->_connections.begin() + i);
							break;
						}
						if (msg.compare(0, 8, "SHUTDOWN") == 0) {
							done = true;
							break;
						}
						ft_sendmsg(this->_connections[i], msg);
					}
				}
			}
		}
	}
}
