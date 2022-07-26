#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <vector>

class Message
{
	public:

		Message (std::string s)
		{
			size_t x = 0;
			if (s[0] == ':')
			{
				x = s.find(' ');
				this->prefix = s.substr(1, x - 1);
				s.erase(0, x + 1);
			}
			x = s.find(' ');
			this->command = s.substr(0, x);
			s.erase(0, x + 1);
			while (x != std::string::npos)
			{
				x = s.find(' ');
				this->parameters.push_back(s.substr(0, x));
				s.erase(0, x + 1);
			}
		}
		std::string					prefix;
		std::string					command;
		std::vector<std::string>	parameters;
};

#endif
