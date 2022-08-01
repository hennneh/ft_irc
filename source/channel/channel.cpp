#include "channel.hpp"

ft::Channel::Channel(const std::string & name, const std::string & password)
{
	this->_name = name;
	this->_password = password;
	this->_private = false;
	this->_secret = false;
	this->_invite-only = false;
	this->_user-limit = 0;
	this->_moderated = false;
}

ft::Channel::~Channel()
{}
