#include "channel.hpp"

ft::Channel::Channel(const std::string & name, const std::string & password)
{
	this->_name = name;
	this->_password = password;
	this->_private = false;
	this->_secret = false;
	this->_invite_only = false;
	this->_user_limit = 0;
	this->_moderated = false;
	this->__topic = false;
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
	for (std::vector<ft::Client> nbr = this->_clients.begin(); nbr != this->_clients.end(); ++nbr)
	{
		nbr->sendMsg(msg);
	}
}
