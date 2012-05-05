#include <boost/program_options.hpp>
#include <pulseOximeter.h>
#include<Functions.h>
string _domainid,_deviceid,_loginfo,_logdata,_logconfpath,_host,_database;

int main(int argc, char* argv[]) 
{
	if (!parse_args_sub_persist(argc, argv,_domainid,_deviceid,_loginfo,_logdata,_logconfpath,_host,_database))
    	return 1;

	persistSubscribePulseOximeter(_domainid,_deviceid,_loginfo,_logdata,_logconfpath,_host,_database);
	return 0;
}

