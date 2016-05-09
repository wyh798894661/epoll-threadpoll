#include "Server.h"
#include "Log.h"

G_Server *G_Server::instance = NULL;

static void ctrlcHandle(int signum)
{
	debug_output("ctrl-c signal .....\n");
}

G_Server::G_Server()
{
	instance = this;
}

G_Server::~G_Server()
{
}


bool G_Server::init()
{
	debug_output("%s\n" , __PRETTY_FUNCTION__);
	///定义ctrl-c信号
	struct sigaction act;
	act.sa_handler = ctrlcHandle;   
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT , &act , NULL);
}


