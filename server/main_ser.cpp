#include "udp_server.h"

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;

void *ser_recv(void *arg)
{
	udp_server* cur = (udp_server *)arg;
	while(1)
	{
//		pthread_mutex_lock(&mutex_lock);
		cur->recv_msg();
//		pthread_mutex_unlock(&mutex_lock);
	}
}

void *ser_boradcast(void *arg)
{
	udp_server* cur = (udp_server *)arg;
	while(1)
	{
//		pthread_mutex_lock(&mutex_lock);
		cur->boradcast_msg();
//		pthread_mutex_unlock(&mutex_lock);
	}
}
int main(int argc,char *argv[])
{
	pthread_t tid1,tid2;
	if(argc != 3)
	{
		usage();
		return -1;
	}
	string ip = argv[1];
	short port = atoi(argv[2]);
	udp_server ser(ip,port);
	ser.server_init();
	
	pthread_create(&tid1,NULL,ser_recv,(void *)&ser);
	pthread_create(&tid2,NULL,ser_boradcast,(void *)&ser);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	//while(1)
	//{
	//	ser.recv_msg();
	//	ser.boradcast_msg();
	//}

	return 0;
}
