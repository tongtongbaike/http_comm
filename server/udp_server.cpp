#include"udp_server.h"

//构造函数
udp_server::udp_server(string ip,short port)
	:_boradcast_list(64)
	 ,_sock(-1)
	 ,_msg(" ")
{
	 _now_data._user_ip = ip;
	 _now_data._user_port = port;
}

//析构函数
udp_server::~udp_server()
{
	if(_sock > 0)
	{
		close(_sock);
	}
}

bool udp_server::find_user(string ip,short port)
{
	bool ret = false;
	vector<u_data>::iterator iter;
	for(iter = _boradcast_list.begin();iter != _boradcast_list.end();++iter)
	{
		if(iter->_user_ip == ip && iter->_user_port == port)
		{
			ret = true;
			break;
		}
	}
	return ret;
}

void udp_server::erase_user(string ip,short port)
{
	vector<u_data>::iterator iter;
	for(iter = _boradcast_list.begin();iter != _boradcast_list.end();++iter)
	{
		if(iter->_user_ip == ip && iter->_user_port == port)
		{
			iter = _boradcast_list.erase(iter);
		}
		else
		{
			iter++;
		}
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
	socklen_t len = sizeof(remote);
	u_data cur_data;
	char buf[_MAX_SIZE_];
	
	ssize_t _s = recvfrom(_sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
	
	cur_data._user_ip = inet_ntoa(remote.sin_addr);
	cur_data._user_port = ntohs(remote.sin_port);
	
	if(_s >= 0)
	{
		buf[_s] = '\0';
		_msg=buf;
		if(find_user(cur_data._user_ip,cur_data._user_port) != true)
		{
			_boradcast_list.push_back(cur_data);
		}
		data.pool_push(_msg);
	}
	else
	{
		print_log(strerror(errno),__FUNCTION__,__LINE__);
		return false;		
	}
	return true;
}
//发送消息
bool udp_server::send_msg(string ip,short port)
{

	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(port);
	client.sin_addr.s_addr = inet_addr(ip.c_str());
	ssize_t _s = sendto(_sock,_msg.c_str(),_msg.size(),0,(struct sockaddr*)&client,sizeof(client));
	
	if(_s <= 0)
	{
		erase_user(ip,port);
		return false;
	}

	return true;
}
//广播消息
void  udp_server::boradcast_msg()
{
	vector<u_data>::iterator iter;
	data.pool_pop(_msg);
	//cout<<"join bdcm"<<endl;
	for(iter = _boradcast_list.begin();iter != _boradcast_list.end();++iter)
	{
		//cout<<iter->_user_ip<<"::"<<iter->_user_port<<endl;
		u_data cur = *iter;
		if(iter->_user_ip != "")
			send_msg(iter->_user_ip,iter->_user_port);
	}
}
