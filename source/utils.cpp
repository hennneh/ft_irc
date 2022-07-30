#include "irc.hpp"

bool ft::isStringNumber(const std::string & s) //negatives excluded?
{
	std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int ft::error(const std::string & s)
{
	std::cerr << TXT_RED << s << TXT_NUL << std::endl;
	return (1);
}

int ft::stoi(const std::string & s)
{
	int i;
	std::stringstream stream;
	std::string string = "";
	stream.clear();
	stream << s;
	stream >> i;
	return (i);
}
