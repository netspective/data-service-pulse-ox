#include <boost/program_options.hpp>
#include <pulseOximeter.h>
#include <Functions.h>



int main(int argc, char* argv[]) 
{
	string _domainid,_deviceid,_loginfo,_logdata,_logconfpath;

	if (!parse_args_pub(argc, argv,_domainid,_deviceid,_loginfo,_logdata,_logconfpath))
	return 1;

	publishPulseOximeter(_deviceid,_domainid,_loginfo,_logdata,_logconfpath);
	return 0;
}

