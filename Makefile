CC = g++
CFLAGS = -g -lpthread

all : testPool

testPool : Worker.cpp testPool.cpp ThreadPool.cpp Lock.cpp Thread.cpp ListenThread.cpp Socket.cpp Data.cpp RecvMessThread.cpp SendMessThread.cpp Server.cpp
	$(CC) $(CFLAG) Log.cpp Thread.cpp Worker.cpp testPool.cpp ThreadPool.cpp Lock.cpp ListenThread.cpp Socket.cpp Data.cpp RecvMessThread.cpp SendMessThread.cpp Server.cpp -lpthread -g -o server

