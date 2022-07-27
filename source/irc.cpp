#include "irc.hpp"
#include <string>
#include <sstream>

void ft_sendmsg(ft::Client client, ft::Message msg) {
	std::string msgstr(msg.serialize());
	send(client.getSocket(), (msgstr + "\r\n").c_str(), msgstr.length() + 2, 0);
	std::cout << "Sending: '" << msgstr << "\\r\\n'" << std::endl;
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
		close(this->_connections[j].getSocket());
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
			this->_connections.push_back(ft::Client(socket, "", "", ""));
			std::cout << TXT_FAT << "Client " << this->_connections.size() - 1 << " connected" << TXT_NUL << std::endl;
		}
		size_t connlen = this->_connections.size();
		struct pollfd fds[connlen];
		for(size_t i = 0; i < connlen; i++) {
			fds[i].fd = this->_connections[i].getSocket();
			fds[i].events = POLLRDNORM;
		}
		int pollreturn = poll(fds, connlen, 0);
		if (pollreturn == -1)
			throw std::runtime_error("Poll failed");
		if (pollreturn > 0) {
			for(size_t i = 0; i < connlen; i++) {
				if ((fds[i].revents & POLLRDNORM) > 1) {
					std::cout << TXT_FAT << "Client " << i << " has pending data"<< TXT_NUL << std::endl;
					ft::Client& client(this->_connections[i]);
					int readval = recv(client.getSocket(), buffer, this->_buffersize, 0);
					if (readval == -1)
						throw std::runtime_error("Reading message failed");
					std::string buf(buffer, readval);
					if (buf.length() == 0) {
						std::cout << TXT_FAT << "Client " << i << " connection lost!" << TXT_NUL << std::endl;
						this->_connections.erase(this->_connections.begin() + i);
						continue;
					}
					std::vector<ft::Message> all_msg = ft::parse(buf);
					for(std::vector<ft::Message>::iterator it = all_msg.begin(); it != all_msg.end(); it++) {
						std::cout << TXT_FAT << "Client " << i << ": " << TXT_NUL << it->command << std::endl;
						if (it->command == "NICK") {
							client.setNick(it->parameters.at(0));
							ft_sendmsg(client, ":127.0.0.1 001 " + client.getNick() + " :Welcome to the Internet Relay Network " + client.getNick() + "!" + client.getUser() + "@127.0.0.1");
							ft_sendmsg(client, ":127.0.0.1 002 " + client.getNick() + " :Your host is 127.0.0.1, running version ft_irc0.1");
							ft_sendmsg(client, ":127.0.0.1 003 " + client.getNick() + " :This server was created 2022-07-25");
							ft_sendmsg(client, ":127.0.0.1 004 " + client.getNick() + " 127.0.0.1 ft_irc0.1 iswo opsitnmlbvk");
							ft_sendmsg(client, ":127.0.0.1 375 " + client.getNick() + " :-- Message of the day --");
							ft_sendmsg(client, ":127.0.0.1 372 " + client.getNick() + " :-    Hello People!     -");
							ft_sendmsg(client, ":127.0.0.1 376 " + client.getNick() + " :-- Message of the day --");
							continue;
						}
						if (it->command == "USER") {
							if (it->parameters.size() < 4)
								continue;
							std::string username = it->parameters.at(0);
							client.setUser(username);
							std::string realname;
							for(size_t i = 3; i < it->parameters.size(); i++) {
								realname.insert(realname.length(), it->parameters.at(i));
							}
							client.setFull(realname);
							continue;
						}
						if (it->command == "PING") {
							std::string token = it->parameters.at(0);
							ft_sendmsg(client, "PONG " + token);
							continue;
						}
						if (it->command == "PRIVMSG") {
							if (it->parameters.size() < 2)
								continue;
							ft::Client target;
							for (std::vector<ft::Client>::iterator clnt = this->_connections.begin(); clnt != this->_connections.end(); clnt++) {
								if (clnt->getNick() == it->parameters.at(0)) {
									std::cout << "Found target" << std::endl;
									target = *clnt;
									break;
								}
							}
							std::vector<std::string> params;
							params.push_back(target.getNick());
							params.insert(params.end(), it->parameters.begin() + 1, it->parameters.end());
							ft::Message msg(client.getNick() + "!" + client.getUser() + "@127.0.0.1", "PRIVMSG", params);
							ft_sendmsg(target, msg);
							continue;
						}
						if (it->command == "QUIT") {
							close(client.getSocket());
							std::cout << TXT_FAT << "Client " << i << " disconnected!" << TXT_NUL << std::endl;
							this->_connections.erase(this->_connections.begin() + i);
							break;
						}
						if (it->command == "DIE") {
							done = true;
							break;
						}
					}
				}
			}
		}
	}
}
