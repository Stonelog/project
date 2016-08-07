#include "data_pool.h"
#include <pthread.h>

data_pool::data_pool(int _size)
	:pool(_size)
	 ,cap(_size)
	 ,index_pro(0)
	 ,index_com(0)
{
	sem_init(&blank_sem , 0, _size);
	sem_init(&data_sem , 0 , 0);
    pthread_mutex_init(&lock,NULL);	
}

void data_pool::data_get(std::string &_out)
{
	sem_wait(&data_sem);

	pthread_mutex_lock(&lock);
	_out = pool[index_com];
	++index_com;
	index_com %= cap;
	pthread_mutex_unlock(&lock);

	sem_post(&blank_sem);
}

void data_pool::data_put(const std::string &msg)
{
	sem_wait(&blank_sem);

	pthread_mutex_lock(&lock);
	pool[index_pro] = msg;
	++index_pro;
	index_pro %= cap;
	pthread_mutex_unlock(&lock);

	sem_post(&data_sem);
}

data_pool::~data_pool()
{
	sem_destroy(&blank_sem);
	sem_destroy(&data_sem);
	pthread_mutex_destroy(&lock);
}


