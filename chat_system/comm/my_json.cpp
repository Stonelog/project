#include "my_json.h"

void my_json::serialize(Json::Value& _val ,std::string& out) 
{
	//Json::StyledWriter _write;
	Json::FastWriter _write;
	out = _write.write(_val);
}

void my_json::unserialize(Json::Value& _val ,const std::string& in) 
{
	Json::Reader _read;
	_read.parse(in ,_val ,false);
}


