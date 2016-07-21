#include "my_json.h"

my_json::my_json(){}
my_json::~my_json(){}

int my_json::serialization(string &_msg,Json::Value &in_val)
{
#ifdef _DEBUG_
	Json::FastWriter write;
	_msg = write.write(in_val);	
#else
	Json::StyledWriter write;
	_msg = write.write(in_val);
#endif	
}

int my_json::deserialization(string &_msg,Json::Value &out_val)
{
	Json::Reader read;
	read.parse(_msg,out_val,false);
}
