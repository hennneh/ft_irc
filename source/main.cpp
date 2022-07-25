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

#define TXT_FAT		"\e[1m"
#define TXT_RED		"\e[31m"
#define TXT_NUL		"\e[0m"

#define BUFFERSIZE	4
#define PORT		8080

void error(const std::string& msg) {
	std::cout << TXT_FAT << TXT_RED << "ERROR: " << msg << std::endl;
	perror("");
	std::cout << TXT_NUL;
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int					opt = 1;
	struct sockaddr_in	address;
	struct protoent		*prtdb;
	char				buffer[BUFFERSIZE] = { 0 };
	int					addrlen = sizeof(address);
	bool				done = false;

	prtdb = getprotobyname("TCP");

	std::cout << "Protocol: " << prtdb->p_name << " (" << prtdb->p_proto << ")" << std::endl;
	int sockfd = socket(PF_INET, SOCK_STREAM, prtdb->p_proto);
	if (sockfd == 0)
		error("Could not open socket fd");
	int optreturn = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (optreturn != 0)
		error("Could not set socket options");
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);

	int bindreturn = bind(sockfd, (struct sockaddr*)&address, sizeof(address));
	if (bindreturn < 0)
		error("Could not bind");
	int listenreturn = listen(sockfd, 3);
	if (listenreturn < 0)
		error("Could not listen");
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
	std::vector<int> connections;
	while(!done) {
		int socket = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
		if (socket != -1) {
			connections.push_back(socket);
			std::cout << TXT_FAT << "Client " << connections.size() - 1 << " connected" << TXT_NUL << std::endl;
		}
		size_t connlen = connections.size();
		struct pollfd fds[connlen];
		for(size_t i = 0; i < connlen; i++) {
			fds[i].fd = connections[i];
			fds[i].events = POLLRDNORM;
		}
		int pollreturn = poll(fds, connlen, 0);
		if (pollreturn == -1)
			error("Poll failed");
		if (pollreturn > 0) {
			for(size_t i = 0; i < connlen; i++) {
				if ((fds[i].revents & POLLRDNORM) > 1) {
					std::cout << TXT_FAT << "Client " << i << " has pending data"<< TXT_NUL << std::endl;
					std::string buf;
					while(1) {
						int readval = recv(connections[i], buffer, BUFFERSIZE, 0);
						if (readval == -1)
							error("Reading message failed");
						buf.insert(buf.length(), std::string(buffer));
						memset(buffer, 0, BUFFERSIZE);
						if (readval < BUFFERSIZE || readval == 0) {
							break;
						}
						if (readval == BUFFERSIZE && buf.length() > 0 && buf.at(buf.length() - 1) == '\n')
							break;
					}
					if (buf.length() == 0) {
						std::cout << TXT_FAT << "Client " << i << " connection lost!" << TXT_NUL << std::endl;
						connections.erase(connections.begin() + i);
						continue;
					}
					buf.erase(std::remove(buf.begin(), buf.end(), '\r'), buf.end());
					buf.erase(std::remove(buf.begin(), buf.end(), '\n'), buf.end());
					if (buf == "QUIT") {
						send(connections[i], "bye!\n", 5, 0);
						close(connections[i]);
						std::cout << TXT_FAT << "Client " << i << " disconnected!" << TXT_NUL << std::endl;
						connections.erase(connections.begin() + i);
						continue;
					}
					if (buf == "SHUTDOWN") {
						std::cout << TXT_FAT << "Shutting down server" << TXT_NUL << std::endl;
						for(size_t j = 0;j < connections.size(); j++) {
							send(connections[j], "bye!\n", 5, 0);
							close(connections[j]);
							std::cout << TXT_FAT << "Client " << j << " disconnected!" << TXT_NUL << std::endl;
						}
						done = true;
						connections.clear();
						continue;
					}
					std::cout << TXT_FAT << "Client " << i << ": " << TXT_NUL << buf << std::endl;
					send(connections[i], (buf + "\n").c_str(), buf.length() + 1, 0);
				}
			}
		}
	}
	shutdown(sockfd, SHUT_RDWR);
	return (0);
}
