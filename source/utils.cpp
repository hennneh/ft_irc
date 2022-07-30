#include "irc.hpp"

bool ft::isStringNumber(const std::string & s)
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

bool ft::isAlpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (true);
	return (false);
}

bool ft::isNumeric(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool ft::isAlphaNumeric(char c)
{
	if (ft::isAlpha(c) || ft::isNumeric(c))
		return (true);
	return (false);
}

#define SPACE ' '
#define NUL '\0'
#define CR '\r'
#define LF '\n'

bool ft::isNonWhite(char c)
{
	if (c == SPACE)
		return (false);
	if (c == NUL)
		return (false);
	if (c == CR)
		return (false);
	if (c == LF)
		return (false);
	return (true);
}