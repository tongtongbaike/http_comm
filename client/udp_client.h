#pragma once

#include<iostream>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<error.h>
#include<errno.h>
#include<string>
#include<vector>
#include<unistd.h>
#include "comm.h"
#include "udp_data.h"
#include"chat_window.h"

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 8080
using namespace std;

typedef struct user_data
{
	string _user_ip;
	short _user_port;
}u_data,*pu_data;

class udp_client
{
	public:
		//构造函数
		udp_client(string ip=DEFAULT_IP,short port=DEFAULT_PORT);

		//析构函数
		~udp_client();
		//初始化服务器
		void client_init();
		//接收消息
		void recv_msg(string &_out);
		//发送消息
		void send_msg(string &_in);
		void del_friend(const string &_win_f);
		void add_friend(const string &_win_f);
		std::vector<std::string> clif;
	private:
		u_data _now_data;//结构体
		int _sock;//sock
		//short _port;//端口
		//string _ip//IP地址
};

