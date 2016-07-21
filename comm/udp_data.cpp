#include "udp_data.h"


udp_data::udp_data()
{}

udp_data::~udp_data()
{}

void udp_data::val_to_string(std::string &_in_nick_name,std::string &_in_msg, std::string &_in_school, std::string &_in_cmd, std::string &_out_str)
{
	nick_name = _in_nick_name;
	msg       = _in_msg;
	school    = _in_school;
	cmd       = _in_cmd;

	Json::Value in_val;
	in_val["nick_name"] = _in_nick_name;
	in_val["school"] = _in_school;
	in_val["msg"] = _in_msg;
	in_val["cmd"] = _in_cmd;
	my_json::serialization(_out_str,in_val);
	
}

void udp_data::string_to_val(std::string &_out_nick_name,std::string &_out_msg, std::string &_out_school, std::string &_out_cmd, std::string &_in_str)
{
	Json::Value _val;
	my_json::deserialization( _in_str, _val);
	
	_out_nick_name = _val["nick_name"].asString();
	_out_msg       = _val["msg"].asString();
	_out_school    = _val["school"].asString();
	_out_cmd       = _val["cmd"].asString();
	nick_name = _out_nick_name;
	msg       = _out_msg;
	school    = _out_school;
	cmd       = _out_cmd;
}


void  udp_data::print_data()
{
	cout<<"nick_name:"<<nick_name<<"\nschool:"<<school<<"\nmsg"<<msg<<"\ncmd"<<cmd<<endl;
}


//int main()
//{
//	string name  = "name";
//	string school = "xpu";
//	string msg = "nihaoma";
//	string cmd = "none";
//	udp_data data_s(name,school,msg,cmd);
//	string _msg;
//	data_s.val_to_str(_msg);
//	data_s.str_to_val(_msg);
//	data_s.print_data();
//	return 0;
//}
