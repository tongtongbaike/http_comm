#include "comm.h"

void print_log(string error_msg,string function.int line)
{
	printf("the msg : [ %s ] function: [ %s ] line: [ %d ]",error_msg,function,line);	
}

void usage()
{
	printf("you mus be have [IP] [PORT]\n");
}
