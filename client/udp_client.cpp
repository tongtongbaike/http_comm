#include "udp_client.h"

//构造函数
udp_client::udp_client(string ip,short port)
	:_now_data._user_ip(ip)
	,_now_data._user_port(port)
	,_msg(" ")
	,sock(-1)
{
}

//析构函数
~udp_client::upd_client()
{
	if(sock > 0)
	{
		close(sock);
	}
}
//初始化服务器
bool udp_client::client_init()
{
	_sock = socket(AF_INET,SOCK_DGRAM,0);
	if(_sock < 0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(2);		
	}
}
//接收消息
bool udp_client::recv_msg()
{
	
	struct sockaddr_in server;

	return true;	
}
//发送消息
bool udp_client::send_msg()
{
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(_now_data._user_port);
	server.sin_addr.s_addr = inet_addr(_now_data._user_port);
	sendto(_sock,_msg.c_str(),msg.size(),0,(struct sockaddr*)&server,sizeof(server));
	return true;
}
