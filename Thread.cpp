#include "Thread.h"
#include "Log.h"

G_Thread::G_Thread()
{
	maskSIGUSR1();

	// 定义SIGUSR1信号阻塞
	sigemptyset(&g_waitSig);
	sigaddset(&g_waitSig, SIGUSR1);
}

G_Thread::~G_Thread()
{
}

void G_Thread::maskSIGUSR1()
{
	sigset_t sig;
	sigemptyset(&sig);
	sigaddset(&sig , SIGUSR1);
	pthread_sigmask(SIG_BLOCK , &sig , NULL);
}


pthread_t G_Thread::getThreadId()
{
	return g_pid;
}


void *G_Thread::threadFun(void *arg)
{
	G_Thread *pThread = (G_Thread*)arg;
	pThread->Run();
}

bool G_Thread::Start()
{
	int nRet = pthread_create(&g_pid , NULL , threadFun , this);
	if(0 == nRet)
	{
		nRet = pthread_detach(g_pid);
		if(nRet == 0)
		{
			return true;
		}
	}
	else
	{
		return false;
	}

	return true;
}

void G_Thread::pause()
{
	int sig;
	sigwait(&g_waitSig , &sig);
}

void G_Thread::continues()
{
	pthread_kill(g_pid , SIGUSR1);
}
