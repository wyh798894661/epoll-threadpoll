#include "Data.h"

G_Data::G_Data(G_RecvMessThread *recvMessThread) : g_recvMessThread(recvMessThread)
{
}


G_Data::G_Data()
{
}

G_Data::~G_Data()
{
}

int G_Data::sendn(int nSocket , const void *pStr , unsigned int nLen)
{
	int n = nLen , nRet;
	char *str = (char*)pStr;
	while(n > 0)
	{
		nRet = send(nSocket , str , n , MSG_NOSIGNAL);
		if(nRet <= 0)
		{
			if(errno == EINTR)
			{
				continue;
			}
			return -1;
		}
		n -= nRet;
		str += nRet;
	}
	return (nLen - n);
}




int G_Data::recvn(int nSocket , void *pStr , unsigned int nLen)
{
	int n = nLen;
	char *str = (char*)pStr;

	while(n > 0)
	{
		int nRet = recv(nSocket , str , n , MSG_NOSIGNAL);
		if(nRet <= 0)
		{
			if(errno == EINTR)
			{
				continue;
			}
			break;
		}
		n -= nRet;
		str += nRet;
	}
	return (nLen - n);
}

int G_Data::packet(const void *pStr , unsigned int nLen , char *pBuffer)
{
	bcopy(pStr , &pBuffer[G_PHLEN] , nLen);
	*(unsigned int *)pBuffer = nLen;

	return (nLen + G_PHLEN);
}

int G_Data::packetSize(const char *pStr)
{
	return (*(unsigned int*)pStr);
}

void G_Data::unPacket(const void *in , unsigned int fromLen , unsigned int nLen , void *out)
{
	bcopy(&((char*)in)[G_PHLEN+fromLen] , out , nLen);
}

int G_Data::sendData(int nSocket , const void *pStr , unsigned int nLen)
{
	char pBuffer[G_MAXDATABUFFSIZE];
	bzero(pBuffer , sizeof(pBuffer));
	if(!pStr)
	{
		return -1;
	}

	int nSize = packet(pStr , nLen , pBuffer);
	int nRet = sendn(nSocket , pBuffer , nSize);
	return nRet;
}

bool G_Data::recvData(int nSocket)
{
	char pBuffer[G_MAXDATABUFFSIZE]; char pStr[G_MAXDATABUFFSIZE];
	bzero(pBuffer , sizeof(pBuffer));
	bzero(pStr , sizeof(pStr));
	int fromLen = 0 , n;

	int nSize = recvn(nSocket , pBuffer , sizeof(pBuffer));    ///返回接收数据大小
	if(nSize <= 0)
	{
		return false;
	}
	
	while(1)
	{
		n = packetSize(&pBuffer[fromLen]);   /// 返回数据真正大小
		unPacket(pBuffer , fromLen , n , pStr);    ///把真正数据存放到pStr中
		g_recvMessThread->pushData((std::string)pStr);          ///放到数据池队列中

		n += sizeof(unsigned int);
		fromLen += n;

		if(fromLen == nSize)
		{
			break;    ///如果数据都取完了退出循环
		}
	}
	return true;
}
