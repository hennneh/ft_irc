#include "client.hpp"
#include <arpa/inet.h>

//Constructors
ft::Client::Client(): _pi(false), _raspberry(false) {};
ft::Client::Client(const int& socket, const std::string& nick, const std::string& user, const std::string& full): _pi(false), _raspberry(false)
{
	this->_socket = socket;
	this->_nickname = nick;
	this->_username = user;
	this->_fullname = full;
	this->_operator = false;
	this->_invis = false;
	this->_wall = true;
	this->_snote = false;
	this->_here = true;
}

ft::Client::Client(const Client& client): _pi(client._pi), _raspberry(client._raspberry)
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
	this->_ip = client.getIp();
	this->_operator = client._operator;
	this->_invis = client._invis;
	this->_wall = client._wall;
	this->_snote = client._snote;
	this->_pi = client._pi;
	this->_raspberry = client._raspberry;
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

std::string ft::Client::getFullId(void) const
{
	return std::string(this->getNick() + "!" + this->getUser() + "@" + this->getIp());
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

void ft::Client::setIp(struct sockaddr_in *addr)
{
	this->_ip = inet_ntoa((struct in_addr)addr->sin_addr);
}

void ft::Client::sendmsg(const ft::Message& msg)
{
	std::string msgstr(msg.serialize());
	send(this->getSocket(), (msgstr + "\r\n").c_str(), msgstr.length() + 2, 0);
	std::cout << "Client " << this->getNick() << " sending: '" << msgstr << "\\r\\n'" << std::endl;
}

/**
 * @brief To send Error Message with no additional arguments
 * 
 * @param hostname IP
 * @param err Error macro
 */
void ft::Client::sendErrMsg(const std::string& hostname, const std::string& err)
{
	std::string msg = ":" + hostname;
	if (err.at(0) != ' ')
		msg += " ";
	msg += err;
	this->sendmsg(msg);
}

/**
 * @brief To send Error Message with one additional argument
 * 
 * @param hostname IP
 * @param err Error macro
 * @param s <channel> / <nickname> / ...
 */
void ft::Client::sendErrMsg(const std::string& hostname, const std::string& err, const std::string& s)
{
	std::string msg = err;

	msg.insert(msg.find('<'), s);
	msg.erase(msg.find('<'), msg.find('>') - msg.find('<') + 1);
	if (err.at(0) != ' ')
		msg = " " + msg;
	msg = ":" + hostname + msg;
	this->sendmsg(msg);
}

/**
 * @brief To send Error Message with two additional argument
 * 
 * @param hostname IP
 * @param err Error macro
 * @param s <channel> / <nickname> / ...
 * @param c <channel> / <nickname> / ...
 */
void ft::Client::sendErrMsg(const std::string& hostname, const std::string& err, const std::string& s, const std::string& c)
{
	std::string msg = err;

	msg.insert(msg.find('<'), s);
	msg.erase(msg.find('<'), msg.find('>') - msg.find('<') + 1);
	msg.insert(msg.find('<'), c);
	msg.erase(msg.find('<'), msg.find('>') - msg.find('<') + 1);
	if (err.at(0) != ' ')
		msg = " " + msg;
	msg = ":" + hostname + msg;
	this->sendmsg(msg);
}
