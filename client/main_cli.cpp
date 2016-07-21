#include "udp_client.h"


udp_client *cli_p = NULL;
string nick_name;
string school;


void* run_header(void* arg)
{
	chat_window* winp = (chat_window*)arg;
	pthread_detach(pthread_self());
	int index = 0;
	std::string msg = "TongTong welcome for you!(^-^)";
	while(1)
	{
		winp->create_header();
		WINDOW* header_win = winp->get_header();

		int x,y;
		int header_x = 0;
		int header_y = 0;
		getmaxyx(header_win,y,x);
		header_y = y/2;

		index = index%(x-5)<5 ? 5:index%(x-5);
		if(index > (x-50))
		{
			index = 5;
		}
		header_x = index;
		winp->put_str_to_win(header_win,header_y,header_x,msg);
		winp->win_refresh(header_win);
		usleep(100000);
		index++;
		winp->clear_win_line(header_win,header_y,3);
	}
	return NULL;
}

void* run_output(void *arg)
{
	pthread_detach(pthread_self());
	std::string msg;
	chat_window *winp = (chat_window*)arg;
	int index = 0;
	const int output_x = 7;
	int output_y = 0;

	winp->create_output();
	WINDOW *output_win = winp->get_output();

	int y,x;
	getmaxyx(output_win,y,x);
	udp_data data;
	string _nick_name;
	string _msg;
	string _school;
	string _cmd;
	string _win_out;
	string _win_f;
	while(1)
	{
//		winp->create_output();
//		WINDOW *output_win = winp->get_output();
//
//		int y,x;
//		getmaxyx(output_win,y,x);
		cli_p->recv_msg(msg);
		data.string_to_val(_nick_name,_msg,_school,_cmd,msg);
		_win_out = _nick_name;
		_win_out += "-";
		_win_out += _school;
		
		_win_f = _win_out;

		_win_out += "# ";
		_win_out += _msg;
		
		cli_p->add_friend(_win_f);

		if(_cmd == "QUIT")
		{
			cli_p->del_friend(_win_f);
			break;
		}

		index = index%(y-1);
		index = index <1?1:index;
		output_y = index;
		winp->put_str_to_win(output_win,output_y,output_x,_win_out.c_str());
		//winp->win_refresh(output_win);
//		usleep(1000000);
		index++;
		if(index == (y - 1))
		{
			index = 1;
			winp->clear_win_line(output_win,1,y-2);
	//		winp->create_output();
	//		output_win = winp->get_output();
		}
		winp->win_refresh(output_win);
	}
	return NULL;
}

void* run_friendlist(void *arg)
{
	chat_window* winp = (chat_window*)arg;
	pthread_detach(pthread_self());
//	winp->create_friendlist();
	while(1)
	{
		winp->create_friendlist();
		int y,x;
		WINDOW *friendlist_win = winp->get_friendlist();
		getmaxyx(friendlist_win,y,x);
		int total = (cli_p->clif.size());
		int total_page = total/15;
		if(total%15 != 0)
		{

			total_page++;
		}
		
		std::string val;
		std::string val1;
		std::strstream ssl;
		ssl<<total_page;
		ssl>>val1;
		for(int i = 1;i <= total_page;++i)
		{
			int j = 0;
			while( j < total && j < 15)
			{
				winp->put_str_to_win(friendlist_win,j+1,3,cli_p->clif[15*(i-1)+j]);
				j++;
			}
			val = "";
			std::strstream ss;
			ss<<i;
			ss>>val;
			val += "/";
			val += val1;
			winp->put_str_to_win(friendlist_win,y-2,x/2,val.c_str());
			winp->win_refresh(friendlist_win);
			sleep(2);
		}
	}
	return NULL;
}
int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		usage();
		exit(1);
	}
	string _remote_ip = argv[1];
	short _remote_port = atoi(argv[2]);

	cout<<"Please Enter Your Nick_name";
	fflush(stdout);
	cin>>nick_name;
	cout<<"Please Enter you school";
	fflush(stdout);
	cin>>school;

	chat_window win;
	udp_client _cli(_remote_ip,_remote_port);
	_cli.client_init();
	cli_p = &_cli;


	pthread_t header;
	pthread_t output;
	pthread_t friendlist;

	pthread_create(&header,NULL,run_header,(void *)&win);
	pthread_create(&output,NULL,run_output,(void *)&win);
	pthread_create(&friendlist,NULL,run_friendlist,(void *)&win);

	string _out;
	string _cmd = "None";
	string _line = "Please Enter# ";
	udp_data _data;
	win.create_input();
	WINDOW* input_win = win.get_input();
	int _max_y;
	int _max_x;
	getmaxyx(input_win,_max_y,_max_x);
	while(1)
	{
	//	win.create_input(_in);
	//	WINDOW* input_win = win.get_input();
	//	int _max_y;
	//	int _max_x;
	//	getmaxyx(input_win,_max_y,_max_x);
		win.put_str_to_win(input_win,1,3,_line);
		string _in = win.get_input_msg(input_win);
		win.clear_win_line(input_win,1,1);
		if(_in == "quit" || _in == "q")
		{
			_cmd = "QUIT";
			_data.val_to_string(nick_name,_in,school,_cmd,_out);
			cli_p->send_msg(_out);
			pthread_cancel(header);
			pthread_cancel(output);
			pthread_cancel(friendlist);
			break;
		}
		_data.val_to_string(nick_name,_in,school,_cmd,_out);
		cli_p->send_msg(_out);
		usleep(1000);
	}
	return 0;
}

//pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
//
//void *cli_recv(void *arg)
//{
//	udp_client* cur = (udp_client *)arg;
//	while(1)
//	{
////		pthread_mutex_lock(&mutex_lock);
//		cur->recv_msg();
////		pthread_mutex_unlock(&mutex_lock);
//	
//	}
//}
//
//void *cli_send(void *arg)
//{
//	udp_client* cur = (udp_client *)arg;
//	while(1)
//	{
////		pthread_mutex_lock(&mutex_lock);
//		cur->send_msg();
////		pthread_mutex_unlock(&mutex_lock);
//	}
//}
//
//int main(int argc,char *argv[])
//{
//	pthread_t tid1,tid2;
//	if(3 != argc)
//	{
//		usage();
//		return -1;
//	}
//
//	udp_client cli(argv[1],atoi(argv[2]));
//	cli.client_init();
//	pthread_create(&tid1,NULL,cli_recv,(void *)&cli);
//	pthread_create(&tid2,NULL,cli_send,(void *)&cli);
//	pthread_join(tid1,NULL);
//	pthread_join(tid2,NULL);
////	while(1)
////	{
////		cli.send_msg();
////
////		cli.recv_msg();
////	}
//
//	return 0;
//}
