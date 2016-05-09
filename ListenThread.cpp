#include "ListenThread.h"
#include "Log.h"

G_ListenThread::G_ListenThread(G_ThreadPool *pool) : g_threadPool(pool)
{
	g_socket = new G_Socket();
}

G_ListenThread::~G_ListenThread()
{
	if(g_socket)
	{
		delete g_socket;
		g_socket = NULL;
	}
}

void G_ListenThread::Run()
{
	pause();

	debug_output("Listen thread is starting ....\n");
	
	int nSocket; 

	while(1)
	{
		if(g_socket->Listen(nSocket))
		{
			debug_output("new client is connecting ....\n");
			g_threadPool->pushSocket(nSocket);   ///填加到套接口队列
			g_threadPool->continues();   ///通知线程池，运行起来，到套接口队列中取套接口
		}
	}
}

bool G_ListenThread::Bind(unsigned int nPort)
{
	if(!g_socket->Bind(nPort))
	{
		debug_output("Bind port %d is faild\n" , nPort);
		return false;
	}
	debug_output("Bind port %d is Successful\n" , nPort);

	continues();

	return true;
}
