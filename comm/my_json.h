#pragma once
#include <iostream>
#include <string>
#include "json/json.h"
using namespace std;

class my_json
{
	public:
		my_json();
		~my_json();

		static int serialization(string &_msg,Json::Value &in_val);
		static int deserialization(string &_msg,Json::Value &out_val);
		
//		void set_val(const Json::Value &val);
//		void set_string(const string &str);
//		const Json::Value &get_val();
//		const string& get_string(); 	
	private:
		//json::value _val;	
		//string _str;
};



