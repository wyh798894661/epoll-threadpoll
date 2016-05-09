///
/// @file Data.h
/// @brief 套接字发送接收的封装
/// @author wangyuhang
/// @date 2016-03-21
///

#ifndef __DATA__
#define __DATA__

#include "def.h"
#include "RecvMessThread.h"
#include "SendMessThread.h"

class G_RecvMessThread;
class G_SendMessThread;

class G_Data
{
	public:
		/// @brief 构造函数
		G_Data(G_RecvMessThread *recvMessThread);

		G_Data();

		/// @brief 析构函数
		~G_Data();

		/// @brief 接收数据并存到缓冲池中
		///
		/// @param nSocket	套接字
		///
		/// @return         如果收到数据返回成功 , 如果client关闭返回false
		bool recvData(int nSocket);

		/// @brief 发送数据
		///
		/// @param nSocket 套接字
		/// @param pData 数据包
		/// @param nLen 数据包长度
		///
		/// @return
		int sendData(int nSocket , const void *pStr , unsigned int nLen);

	private:

		/// @brief 发送数据
		///
		/// @param nSocket 	套接字
		/// @param ptr      发送数据
		/// @param nLen     数据长度
		///
		/// @return          发送数据长度
		int sendn(int nSocket , const void *pStr , unsigned int nLen);

		/// @brief 从套接口接受数据
		///
		/// @param nSocket 	套接口
		/// @param pStr     存放数据
		/// @param nLen     长度
		///
		/// @return         返回接受数据长度
		int recvn(int nSocket , void *pStr , unsigned int nLen);

		/// @brief 对数据进行打包
		///
		/// @param pStr 	输入数据
		/// @param nLen 	数据包长度
		/// @param pBuffer  输出数据
		///
		/// @return
		int packet(const void *pStr , unsigned int nLen , char *pBuffer);

		/// @brief 对数据进行解包
		///
		/// @param in 输入数据
		/// @param fromLen 从什么地方开始
		/// @param nLen  数据长度
		/// @param out 输出数据
		///
		//void unPacket(const char *in , unsigned int fromLen , unsigned int nLen , char *out);
		void unPacket(const void *in , unsigned int fromLen , unsigned int nLen , void *out);

		/// @brief 返回数据包大小
		///
		/// @param pData 数据包
		///
		/// @return  包的大小
		int packetSize(const char *pStr);


		G_RecvMessThread *g_recvMessThread;

		/// @brief 数据包大小
		static const unsigned int G_MAXDATABUFFSIZE = 65535;

		/// @brief 数据包包头大小
		static const unsigned int G_PHLEN = sizeof(unsigned int);

};

#endif
