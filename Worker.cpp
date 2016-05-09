#include "Worker.h"
#include "Log.h"

G_Worker::G_Worker(unsigned int num)
{
	g_threadPool = new G_ThreadPool(num , this);
}

G_Worker::~G_Worker()
{
	if(g_threadPool)
	{
		delete g_threadPool;
		g_threadPool = NULL;
	}
}

bool G_Worker::Bind(unsigned int nPort)
{
	return g_threadPool->Bind(nPort);
}

int G_Worker::sendMessage(int nSocket , const void *pStr)
{
	return g_threadPool->sendMessage(nSocket , pStr);
}
