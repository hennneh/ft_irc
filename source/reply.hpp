#ifndef REPLY_HPP
# define REPLY_HPP

/** "001 RPL_WELCOME Welcome to the Internet Relay Network <nick>!<user>@<host>" */
#define RPL_WELCOME "001 Welcome to the Internet Relay Network <nick>!<user>@<host>"

/** "002 RPL_YOURHOST Your host is <servername>, running version <ver>" */
#define RPL_YOURHOST "002 Your host is <servername>, running version <ver>"

/** "003 RPL_CREATED This server was created <date>" */
#define RPL_CREATED "003 This server was created <date>"

/** "004 RPL_MYINFO <servername> <version> <available user modes> <available channel modes>" */
#define RPL_MYINFO "004 <servername> <version> <available user modes> <available channel modes>"

/** "005 RPL_BOUNCE Try server <server name>, port <port number>" */
#define RPL_BOUNCE "005 Try server <server name>, port <port number>"

/** "302 RPL_USERHOST :<replys>" */
#define RPL_USERHOST "302 :<replys>"

/** "303 RPL_ISON :<nicks>" */
#define RPL_ISON "303 :<nicks>"

/** "301 RPL_AWAY <nick> :<away message>" */
#define RPL_AWAY "301 <nick> :<away message>"

/** "305 RPL_UNAWAY :You are no longer marked as being away" */
#define RPL_UNAWAY "305 :You are no longer marked as being away"

/** "306 RPL_NOWAWAY :You have been marked as being away" */
#define RPL_NOWAWAY "306 :You have been marked as being away"

/** "311 RPL_WHOISUSER <nick> <user> <host> * :<real name>" */
#define RPL_WHOISUSER "311 <nick> <user> <host> * :<real name>"

/** "312 RPL_WHOISSERVER <nick> <server> :<server info>" */
#define RPL_WHOISSERVER "312 <nick> <server> :<server info>"

/** "313 RPL_WHOISOPERATOR <nick> :is an IRC operator" */
#define RPL_WHOISOPERATOR "313 <nick> :is an IRC operator"

/** "317 RPL_WHOISIDLE <nick> <integer> :seconds idle" */
#define RPL_WHOISIDLE "317 <nick> <integer> :seconds idle"

/** "318 RPL_ENDOFWHOIS <nick> :End of WHOIS list" */
#define RPL_ENDOFWHOIS "318 <nick> :End of WHOIS list"

/** "319 RPL_WHOISCHANNELS <nick> :<channels>" */
#define RPL_WHOISCHANNELS "319 <nick> :<channels>)"

/** "314 RPL_WHOWASUSER <nick> <user> <host> * :<real name>" */
#define RPL_WHOWASUSER "314 <nick> <user> <host> * :<real name>"

/** "369 RPL_ENDOFWHOWAS <nick> :End of WHOWAS" */
#define RPL_ENDOFWHOWAS "369 <nick> :End of WHOWAS"

/** "322 RPL_LIST <channel> <# visible> :<topic>" */
#define RPL_LIST "322 <channel> <# visible> :<topic>"

/** "323 RPL_LISTEND :End of LIST" */
#define RPL_LISTEND "323 :End of LIST"

/** "325 RPL_UNIQOPIS <channel> <nickname>" */
#define RPL_UNIQOPIS "325 <channel> <nickname>"

/** "324 RPL_CHANNELMODEIS <channel> <mode> <mode params>" */
#define RPL_CHANNELMODEIS "324 <channel> <mode> <mode params>"

/** "331 RPL_NOTOPIC <channel> :No topic is set" */
#define RPL_NOTOPIC "331 <channel> :No topic is set"

/** "332 RPL_TOPIC <channel> :<topic>" */
#define RPL_TOPIC "332 <channel> :<topic>"

/** "341 RPL_INVITING <channel> <nick>" */
#define RPL_INVITING "341 <channel> <nick>"

/** "342 RPL_SUMMONING <user> :Summoning user to IRC" */
#define RPL_SUMMONING "342 <user> :Summoning user to IRC"

/** "346 RPL_INVITELIST <channel> <invitemask>" */
#define RPL_INVITELIST "346 <channel> <invitemask>"

/** "347 RPL_ENDOFINVITELIST <channel> :End of channel invite list" */
#define RPL_ENDOFINVITELIST "347 <channel> :End of channel invite list"

/** "348 RPL_EXCEPTLIST <channel> <exceptionmask>" */
#define RPL_EXCEPTLIST "348 <channel> <exceptionmask>"

/** "349 RPL_ENDOFEXCEPTLIST <channel> :End of channel exception list" */
#define RPL_ENDOFEXCEPTLIST "349 <channel> :End of channel exception list"

/** "351 RPL_VERSION <version>.<debuglevel> <server> :<comments>" */
#define RPL_VERSION "351 <version>.<debuglevel> <server> :<comments>"

/** "352 RPL_WHOREPLY <channel> <user> <host> <server> <nick> <flags>" */
#define RPL_WHOREPLY "352 <channel> <user> <host> <server> <nick> <flags> :<hopcount> <real name>"

/** "315 RPL_ENDOFWHO <name> :End of WHO list" */
#define RPL_ENDOFWHO "315 <name> :End of WHO list"

/** "353 RPL_NAMREPLY <channeltype> <channel> :<nickwithflag>" */
#define RPL_NAMREPLY "353 <channeltype> <channel> :<nickwithflag>"

/** "366 RPL_ENDOFNAMES <channel> :End of NAMES list" */
#define RPL_ENDOFNAMES "366 <channel> :End of NAMES list"

/** "364 RPL_LINKS <mask> <server> :<hopcount> <server info>" */
#define RPL_LINKS "364 <mask> <server> :<hopcount> <server info>"

/** "365 RPL_ENDOFLINKS <mask> :End of LINKS list" */
#define RPL_ENDOFLINKS "365 <mask> :End of LINKS list"

/** "367 RPL_BANLIST <channel> <banmask>" */
#define RPL_BANLIST "367 <channel> <banmask>"

/** "368 RPL_ENDOFBANLIST <channel> :End of channel ban list" */
#define RPL_ENDOFBANLIST "368 <channel> :End of channel ban list"

/** "371 RPL_INFO :<string>" */
#define RPL_INFO "371 :<string>"

/** "374 RPL_ENDOFINFO :End of INFO list" */
#define RPL_ENDOFINFO "374 :End of INFO list"

/** "375 RPL_MOTDSTART :- <server> Message of the day - " */
#define RPL_MOTDSTART "375 :- <server> Message of the day - "

/** "372 RPL_MOTD :- <text>" */
#define RPL_MOTD "372 :- <text>"

/** "376 RPL_ENDOFMOTD :End of MOTD command" */
#define RPL_ENDOFMOTD "376 :End of MOTD command"

/** "381 RPL_YOUREOPER :You are now an IRC operator" */
#define RPL_YOUREOPER "381 :You are now an IRC operator"

/** "382 RPL_REHASHING <config file> :Rehashing" */
#define RPL_REHASHING "382 <config file> :Rehashing"

/** "383 RPL_YOURESERVICE You are service <servicename>" */
#define RPL_YOURESERVICE "383 You are service <servicename>"

/** "391 RPL_TIME <server> :<string showing server's local time>" */
#define RPL_TIME "391 <server> :<string showing server's local time>"

/** "392 RPL_USERSSTART :UserID   Terminal  Host" */
#define RPL_USERSSTART "392 :UserID   Terminal  Host"

/** "393 RPL_USERS :<username> <ttyline> <hostname>" */
#define RPL_USERS "393 :<username> <ttyline> <hostname>"

/** "394 RPL_ENDOFUSERS :End of users" */
#define RPL_ENDOFUSERS "394 :End of users"

/** "395 RPL_NOUSERS :Nobody logged in" */
#define RPL_NOUSERS "395 :Nobody logged in"

/** "200 RPL_TRACELINK Link <version & debug level> <destination> <next server> V<protocol version> <link uptime in seconds> <backstream sendq> <upstream sendq>" */
#define RPL_TRACELINK "200 Link <version & debug level> <destination> <next server> V<protocol version> <link uptime in seconds> <backstream sendq> <upstream sendq>"

/** "201 RPL_TRACECONNECTING Try. <class> <server>" */
#define RPL_TRACECONNECTING "201 Try. <class> <server>"

/** "202 RPL_TRACEHANDSHAKE H.S. <class> <server>" */
#define RPL_TRACEHANDSHAKE "202 H.S. <class> <server>"

/** "203 RPL_TRACEUNKNOWN ???? <class> [<client IP address in dot form>]" */
#define RPL_TRACEUNKNOWN "203 ???? <class> [<client IP address in dot form>]"

/** "204 RPL_TRACEOPERATOR Oper <class> <nick>" */
#define RPL_TRACEOPERATOR "204 Oper <class> <nick>"

/** "205 RPL_TRACEUSER User <class> <nick>" */
#define RPL_TRACEUSER "205 User <class> <nick>"

/** "206 RPL_TRACESERVER Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server> V<protocol version>" */
#define RPL_TRACESERVER "206 Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server> V<protocol version>"

/** "207 RPL_TRACESERVICE Service <class> <name> <type> <active type>" */
#define RPL_TRACESERVICE "207 Service <class> <name> <type> <active type>"

/** "208 RPL_TRACENEWTYPE <newtype> 0 <client name>" */
#define RPL_TRACENEWTYPE "208 <newtype> 0 <client name>"

/** "209 RPL_TRACECLASS Class <class> <count>" */
#define RPL_TRACECLASS "209 Class <class> <count>"

/** "261 RPL_TRACELOG File <logfile> <debug level>" */
#define RPL_TRACELOG "261 File <logfile> <debug level>"

/** "262 RPL_TRACEEND <server name> <version & debug level> :End of TRACE" */
#define RPL_TRACEEND "262 <server name> <version & debug level> :End of TRACE"

/** "211 RPL_STATSLINKINFO <linkname> <sendq> <sent messages> <sent Kbytes> <received messages> <received Kbytes> <time open>" */
#define RPL_STATSLINKINFO "<linkname> <sendq> <sent messages> <sent Kbytes> <received messages> <received Kbytes> <time open>"

/** "212 RPL_STATSCOMMANDS <command> <count> <byte count> <remote count>" */
#define RPL_STATSCOMMANDS "212 <command> <count> <byte count> <remote count>"

/** "219 RPL_ENDOFSTATS <stats letter> :End of STATS report" */
#define RPL_ENDOFSTATS "219 <stats letter> :End of STATS report"

/** "242 RPL_STATSUPTIME :Server Up %d days %d:%02d:%02d" */
#define RPL_STATSUPTIME "242 :Server Up %d days %d:%02d:%02d"

/** "243 RPL_STATSOLINE O <hostmask> * <name>" */
#define RPL_STATSOLINE "243 O <hostmask> * <name>"

/** "221 RPL_UMODEIS <user mode string>" */
#define RPL_UMODEIS "221 <user mode string>"

/** "234 RPL_SERVLIST <name> <server> <mask> <type> <hopcount> <info>" */
#define RPL_SERVLIST "234 <name> <server> <mask> <type> <hopcount> <info>"

/** "235 RPL_SERVLISTEND <mask> <type> :End of service listing" */
#define RPL_SERVLISTEND "235 <mask> <type> :End of service listing"

/** "251 RPL_LUSERCLIENT :There are <integer> users and <integer> services on <integer> servers" */
#define RPL_LUSERCLIENT "251 :There are <integer> users and <integer> services on <integer> servers"

/** "252 RPL_LUSEROP <integer> :operator(s) online" */
#define RPL_LUSEROP "252 <integer> :operator(s) online"

/** "253 RPL_LUSERUNKNOWN <integer> :unknown connection(s)" */
#define RPL_LUSERUNKNOWN "253 <integer> :unknown connection(s)"

/** "254 RPL_LUSERCHANNELS <integer> :channels formed" */
#define RPL_LUSERCHANNELS "254 <integer> :channels formed"

/** "255 RPL_LUSERME :I have <integer> clients and <integer> servers" */
#define RPL_LUSERME "255 :I have <integer> clients and <integer> servers"

/** "256 RPL_ADMINME <server> :Administrative info" */
#define RPL_ADMINME "256 <server> :Administrative info - King Hendrick, Prime Minister Pete, Alchemist Clemens & Head TroubleMaker Vincent"

/** "257 RPL_ADMINLOC1 :<admin info>" */
#define RPL_ADMINLOC1 "257 :<admin info>"

/** "258 RPL_ADMINLOC2 :<admin info>" */
#define RPL_ADMINLOC2 "258 :<admin info>"

/** "259 RPL_ADMINEMAIL :<admin info>" */
#define RPL_ADMINEMAIL "259 :<admin info>"

/** "263 RPL_TRYAGAIN <command> :Please wait a while and try again." */
#define RPL_TRYAGAIN "263 <command> :Please wait a while and try again."

#endif
