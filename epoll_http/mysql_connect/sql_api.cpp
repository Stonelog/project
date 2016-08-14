
#include "sql_api.h"

sql_api::sql_api(const std::string &_host,const std::string &_user,const std::string &_passwd, const std::string & _db,const  int _port)
	: host(_host)
	, user(_user)
	, passwd(_passwd)
	, db(_db)
	, port(_port)
{
	this->conn = mysql_init(NULL);
}

int sql_api::my_connect()
{
	mysql_real_connect(conn,host.c_str(),user.c_str(),passwd.c_str(),db.c_str(),port,NULL,0);

	mysql_set_character_set(conn,"utf8");
}

int sql_api::my_insert(const std::string &table, const std::string &filed, const std::string &values)
{
	mysql_set_character_set(conn, "gbk");

	std::string sql = "INSERT INTO ";
	sql += table;
	sql += " ";
	sql += filed;
	sql += " ";
	sql += " values ";
	sql += values;
	sql += " ";
	
	int ret	= mysql_query(conn,sql.c_str());
	if (ret == 0)
	{
		std::cout << "INSERT SUCCESS " <<  std::endl;
	}
}

int sql_api::my_select(const std::string & table)
{
	std::string sql = "select * from ";
	sql += table;
	sql += " ";

	MYSQL_RES *res;
	MYSQL_ROW row;

	if (mysql_query(conn, sql.c_str()))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
	    exit(0);
	}

	res = mysql_store_result(conn);

//	int row_num = mysql_num_rows(res);
//	int field_num = mysql_num_fields(res);

	MYSQL_FIELD *fd = NULL;
	int i = 0;
	for(; fd = mysql_fetch_field(res); )
	{
		std::cout << fd->name << "&nbsp;&nbsp;";
	//	std::cout << fd->name << "	";
	}
	std::cout << "<br/> "<<std::endl;
	//std::cout <<std::endl;

	while ((row = mysql_fetch_row(res)) != NULL)	
	{
		unsigned int  len = mysql_field_count(conn);
		int i = 0;

		for ( ; i < len ; ++i)
		{
			std::cout << row[i] << " &nbsp;&nbsp; " ;
	//		std::cout << row[i] << "	 " ;
		}
		std::cout << "<br/>"<< std::endl;
	}

	mysql_free_result(res);
}

sql_api::~sql_api()
{
	mysql_close(conn);
}

//int main()
//{
//	sql_api *sql =  new sql_api();
//
//	sql->my_connect();
//
//	std::string table = "student";
//	std::string filed = "(name, sex,age,school)";
//	std::string values = "('小华', '女',23,'q')";
//	sql->my_insert(table,filed,values);
//
//	sql->my_select(table);
//
//	return 0;
//}



