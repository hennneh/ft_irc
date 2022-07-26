#include "message.h"

std::vector<Message> parse(std::string s)
{
	size_t x = 0;
	size_t y = 0;
	std::vector<Message> v;

	while (x < s.length())
	{
		if (s[x] == '\r' || s[x] == '\n')
		{
			if (x == 0)
			{
				y = ++ x;
				continue;
			}
			v.push_back(Message(s.substr(y, x - y)));
			x ++;
			if (x < s.length() && s[x - 1] == '\r' && s[x] == '\n')
				x ++;
			y = x;
		}
		else
			x ++;
	}
	if (y != s.length())
		v.push_back(Message(s.substr(y, x - y)));
	return (v);
}

// int main(void)
// {
// 	std::string s = ":12345 PRIVMESG hello Vincent\r\nPRIVMSG hello Pete\r";
// 	std::vector<Message> m = parse(s);
// 	std::vector<Message>::iterator it_m = m.begin();
// 	int i = 1;
// 	while (it_m != m.end())
// 	{
// 		std::cout << "# " << i << "\nprefix :" << it_m->prefix << std::endl << "command :" << it_m->command << std::endl;
// 		for (std::vector<std::string>::iterator it_s = it_m->parameters.begin(); it_s != it_m->parameters.end(); it_s ++)
// 			std::cout << "parameter : " << *it_s << std::endl;
// 		std::cout << std::endl;
// 		i ++;
// 		it_m++;
// 	}
// 	return (0);
// }