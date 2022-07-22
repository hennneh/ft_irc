#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

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
	int socket = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
	if (socket < 0)
		error("Could not accept");
	int valread = read(socket, buffer, 1024);
	std::cout << "BUFFER: " << buffer << ", size: " << valread << std::endl;
	send(socket, buffer, valread, 0);
	close(socket);
	shutdown(sockfd, SHUT_RDWR);
	return (0);
}
