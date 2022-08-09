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

std::vector<std::string> ft::split(const std::string & s, char delimiter)
{
	std::vector<std::string> substrings;
	std::string original = s;

	size_t x = 0;
	x = original.find(delimiter);
	substrings.push_back(original.substr(0, x)); //npos prblm ??
	original.erase(0, x + 1);
	while (original.length() != 0 && x != std::string::npos)
	{
		x = original.find(delimiter);
		substrings.push_back(original.substr(0, x));
		original.erase(0, x + 1);
	}
	return (substrings);
}

bool ft::isChannel(const std::string& s)
{
	if (s[0] == '#' || s[0] == '&')
		return true;
	return false;
}

bool ft::wildcardMatch(std::string wildcard, std::string str)
{
	if (wildcard.empty() && str.empty())
		return true;

	if (wildcard.empty())
		return false;

	if (wildcard.at(0) == '*')
	{
		while (wildcard.size() > 1 && wildcard.at(1) == '*')
			wildcard.erase(0, 1);
	}

	if (wildcard == "*")
		return true;

	if (wildcard.at(0) == '*' && wildcard.size() > 1 && str.empty() == true)
		return false;

	std::cout << "Before recursion" << std::endl;
	if (wildcard.at(0) == '?' || wildcard.at(0) == str.at(0))
		return ft::wildcardMatch(wildcard.substr(1), str.substr(1));

	if (wildcard.at(0) == '*')
		return ft::wildcardMatch(wildcard.substr(1), str)
			|| ft::wildcardMatch(wildcard, str.substr(1));
	return false;
}
