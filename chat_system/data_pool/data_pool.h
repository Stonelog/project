#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <semaphore.h>
#include <pthread.h>

class data_pool
{
public:
	data_pool(int  _size = 128);

	void data_get(std::string &_out);

	void data_put(const std::string &msg);

	~data_pool();

private:

	std::vector<std::string> pool;
	int cap;

	int index_pro;
	int index_com;

	pthread_mutex_t lock;
	sem_t blank_sem;
	sem_t data_sem;
};



