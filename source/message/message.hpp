#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <vector>

namespace ft {
	class Message
	{
		public:
			std::string					prefix;
			std::string					command;
			std::vector<std::string>	parameters;

			// Constructors
			Message (const std::string& prefix, const std::string& command, const std::vector<std::string>& parameters);
			Message (const std::string& s);

			void		deserialize(const std::string& s);
			std::string	serialize(void);
	};

	std::vector<Message> parse(std::string s);
}

#endif
