#include "client.hpp"
#include <string>

//Constructors
ft::Client::Client() {};
ft::Client::Client(const int& socket, const std::string& nick, const std::string& user, const std::string& full)
{
	this->_socket = socket;
	this->_nickname = nick;
	this->_username = user;
	this->_fullname = full;
}

ft::Client::Client(const Client& client)
{
	*this = client;
}

//Assignment Operator
ft::Client& ft::Client::operator=(const ft::Client& client)
{
	this->_socket = client.getSocket();
	this->_fullname = client.getFull();
	this->_nickname = client.getNick();
	this->_username = client.getUser();
	return *this;
}

//Destructor
ft::Client::~Client() {};

//Getters
std::string	ft::Client::getNick(void) const
{
	return this->_nickname;
}

std::string	ft::Client::getUser(void) const
{
	return this->_username;
}

std::string	ft::Client::getFull(void) const
{
	return this->_fullname;
}

int	ft::Client::getSocket(void) const
{
	return this->_socket;
}

std::string ft::Client::getIp(void) const
{
	return this->_ip;
}

//Setters
void	ft::Client::setNick(const std::string& nick)
{
	this->_nickname = nick;
}

void	ft::Client::setUser(const std::string& user)
{
	this->_username = user;
}

void	ft::Client::setFull(const std::string& full)
{
	this->_fullname = full;
}

void	ft::Client::setSocket(const int& socket)
{
	this->_socket = socket;
}

void ft::Client::setIp(const struct sockaddr  *restrict & addr)
{
	this->_ip = addr.sa_data;
}
