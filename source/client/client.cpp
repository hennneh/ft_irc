#include "client.hpp"
#include <arpa/inet.h>

//Constructors
ft::Client::Client()
{
	this->__init();
}

ft::Client::Client(const int& socket, const std::string& nick, const std::string& user, const std::string& full)
{
	this->__init();
	this->_socket = socket;
	this->_nickname = nick;
	this->_username = user;
	this->_fullname = full;
}

void ft::Client::__init(void)
{
	this->_socket = 0;
	this->_nickname = "";
	this->_username = "";
	this->_fullname = "";
	this->_ip = "";
	this->_pi = false;
	this->_here = true;
	this->_raspberry = false;
	this->_operator = false;
	this->_invis = false;
	this->_wall = true;
	this->_snote = false;

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

void ft::Client::sendMsg(const ft::Message& msg)
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
	std::string msg = err;
	msg.insert(4, this->getNick() + " ");
	if (err.at(0) != ' ')
		msg = " " + msg;
	msg.insert(0, ":" + hostname);
	this->sendMsg(msg);
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

	msg.insert(4, this->getNick() + " ");
	msg.insert(msg.find('<'), s);
	msg.erase(msg.find('<'), msg.find('>') - msg.find('<') + 1);
	if (err.at(0) != ' ')
		msg = " " + msg;
	msg.insert(0, ":" + hostname);
	this->sendMsg(msg);
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

	msg.insert(4, this->getNick() + " ");
	msg.insert(msg.find('<'), s);
	msg.erase(msg.find('<'), msg.find('>') - msg.find('<') + 1);
	msg.insert(msg.find('<'), c);
	msg.erase(msg.find('<'), msg.find('>') - msg.find('<') + 1);
	if (err.at(0) != ' ')
		msg = " " + msg;
	msg.insert(0, ":" + hostname);
	this->sendMsg(msg);
}

/**
 * @brief To send Error Message with multiple additional arguments
 *
 * @param hostname IP
 * @param err Error macro
 * @param args std::vector<std::string>(<channel> / <nickname> / ...)
 */
void ft::Client::sendErrMsg(const std::string& hostname, const std::string& err, std::vector<std::string> args)
{

	std::string msg = err;

	msg.insert(4, this->getNick() + " ");
	for(std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++)
	{
		size_t pos = msg.find('<');
		if (pos == std::string::npos)
			break;
		msg.insert(pos, *it);
		msg.erase(msg.find('<'), msg.find('>') - msg.find('<') + 1);
	}
	if (err.at(0) != ' ')
		msg = " " + msg;
	msg.insert(0, ":" + hostname);
	this->sendMsg(msg);
}
