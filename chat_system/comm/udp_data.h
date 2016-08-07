#pragma once 

#include <iostream>
#include <string>
#include <json/json.h>
#include "my_json.h"

class udp_data
{
public:

	void get_nick_name(std::string& _out);
	void get_school(std::string& _out);
	void get_msg(std::string& _out);
	void get_cmd(std::string& _out);

	void set_nick_name(const std::string& _in);
	void set_school(const std::string& _in);
	void set_msg(const std::string& _in);
	void set_cmd(const std::string& _in);

	void serialize(std::string &out) ;
	void unserialize(const std::string &in) ;

private:
	std::string nick_name;		
	std::string school;		
	std::string msg;		
	std::string cmd;		                      		
};


