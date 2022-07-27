#include "message.hpp"

std::vector<ft::Message> ft::parse(std::string s)
{
	size_t x = 0;
	size_t y = 0;
	std::vector<ft::Message> v;

	while (x < s.length())
	{
		if (s[x] == '\r' || s[x] == '\n')
		{
			if (x == 0)
			{
				y = ++ x;
				continue;
			}
			v.push_back(ft::Message(s.substr(y, x - y)));
			x ++;
			if (x < s.length() && s[x - 1] == '\r' && s[x] == '\n')
				x ++;
			y = x;
		}
		else
			x ++;
	}
	if (y != s.length())
		v.push_back(ft::Message(s.substr(y, x - y)));
	return (v);
}

ft::Message::Message(void) {}

ft::Message::Message (const std::string& prefix, const std::string& command, const std::vector<std::string>& parameters)
{
	this->prefix = prefix;
	this->command = command;
	this->parameters = parameters;
}

ft::Message::Message (const std::string& s)
{
	this->deserialize(s);
}

void ft::Message::deserialize(const std::string& s)
{
	std::string msg(s);
	size_t x = 0;
	if (s[0] == ':')
	{
		x = msg.find(' ');
		this->prefix = msg.substr(1, x - 1);
		msg.erase(0, x + 1);
	}
	x = msg.find(' ');
	this->command = msg.substr(0, x);
	msg.erase(0, x + 1);
	while (x != std::string::npos)
	{
		if (msg.at(0) == ':') {
			this->parameters.push_back(msg.substr(1));
			break;
		}
		x = msg.find(' ');
		this->parameters.push_back(msg.substr(0, x));
		msg.erase(0, x + 1);
	}
}

std::string ft::Message::serialize(void) const
{
	std::string msg;

	if (!this->prefix.empty()) {
		msg.append(":");
		msg.append(this->prefix);
		msg.append(" ");
	}
	msg.append(this->command);
	if (this->parameters.empty())
		return msg;
	for(std::vector<std::string>::const_iterator it = this->parameters.begin(); it != this->parameters.end(); it++) {
		msg.append(" ");
		if (it->find(' ') != std::string::npos) {
			msg.append(":");
		}
		msg.append(*it);
	}
	return msg;
}

