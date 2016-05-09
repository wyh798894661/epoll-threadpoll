#include "testPool.h"

MainPro *MainPro::instance = NULL;

bool MainPro::init()
{
	G_Server::init();
}

int main()
{
	MainPro *mp = MainPro::getInstance();
	mp->init();
	sleep(-1);
	//mp->delInstance();
	//delete mp;
	//mp = NULL;
	//mp.init();
}
