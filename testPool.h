#ifndef __USERWORKER__
#define __USERWORKER__

#include "Worker.h"
#include "Log.h"
#include "def.h"
#include "Server.h"

struct UserData
{
	int age;
	char name[20];
};


class UserWorker : public G_Worker
{
	public:
		UserWorker(unsigned int num) : G_Worker(num)
		{
		}

		~UserWorker()
		{
		}

		void recvMessage(void *str , int nSocket)
		{
	//		struct UserData *userData = (struct UserData*)str;
	//		std::cout<<"userData->age = "<<userData->age<<std::endl;

			sendMessage(nSocket , str);
			//sleep(2);
		}
};

class MainPro  : public G_Server
{
	public:
		MainPro()
		{
	//		userWork = new UserWorker(3);
	//	userWork->Bind(9999);
		}

		~MainPro()
		{
		/*
			if(userWork)
			{
				delete userWork;
				userWork = NULL;
			}
			*/
		}
	
		static MainPro *getInstance()
		{
			if(!instance)
			{
				instance = new MainPro();
			}
			return instance;
		}

		void delInstance()
		{
			if(instance)
			{
				delete instance;
				instance = NULL;
			}
		}

		bool init();
	
	private:
		UserWorker *userWork;

		static MainPro *instance;
	
};

#endif
