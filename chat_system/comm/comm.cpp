#include "comm.h"

void print_log(const char* err , const char* fun, int line )
{
	std::cout << err  <<" ,["<<fun<<"] , "<<" ["<<line<<"]"<<std::endl; 
}


