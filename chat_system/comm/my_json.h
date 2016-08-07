#pragma once

#include <iostream>
#include <json/json.h>

class my_json
{
public:

	static	void serialize(Json::Value &_val ,std::string &out);

	static  void unserialize(Json::Value &_val ,const std::string &in);

};


