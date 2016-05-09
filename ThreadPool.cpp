#include "ThreadPool.h"
#include "Log.h"

G_ThreadPool::G_ThreadPool(unsigned int num , G_Worker *g_work) : g_worker(g_work)
{
	g_listenThread = new G_ListenThread(this);
	g_listenThread->Start();  ///启动监听线程

	g_sendMessThread = new G_SendMessThread();
	g_sendMessThread->Start();   ///发送消息线程

	for(int i=0; i<num; i++)
	{
		/// 启动处理client发送信息线程 , 收消息线程
		G_RecvMessThread *g_recvMessThread = new G_RecvMessThread(this);
		g_idleRecvMessThreadQueue.push(g_recvMessThread);
		g_recvMessThread->Start();        
	}

	Start();   ///线程池自己启动
}

G_ThreadPool::~G_ThreadPool()
{
	if(g_listenThread)
	{
		delete g_listenThread;
		g_listenThread = NULL;
	}
	if(g_sendMessThread)
	{
		delete g_sendMessThread;
		g_sendMessThread = NULL;
	}
	
	g_sockQueue.clear();
	g_idleRecvMessThreadQueue.clear();
	g_busyRecvMessThreadQueue.clear();
}

bool G_ThreadPool::Bind(unsigned int nPort)
{
	return g_listenThread->Bind(nPort);
}

int G_ThreadPool::sendMessage(int nSocket , const void *pStr)
{
	g_sendMessThread->sendMessage(nSocket , pStr);
}

void G_ThreadPool::Run()
{
	int nSocket;  
	G_RecvMessThread *g_recvMessThread;
	while(1)
	{
		pause();   ///等待ListenThread 发信号
		while(popSocket(nSocket))     ///必须把存放socket队列中的套接口全部取出
		{ 
			g_sendMessThread->addEpoll(nSocket);
			while(1)
			{
				///从空闲队列中获得对首TaskThread
				if(g_idleRecvMessThreadQueue.getFront(g_recvMessThread)) 
				{
					///如果TaskThread线程中客户大于maxCounter , 从空闲队列中pop并放到忙碌队列中
					if(g_recvMessThread->getCounter() >= maxCounter)  
					{
						if(g_idleRecvMessThreadQueue.pop(g_recvMessThread))
						{
							g_busyRecvMessThreadQueue.push(g_recvMessThread);
						}
						else
						{
							///表示空闲队列中再没有TaskThread可以用 , 创建addTaskThread个TaskThread线程 , 并且把busy队列中的TaskThread放到idle队列中这样可以防止busy队列中的用户数减少但是他还在busy队列中
							for(int i=0; i<addTaskThread; i++)
							{
								G_RecvMessThread *g_recvMessThread = new G_RecvMessThread(this);
								g_idleRecvMessThreadQueue.push(g_recvMessThread);
								g_recvMessThread->Start();
							}
							while(g_busyRecvMessThreadQueue.pop(g_recvMessThread))
							{
								g_idleRecvMessThreadQueue.push(g_recvMessThread);
							}
						}
					}
					else
					{
						/// 填加到TaskThread 线程中
						g_recvMessThread->addSocket(nSocket);
						g_recvMessThread->continues();   /// 唤醒TaskThread 线程
						break;
					}
				}
				else
				{
					/// 空闲队列中没有任何线程 , 应该没有这种情况
					debug_output("idleRecvMessThreadQueue is not g_recvMessThread\n");
				}
			}
		}
	}
}

bool G_ThreadPool::pushSocket(unsigned int nSocket)
{
	return g_sockQueue.push(nSocket);
}

bool G_ThreadPool::popSocket(int &nSocket)
{
	return g_sockQueue.pop(nSocket);
}


void G_ThreadPool::recvMessage(void *pStr , int nSocket)
{
	g_worker->recvMessage(pStr , nSocket);
}
