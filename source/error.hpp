
#ifndef ERROR_HPP
# define ERROR_HPP

/**" 401 <nickname> :No such nick/channel"*/
#define ERR_NOSUCHNICK " 401 :No such nick/channel"

/** " 402 <server name> :No such server"*/
#define ERR_NOSUCHSERVER " 402 <server name> :No such server"

/** " 403 <channel name> :No such channel"*/
#define ERR_NOSUCHCHANNEL " 403 <channel name> :No such channel"

/** " 404 <channel name> :Cannot send to channel"*/
#define ERR_CANNOTSENDTOCHAN " 404 <channel name> :Cannot send to channel"

/** " 405 <channel name> :You have joined too many channels"*/
#define ERR_TOOMANYCHANNELS " 405 <channel name> :You have joined too many channels"

/** " 406 <nickname> :There was no such nickname"*/
#define ERR_WASNOSUCHNICK " 406 <nickname> :There was no such nickname"

/** " 407 <target> :Duplicate recipients. No message delivered"*/
#define ERR_TOOMANYTARGETS " 407 <target> :Duplicate recipients. No message delivered"

/** " 409 :No origin specified"*/
#define ERR_NOORIGIN " 409 :No origin specified"

/** " 411 :No recipient given (<command>)"*/
#define ERR_NORECIPIENT " 411 :No recipient given (<command>)"

/** " 412 :No text to send"*/
#define ERR_NOTEXTTOSEND " 412 :No text to send"

/** " 413 <mask> :No toplevel domain specified"*/
#define ERR_NOTOPLEVEL " 413 <mask> :No toplevel domain specified"

/** " 414 <mask> :Wildcard in toplevel domain"*/
#define ERR_WILDTOPLEVEL " 414 <mask> :Wildcard in toplevel domain"

/** " 421 <command> :Unknown command"*/
#define ERR_UNKNOWNCOMMAND " 421 <command> :Unknown command"

/** " 422 :MOTD File is missing"*/
#define ERR_NOMOTD " 422 :MOTD File is missing"

/** " 423 <server> :No administrative info available"*/
#define ERR_NOADMININFO " 423 <server> :No administrative info available"

/** " 424 :File error doing <file op> on <file>"*/
#define ERR_FILEERROR " 424 :File error doing <file op> on <file>"

/** " 431 :No nickname given"*/
#define ERR_NONICKNAMEGIVEN " 431 :No nickname given"

/** " 432 <nick> :Erroneus nickname"*/
#define ERR_ERRONEUSNICKNAME " 432 <nick> :Erroneus nickname"

/** " 433 <nick> :Nickname is already in use"*/
#define ERR_NICKNAMEINUSE " 433 <nick> :Nickname is already in use"

/** " 436 <nick> :Nickname collision KILL"*/
#define ERR_NICKCOLLISION " 436 <nick> :Nickname collision KILL"

/** " 441 <nick> <channel> :They aren't on that channel"*/
#define ERR_USERNOTINCHANNEL " 441 <nick> <channel> :They aren't on that channel"

/** " 442 <channel> :You're not on that channel"*/
#define ERR_NOTONCHANNEL " 442 <channel> :You're not on that channel"

/** " 443 <user> <channel> :is already on channel"*/
#define ERR_USERONCHANNEL " 443 <user> <channel> :is already on channel"

/** " 444 <user> :User not logged in"*/
#define ERR_NOLOGIN " 444 <user> :User not logged in"

/** " 445 :SUMMON has been disabled"*/
#define ERR_SUMMONDISABLED " 445 :SUMMON has been disabled"

/** " 446 :USERS has been disabled"*/
#define ERR_USERSDISABLED " 446 :USERS has been disabled"

/** " 451 :You have not registered"*/
#define ERR_NOTREGISTERED " 451 :You have not registered"

/** " 461 <command> :Not enough parameters"*/
#define ERR_NEEDMOREPARAMS " 461 <command> :Not enough parameters"

/** " 462 :You may not reregister"*/
#define ERR_ALREADYREGISTRED " 462 :You may not reregister"

/** " 463 :Your host isn't among the privileged"*/
#define ERR_NOPERMFORHOST " 463 :Your host isn't among the privileged"

/** " 464 :Password incorrect"*/
#define ERR_PASSWDMISMATCH " 464 :Password incorrect"

/** " 465 :You are banned from this server"*/
#define ERR_YOUREBANNEDCREEP " 465 :You are banned from this server"

/** " 467 <channel> :Channel key already set"*/
#define ERR_KEYSET " 467 <channel> :Channel key already set"

/** " 471 <channel> :Cannot join channel (+l)"*/
#define ERR_CHANNELISFULL " 471 <channel> :Cannot join channel (+l)"

/** " 472 <char> :is unknown mode char to me"*/
#define ERR_UNKNOWNMODE " 472 <char> :is unknown mode char to me"

/** " 473 <channel> :Cannot join channel (+i)"*/
#define ERR_INVITEONLYCHAN " 473 <channel> :Cannot join channel (+i)"

/** " 474 <channel> :Cannot join channel (+b)"*/
#define ERR_BANNEDFROMCHAN " 474 <channel> :Cannot join channel (+b)"

/** " 475 <channel> :Cannot join channel (+k)"*/
#define ERR_BADCHANNELKEY " 475 <channel> :Cannot join channel (+k)"

/** " 481 :Permission Denied- You're not an IRC operator"*/
#define ERR_NOPRIVILEGES " 481 :Permission Denied- You're not an IRC operator"

/** " 482 <channel> :You're not channel operator"*/
#define ERR_CHANOPRIVSNEEDED " 482 <channel> :You're not channel operator"

/** " 483 :You cant kill a server!"*/
#define ERR_CANTKILLSERVER " 483 :You cant kill a server!"

/** " 491 :No O-lines for your host"*/
#define ERR_NOOPERHOST " 491 :No O-lines for your host"

/** " 501 :Unknown MODE flag"*/
#define ERR_UMODEUNKNOWNFLAG " 501 :Unknown MODE flag"

/** " 502 :Cant change mode for other users"*/
#define ERR_USERSDONTMATCH " 502 :Cant change mode for other users"

#endif
