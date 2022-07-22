#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

void error(const std::string& msg) {
	std::cout << "ERROR: " << msg << std::endl;
	perror("");
	exit(1);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int opt = 1;
	struct sockaddr_in address;
	struct protoent *prtdb;
	char buffer[1024] = { 0 };
	int addrlen = sizeof(address);

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
	address.sin_port = htons(8080);

	int bindreturn = bind(sockfd, (struct sockaddr*)&address, sizeof(address));
	if (bindreturn < 0)
		error("Could not bind");
	int listenreturn = listen(sockfd, 3);
	if (listenreturn < 0)
		error("Could not listen");
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
	std::vector<int> connections;
	while(1) {
		int socket = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
		if (socket != -1) {
			connections.push_back(socket);
			std::cout << "Client connected" << std::endl;
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
			std::cout << "Some files are ready" << std::endl;
			for(size_t i = 0; i < connlen; i++) {
				std::cout << "Checking file " << i << std::endl;
				if ((fds[i].revents & POLLRDNORM) > 1) {
					std::cout << "Reading..." << std::endl;
					int valread = read(connections[i], buffer, 1024);
					std::cout << "BUFFER: " << buffer << ", size: " << valread << std::endl;
					if (valread == 0) {
						std::cout << "Client connection lost!" << std::endl;
						connections.erase(connections.begin() + i);
					}
					std::string buf(buffer);
					send(connections[i], buffer, valread, 0);
					if (buf.find("QUIT") != std::string::npos) {
						send(connections[i], "bye!\n", 5, 0);
						close(connections[i]);
						std::cout << "Client disconnected!" << std::endl;
						connections.erase(connections.begin() + i);
					}
				}
			}
		}
	}
	shutdown(sockfd, SHUT_RDWR);
	return (0);
}
