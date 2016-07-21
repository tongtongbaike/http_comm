#include "chat_window.h"


chat_window::chat_window()
	:_size(_MAX_SIZE_)
{
	initscr();
	curs_set(0);
}
chat_window::~chat_window()
{
	destroy_win(header);
	destroy_win(output);
	destroy_win(friendlist);
	destroy_win(input);
	endwin();

}

void chat_window::create_header()
{
	int starty = 0;
	int startx = 0;
	int heigth = LINES/5;
	int width = COLS;
	header = create_newwin(heigth,width,starty,startx);
	win_refresh(header);
}

void chat_window::create_output()
{
	int starty = LINES/5;
	int startx = 0;
	int heigth = (LINES*3)/5;
	int width = (COLS * 3)/4;
	output = create_newwin(heigth,width,starty,startx);
	win_refresh(output);
}

void chat_window::create_friendlist()
{
	int starty = LINES/5;
	int startx = (COLS *3)/4;
	int heigth = (LINES*3)/5;
	int width = COLS/4;
	friendlist = create_newwin(heigth,width,starty,startx);	
	win_refresh(friendlist);
}

void chat_window::create_input()
{
	int starty = (LINES*4)/5;
	int startx = 0;
	int heigth = LINES/5;
	int width = COLS;
	input  = create_newwin(heigth,width,starty,startx);
	win_refresh(input);
//	
//	int output_start_y = 1;
//	int output_start_x = 1;
//	//put_str_to_win(input,output_start_y,output_start_x,msg_tmp);
//	out  = get_input_msg(input);
}

void chat_window::win_refresh(WINDOW *win)
{
	wrefresh(win);
}

void chat_window::clear_win_line(WINDOW *win,int begin,int line)
{
	while(line-- > 0)
	{
		wmove(win,begin++,0);
		wclrtoeol(win);
	}
}

void chat_window::destroy_win(WINDOW *local_win)
{
	delwin(local_win);
}

std::string chat_window::get_input_msg(WINDOW *win)
{
	char msg[_MAX_SIZE_];
	memset(msg,'\0',sizeof(msg));
	wgetnstr(win,msg,_MAX_SIZE_);
	return msg;
}

void chat_window::put_str_to_win(WINDOW *win,int starty,int startx,const std::string &msg)
{
	mvwaddstr(win,starty,startx,msg.c_str());
}

WINDOW *chat_window::create_newwin(int heigth,int width,int starty,int startx)
{
	WINDOW* local_win = newwin(heigth,width,starty,startx);
	box(local_win,0,0);
	return local_win;
}
WINDOW* chat_window::get_header()
{
	return header;
}
WINDOW* chat_window::get_output()
{
	return output;
}
WINDOW* chat_window::get_friendlist()
{
	return friendlist;
}

WINDOW* chat_window::get_input()
{
	return input;
}




//static chat_window win;
//
//void* run_header(void* arg)
//{
//	pthread_detach(pthread_self());
//	int index = 0;
//	std::string msg = "TongTong welcome for you!(^-^)";
//	while(1)
//	{
//		win.create_header();
//		WINDOW* header_win = win.get_header();
//
//		int x,y;
//		int header_x = 0;
//		int header_y = 0;
//		getmaxyx(header_win,y,x);
//		header_y = y/2;
//
//		index = index%(x-5)<5 ? 5:index%(x-5);
//		if(index > (x-50))
//		{
//			index = 5;
//		}
//		header_x = index;
//		win.put_str_to_win(header_win,header_y,header_x,msg);
//		win.win_refresh(header_win);
//		usleep(100000);
//		index++;
//		win.clear_win_line(header_win,header_y,3);
//	}
//	return NULL;
//}
//
//void* run_output(void *arg)
//{
//	pthread_detach(pthread_self());
//	std::string msg = "test data";
//	int index = 0;
//	const int output_x = 10;
//	int output_y = 0;
//
//	win.create_output();
//	WINDOW *output_win = win.get_output();
//
//	while(1)
//	{
//		int y,x;
//		getmaxyx(output_win,y,x);
//		index = index%(y-1);
//		index = index <1?1:index;
//		output_y = index;
//		win.put_str_to_win(output_win,output_y,output_x,msg.c_str());
//		win.win_refresh(output_win);
//		usleep(1000000);
//		index++;
//		if(index == (y - 1))
//		{
//			win.clear_win_line(output_win,1,y-2);
//			win.create_output();
//			output_win = win.get_output();
//		}
//	}
//	return NULL;
//}
//
//void* run_friendlist(void *arg)
//{
//	pthread_detach(pthread_self());
//	while(1)
//	{
//		win.create_friendlist();
//		int y,x;
//		WINDOW *friendlist_win = win.get_friendlist();
//		getmaxyx(friendlist_win,y,x);
//		int total = 56;
//		int total_page = total/15;
//		if(total%15 != 0)
//		{
//			total_page++;
//		}
//
//		std::string val;
//		std::string val1;
//		std::strstream ssl;
//		ssl<<total_page;
//		ssl>>val1;
//		for(int i = 1;i <= total_page;++i)
//		{
//			val = "";
//			std::strstream ss;
//			ss<<i;
//			ss>>val;
//			val += "/";
//			val += val1;
//			win.put_str_to_win(friendlist_win,y-2,x/2,val.c_str());
//			win.win_refresh(friendlist_win);
//			sleep(2);
//		}
//	}
//	return NULL;
//}
//int main()
//{
//	pthread_t header;
//	pthread_t output;
//	pthread_t friendlist;
//
//	pthread_create(&header,NULL,run_header,NULL);
//	pthread_create(&output,NULL,run_output,NULL);
//	pthread_create(&friendlist,NULL,run_friendlist,NULL);
//
//	std::string out;
//	while(1)
//	{
//		win.win_refresh(stdscr);
//		out = "";
//		win.create_input(out);
//		if(out == "quit" || out == "q")
//		{
//			pthread_cancel(header);
//			pthread_cancel(output);
//			pthread_cancel(friendlist);
//			break;
//		}
//		win.win_refresh(win.get_input());
//	}
//	return 0;
//}
