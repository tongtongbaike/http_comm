#include "udp_client.h"

//构造函数
udp_client::udp_client(string ip,short port)
	:_sock(-1)
{
	_now_data._user_ip = ip;
	_now_data._user_port = port;
}

//析构函数
udp_client::~udp_client()
{
	if(_sock > 0)
	{
		close(_sock);
	}
}
//初始化服务器
void  udp_client::client_init()
{
	_sock = socket(AF_INET,SOCK_DGRAM,0);
	if(_sock < 0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(2);		
	}
}
//接收消息
void  udp_client::recv_msg(string &_out)
{
	
	struct sockaddr_in server;
	socklen_t len;
	char buf[_MAX_SIZE_];
	buf[0] = '\0';
//	server.sin_family=AF_INET;
//	server.sin_port=htons(_now_data._user_port);
//	server.sin_addr.s_addr = inet_addr(_now_data._user_ip.c_str());
	ssize_t _s = recvfrom(_sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&server,&len);
	if(_s > 0)
	{
		buf[_s] = '\0';
		_out = buf;
	}
	else if(_s == 0)
	{
		const char *msg = "client is close";
		print_log(msg,__FUNCTION__,__LINE__);
	}
	else
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(3);	
	}
}
//发送消息
void udp_client::send_msg(string &_in)
{
	struct sockaddr_in server_t;
	server_t.sin_family=AF_INET;
	server_t.sin_port=htons(_now_data._user_port);
	server_t.sin_addr.s_addr = inet_addr(_now_data._user_ip.c_str());
	socklen_t len = sizeof(server_t);
	ssize_t _s = sendto(_sock,_in.c_str(),_in.size(),0,(struct sockaddr*)&server_t,len);
	if(_s < 0)
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		exit(4);	
	}
	//cout<<_s<<_msg<<endl;
}

void udp_client::add_friend(const string &_win_f)
{
	std::vector<std::string>::iterator _iter = clif.begin();
	for(;_iter != clif.end(); ++_iter)
	{
		if(*_iter == _win_f)
		{
			return;
		}
	}
	clif.push_back(_win_f);
}

void udp_client::del_friend(const string &_win_f)
{
	std::vector<std::string>::iterator _iter = clif.begin();
	for(;_iter != clif.end();)
	{
		if(*_iter == _win_f)
		{
			_iter = clif.erase(_iter);
			break;
		}
		else
		{
			_iter++;
		}
	}	
}
