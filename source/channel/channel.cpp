#include "channel.hpp"

ft::Channel::Channel(const std::string & name, const std::string & password)
{
	this->_name = name;
	this->_password = password;
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
