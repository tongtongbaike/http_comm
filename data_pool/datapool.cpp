#include"datapool.h"

data_pool::data_pool()
	:datapools(_DATA_SIZE_)
	,product_index(0)
	,customer_index(0)
{
	
//	mutex_product = PTHREAD_MUTEX_INITIALIZER;
//	mutex_consumer = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&mutex_product,NULL);
	pthread_mutex_init(&mutex_consumer,NULL);
	sem_init(&sem_product,0,datapools.size());
	sem_init(&sem_consumer,0,0);
}
data_pool::~data_pool()
{
	pthread_mutex_destroy(&mutex_product);
	pthread_mutex_destroy(&mutex_consumer);
}

void data_pool::pool_push(string &msg)
{
	sem_wait(&sem_product);
	pthread_mutex_lock(&mutex_product);
	datapools[product_index]= msg;
	++product_index;
	product_index %= _DATA_SIZE_;
	pthread_mutex_unlock(&mutex_product);
	sem_post(&sem_consumer);
}
void  data_pool::pool_pop(string &msg)
{
	sem_wait(&sem_consumer);
	pthread_mutex_lock(&mutex_consumer);
	msg = datapools[customer_index];
	++customer_index;
	customer_index %= _DATA_SIZE_;
	pthread_mutex_unlock(&mutex_consumer);
	sem_post(&sem_product);
}
