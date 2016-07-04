#include"udp_server.h"

//构造函数
udp_server::udp_server(string ip,short port)
	:_boradcast_list(64)
	 ,_now_data._user_ip(ip)
	 ,_now_data._user_port(port)
	 ,_sock(-1)
	 ,_msg(" ")
{
}

//析构函数
udp_server::~udp_server()
{
	if(_sock > 0)
	{
		close(_sock);
	}
}

//初始化服务器
void  udp_server::server_init()
{
	_sock = socket(AF_INET,SOCK_DGRAM,0);
	if(_sock < 0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(2);		
	}

	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(_now_data._user_port);
	if(_now_data._user_ip == "any")
	{
		local.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		local.sin_addr.s_addr = inet_addr(_now_data._user_ip.c_str());
	}
	
	if(bind(_sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(3);		
	}
}
//接收消息
bool udp_server::recv_msg()
{
	//接收数据
	struct sockaddr_in remote;
	socklen_t len;
	u_data cur_data;
	char buf[_MAX_SIZE_];
	ssize_t _s = recvfrom(_sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
	if(_s > 0)
	{
		_msg=buf;	
		cur_data._user_ip = inet_ntoa(remote.sin_addr);
		cur_data._user_port = ntohs(remote.sin_port);
		_boradcast_list.push_back(cur_data);
	}
	else if(_s == 0)
	{
		cout<<"client close";
		return false;
	}
	else
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(3);		
	}
	return true;
}
//发送消息
bool udp_server::send_msg()
{
	
	return true;
}
//广播消息
bool udp_server::boradcast_msg()
{
	return true;
}
