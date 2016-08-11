#include "udp_data.h" 

void udp_data::get_nick_name(std::string& _out)
{
	_out = nick_name;
}
void udp_data::get_school(std::string& _out)
{
	_out = school;
}
void udp_data::get_msg(std::string& _out)
{
	_out = msg;
}
void udp_data::get_cmd(std::string& _out)
{
	_out = cmd;
}

void udp_data::set_nick_name(const std::string& _in)
{
	nick_name = _in;
}
void udp_data::set_school(const std::string& _in)
{
	school = _in;
}
void udp_data::set_msg(const std::string& _in)
{
	msg = _in;
}
void udp_data::set_cmd(const std::string& _in)
{
	cmd = _in;
}

void udp_data::serialize(std::string &out) 
{
	Json::Value _val;
	_val["nick_name"] = nick_name;
	_val["school"] = school;
	_val["msg"] = msg;
	_val["cmd"] = cmd;

	 my_json::serialize(_val , out);
}

void udp_data::unserialize(const std::string &in)
{
	Json::Value _val;
	my_json::unserialize(_val , in);

	nick_name  = _val["nick_name"].asString();
	school = _val["school"].asString() ;
	msg = _val["msg"].asString() ;
	cmd = _val["cmd"].asString() ;
}


