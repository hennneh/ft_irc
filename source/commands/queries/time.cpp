#include "../commands.hpp"
#include "../../irc.hpp"
#include <ctime>

void cmd::timer(const ft::Message & msg, ft::Client & client, ft::IRC & irc)
{
	(void) msg;
	time_t rawtime;
	struct tm * timeinfo;
	std::string s;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	s = asctime(timeinfo);
	client.sendErrMsg(irc._hostname, RPL_TIME, s);
}
/*
int main ()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "The current date/time is: %s", asctime (timeinfo) );

  return 0;
}
*/
