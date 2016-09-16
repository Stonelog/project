#pragma once

#include <iostream>
using namespace std;
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "mysql.h"

class sql_api
{
	public:
		sql_api(const std::string &_host = "127.0.0.1",const std::string &_user = "root",const std::string &_passwd = "",const std::string & _db = "test", const int _port = 3306);
		//sql_api(std::string &_host,std::string &_user,std::string &_passwd, std::string & _db, int _port);

		int my_connect();

		int my_insert(const std::string &table, const std::string &filed, const std::string &values);

		int my_select(const std::string & table);

		//int my_close();

		~sql_api();

	private:
		MYSQL			*conn;
		std::string		host;
		std::string		user;
		std::string		passwd;
		std::string		db;
		int				port;

};




