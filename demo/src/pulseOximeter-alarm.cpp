#include <boost/program_options.hpp>
#include <pulseOximeter.h>
#include<Functions.h>

string _domainid,_deviceid,_loginfo,_logdata,_logconfpath;
int _splow,_sphigh,_pulselow,_pulsehigh;

int main(int argc, char* argv[]) 
{
	if (!parse_args_pulse_alarm(argc, argv,_domainid,_deviceid,_loginfo,_logdata,_logconfpath,_splow,_sphigh,_pulselow,_pulsehigh))
    	return 1;
	
	alarmSubscribePulseOximeter(_domainid,_deviceid,_loginfo,_logdata,_logconfpath,_splow,_sphigh,_pulselow,_pulsehigh);
	return 0;
}

