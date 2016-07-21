#pragma once
#include<iostream>
#include<string>
#include "my_json.h"

using namespace std;

class udp_data
{
	public:
		udp_data();
		udp_data(string &nickname,string &school,string &msg,string &cmd);
		~udp_data();
		void val_to_string(std::string &_in_nick_name,std::string &_in_msg, std::string &_in_school, std::string &_in_cmd, std::string &_out_str);
		void print_data();
		void string_to_val(std::string &_out_nick_name,std::string &_out_msg, std::string &_out_school, std::string &_out_cmd, std::string &_in_str);
	private:
		string school;
		string nick_name;
		string cmd;
		string msg;
};
