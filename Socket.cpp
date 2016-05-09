#include "Socket.h"
#include "Log.h"
		
G_Socket::G_Socket()
{
	epfd = epoll_create(256);
}

G_Socket::~G_Socket()
{
	close(g_sockfd);
	close(epfd);
}


bool G_Socket::setNonBlock(int sockfd)
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

bool G_Socket::Bind(unsigned int nPort)
{
	g_sockfd = socket(PF_INET , SOCK_STREAM , 0);
	if(-1 == g_sockfd)
	{
		debug_output("%s\n" , "Create Socket is faild");
		return false;
	}

	/// 允许地址重用
	int reuse = 1;
	setsockopt(g_sockfd , SOL_SOCKET , SO_REUSEADDR , &reuse , sizeof(reuse));

	bool bRet = setNonBlock(g_sockfd);
	if(bRet == false)
	{
		return false;
	}

	struct sockaddr_in servaddr;
	bzero(&servaddr , sizeof(servaddr));

	servaddr.sin_family = PF_INET;
	servaddr.sin_port = htons(9999);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int nRet = bind(g_sockfd , (struct sockaddr*)&servaddr , sizeof(servaddr));
	if(-1 == nRet)
	{
		debug_output("%s\n" , "bind is faild");
		return false;
	}

	nRet = listen(g_sockfd , 128);
	if(-1 == nRet)
	{
		debug_output("%s\n" , "listen is faild");
		return false;
	}

	struct epoll_event ev;
	bzero(&ev , sizeof(ev));
	ev.data.fd = g_sockfd;
	ev.events = EPOLLIN | EPOLLET;

	nRet = epoll_ctl(epfd , EPOLL_CTL_ADD , g_sockfd , &ev);
	if(-1 == nRet)
	{
		debug_output("%s\n" , "epoll_ctl is faild");
		return false;
	}

	return true;
}

bool G_Socket::Listen(int &nSocket)
{
	static int counter = 0;
	int nfds , i;
	while(1)
	{
		nfds = epoll_wait(epfd , events , 100 , 500);
		for(i=0; i<nfds; i++)
		{
			if(events[i].data.fd == g_sockfd)
			{
				nSocket = accept(g_sockfd , NULL , NULL);
				debug_output("nSocket = %d\n" , nSocket);
				if(nSocket == -1)
				{
					if(errno == EINTR)
					{
						continue;
					}
					debug_output("%s\n" , "accept is faild");
					return false;
				}
				debug_output("counter = %d\n" , ++counter);
				return true;
			}
		}
	}
}
