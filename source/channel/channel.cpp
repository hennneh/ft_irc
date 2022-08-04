#include "channel.hpp"

ft::Channel::Channel(const std::string & name, const std::string & password)
{
	this->_name = name;
	this->_password = password;
	this->_topic = "";
	this->_private = false;
	this->_secret = false;
	this->_invite_only = false;
	this->_user_limit = 0;
	this->_moderated = false;
	this->__topic_op = false;
	this->_clsd = false;
}

ft::Channel::~Channel()
{}

void ft::Channel::setName(const std::string & name)
{
	this->_name = name;
}

void ft::Channel::setPassword(const std::string & password)
{
	this->_password = password;
}

std::string ft::Channel::getName(void) const
{
	return (this->_name);
}

std::string ft::Channel::getPassword(void) const
{
	return (this->_password);
}

void ft::Channel::sendMsg(const ft::Message & msg)
{
	for (clients_map::iterator nbr = this->_clients.begin(); nbr != this->_clients.end(); ++nbr)
	{
		if (nbr->second.client.getFullId() == msg.prefix)
			continue;
		nbr->second.client.sendMsg(msg);
	}
}

/**
 * @brief To send Error Message with no additional arguments
 *
 * @param hostname IP
 * @param err Error macro
 */
void ft::Channel::sendErrMsg(const std::string& hostname, const std::string& err)
{
	for (clients_map::iterator nbr = this->_clients.begin(); nbr != this->_clients.end(); ++nbr)
	{
		nbr->second.client.sendErrMsg(hostname, err);
	}
}

/**
 * @brief To send Error Message with one additional argument
 *
 * @param hostname IP
 * @param err Error macro
 * @param s <channel> / <nickname> / ...
 */
void ft::Channel::sendErrMsg(const std::string& hostname, const std::string& err, const std::string& s)
{
	for (clients_map::iterator nbr = this->_clients.begin(); nbr != this->_clients.end(); ++nbr)
	{
		nbr->second.client.sendErrMsg(hostname, err, s);
	}
}

/**
 * @brief To send Error Message with two additional argument
 *
 * @param hostname IP
 * @param err Error macro
 * @param s <channel> / <nickname> / ...
 * @param c <channel> / <nickname> / ...
 */
void ft::Channel::sendErrMsg(const std::string& hostname, const std::string& err, const std::string& s, const std::string& c)
{
	for (clients_map::iterator nbr = this->_clients.begin(); nbr != this->_clients.end(); ++nbr)
	{
		nbr->second.client.sendErrMsg(hostname, err, s, c);
	}
}

/**
 * @brief To send Error Message with multiple additional arguments
 *
 * @param hostname IP
 * @param err Error macro
 * @param args std::vector<std::string>(<channel> / <nickname> / ...)
 */
void ft::Channel::sendErrMsg(const std::string& hostname, const std::string& err, std::vector<std::string> args)
{
	for (clients_map::iterator nbr = this->_clients.begin(); nbr != this->_clients.end(); ++nbr)
	{
		nbr->second.client.sendErrMsg(hostname, err, args);
	}
}