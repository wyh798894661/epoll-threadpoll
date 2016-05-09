# epoll-threadpoll
Lock.cpp :      锁的操作 , 读锁可以并发 , 写锁独占.
Queue.h  :      队列的封装 , 队列的读和写都加了锁的保护.
Socket.cpp :   套接口的简单封装.
Thread.cpp :   线程的封装实现了些简单的线程停止，运行等功能 , 启动别的线程的时候需要继承次类.
Worker.cpp :  用户接口类 , 用户需继承此类。
ListenThread.cpp(继承Thread.cpp) : 服务器监听线程.如果有客户端连接通知ThreadPool类，由ThreadPool类进行任务分派.
TaskThread.cpp(继承Thread.cpp) : 具体任务类，负责接受客户端发送数据.
ThreadPool.cpp (继承Thread.cpp) : 线程池类负责启动别的线程 , 并且进行线程调度。首先启动ListenThread.cpp类，如果有客户端
连接ListenThread.cpp类发送信号通知ThreadPool.cpp类，收到信号再分配给TaskThread.cpp类，进行处理。如果没有空闲任务类，动态再
创建一定数目的任务类。
