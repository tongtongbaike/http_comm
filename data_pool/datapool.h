#include<iostream>
#include<vector>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#define _DATA_SIZE_ 256
using namespace std;

class data_pool
{
	public:
		data_pool();
		~data_pool();
		void pool_push(string &msg);
		void   pool_pop(string &msg);
	private:
		vector<std::string> datapools;
		sem_t sem_product;
		sem_t sem_consumer;
		pthread_mutex_t mutex_product;
		pthread_mutex_t mutex_consumer;
		int product_index;
		int customer_index;
};

