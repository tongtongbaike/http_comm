#pragma once
#include<iostream>
#include<pthread.h>
#include<string>
#include<ncurses.h>
#include<string.h>
#include<strstream>
#include "../comm/comm.h"
class chat_window
{
	public:
		chat_window();
		~chat_window();
		void create_header();
		void create_output();
		void create_friendlist();
		void create_input();
		void win_refresh(WINDOW *win);
		void clear_win_line(WINDOW *win,int begin,int line);
		void destroy_win(WINDOW *local_win);
		std::string get_input_msg(WINDOW *win);
		void put_str_to_win(WINDOW *win,int starty,int startx,const std::string &msg);
		WINDOW *create_newwin(int heigth,int width,int starty,int startx);
		WINDOW *get_header();
		WINDOW *get_output();
		WINDOW *get_friendlist();
		WINDOW *get_input();
	private:
		WINDOW *header;
		WINDOW *output;
		WINDOW *friendlist;
		WINDOW *input;
		const unsigned int _size;
};
