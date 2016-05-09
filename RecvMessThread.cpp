#include "RecvMessThread.h"
#include "Log.h"

G_RecvMessThread::G_RecvMessThread(G_ThreadPool *pool) : g_threadPool(pool)
{
	counter = 0;
	epfd = epoll_create(256);

	g_data = new G_Data(this);
}

G_RecvMessThread::~G_RecvMessThread()
{
	close(epfd);
}

unsigned int G_RecvMessThread::getCounter()
{
	return counter;
}

bool G_RecvMessThread::setNonBlock(int sockfd)
{
	int opts = fcntl(sockfd , F_GETFL);
	if(-1 == opts)
	{
		debug_output("%s\n" , "fcntl F_GETFL is faild");
		return false;
	}

	opts = opts | O_NONBLOCK;
	if(fcntl(sockfd , F_SETFL , opts) < 0)
	{
		debug_output("%s\n" , "fcntl F_SETFL is faild");
		return false;
	}
	return true;
}

void G_RecvMessThread::addSocket(int nSocket)
{
	struct epoll_event ev;
	bzero(&ev , sizeof(ev));

	setNonBlock(nSocket);
	ev.data.fd = nSocket;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd , EPOLL_CTL_ADD , nSocket , &ev);
	counter++;
}

bool G_RecvMessThread::pushData(std::string pStr)
{
	return g_dataBufferQueue.push(pStr);
}

void G_RecvMessThread::Run()
{
	pause();    /// 暂停线程

	int nfds , sock;
	struct epoll_event ev;
	bool nRet;
	char line[1024];
	while(1)
	{
		nfds = epoll_wait(epfd,events,100,50);
		for(int i=0; i<nfds; i++)
		{
			if(events[i].events&EPOLLIN)
			{
				if((sock = events[i].data.fd) < 0)
					continue;
				if(!(nRet=g_data->recvData(sock)))
				{
					debug_output("client is quit\n");
					ev.data.fd= sock;
					epoll_ctl(epfd , EPOLL_CTL_DEL , sock , &ev);
					close(sock);
					events[i].data.fd = -1;
					counter --;
				}
				else
				{
					std::string pBuffer;
					while(g_dataBufferQueue.size())
					{
						g_dataBufferQueue.pop(pBuffer);
						g_threadPool->recvMessage((void*)pBuffer.c_str() , sock);
					}
				}
				usleep(100);
			}
		}
	}
}
