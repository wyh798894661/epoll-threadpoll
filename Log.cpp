#include "Log.h"

void debug_output(const char *fmt , ...)
{
/*
	time_t ti;
	ti = time(NULL);
	char times[65535];
	snprintf(times , sizeof(times) , "%s" , ctime(&ti));
	times[strlen(times)-1] = ' ';
	strncat(times , "-----------    " , 9);
	*/

	va_list ap;
	char buff[65535];
	va_start(ap , fmt);

	vsnprintf(buff , sizeof(buff) ,  fmt , ap);
	std::cout<<buff;
	//strncat(times , buff , strlen(buff));

	//fwrite(times , sizeof(char) , strlen(times) , pt);
	//fwrite("\n" , 1 , 1 , pt);
	//fflush(pt);
	va_end(ap);
}



