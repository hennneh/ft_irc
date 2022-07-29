#include "client.hpp"

//Constructors
ft::Client::Client(): _pi(false), _raspberry(false) {};
ft::Client::Client(const int& socket, const std::string& nick, const std::string& user, const std::string& full): _pi(false), _raspberry(false)
{
	this->_socket = socket;
	this->_nickname = nick;
	this->_username = user;
	this->_fullname = full;
	this->_operator = false;
}

ft::Client::Client(const Client& client): _pi(client._pi), _raspberry(client._raspberry)
{
	*this = client;
}

//Assignment Operator
ft::Client& ft::Client::operator=(const ft::Client& client)
{
	this->setSocket(client.getSocket());
	this->setFull(client.getFull());
	this->setNick(client.getNick());
	this->setUser(client.getUser());
	this->_socket = client.getSocket();
	this->_fullname = client.getFull();
	this->_nickname = client.getNick();
	this->_username = client.getUser();
	this->_operator = client._operator;
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

void ft::Client::setIp(const struct sockaddr  *addr)
{
	this->_ip = addr->sa_data;
}

void ft::Client::sendmsg(const ft::Message& msg)
{
	std::string msgstr(msg.serialize());
	send(this->getSocket(), (msgstr + "\r\n").c_str(), msgstr.length() + 2, 0);
	std::cout << "Client " << this->getNick() << " sending: '" << msgstr << "\\r\\n'" << std::endl;
}
