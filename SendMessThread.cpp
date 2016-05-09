#include "Log.h"
#include "SendMessThread.h"

G_SendMessThread::G_SendMessThread()
{
	bzero(&ev , sizeof(struct epoll_event));
	epfd = epoll_create(256);
	g_data = new G_Data();
}

G_SendMessThread::~G_SendMessThread()
{
	close(epfd);
	if(g_data)
	{
		delete g_data;
		g_data = NULL;
	}
}

void G_SendMessThread::addEpoll(int nSocket)
{
	ev.data.fd = nSocket;
	ev.events = EPOLLOUT | EPOLLERR;
	epoll_ctl(epfd , EPOLL_CTL_ADD , nSocket , &ev);
}

void G_SendMessThread::modEpoll(int nSocket)
{
	ev.data.fd = nSocket;
	ev.events = EPOLLOUT | EPOLLERR;
	epoll_ctl(epfd , EPOLL_CTL_MOD , nSocket , &ev);
}

/*
void G_SendMessThread::delEpoll(int nSocket)
{
	ev.data.fd = nSocket;
	epoll_ctl(epfd , EPOLL_CTL_DEL , nSocket , &ev);
}
*/

int G_SendMessThread::sendMessage(int nSocket , const void *pStr)
{
	char *str = (char*)pStr;
	g_sockDataMap.insert(g_mapPair(nSocket , (std::string)str));      ///把套接口和数据插入map中
}

void G_SendMessThread::Run()
{
	multimap<int , std::string>::iterator map_interator;

	int nfds , i , sock;
	std::string buffer;
	while(1)
	{
		nfds = epoll_wait(epfd , event , 100 , 500);
		for(i=0; i<nfds; i++)
		{
			if(event[i].events&EPOLLOUT)
			{
				sock = event[i].data.fd;
				
				while(1)
				{
					map_interator = g_sockDataMap.find(sock);
					if(map_interator == g_sockDataMap.end())
					{
						break;
					}
					g_data->sendData(sock , (void*)map_interator->second.c_str() , strlen(map_interator->second.c_str()));
					g_sockDataMap.erase(map_interator);
				}
				usleep(100);
			}
		}
	}
}

