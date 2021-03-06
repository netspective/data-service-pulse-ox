# PulseOximeter Library

PulseOximeter library is intended to greatly simplify the use of PulseOximeter device simulation with DDS. As such, PulseOximeter library have functions that reduces by several times the line of code that need to be written for a creating PulseOximeter Simulation DDS application. 

# Prerequisite

[Setting Up Logging Service](https://github.com/netspective/commons-logging-cpp/blob/master/README.md)

# Compilation and Installation
Clone the library from the github

	git clone git@github.com:netspective/data-service-pulse-ox.git
	
	cd data-service-pulse-ox

Compiling
	
	make

Installing
	
	make install 

	or 

	make install PREFIX=<installation path>



## Simplified Functions
Following are PulseOximeter functions and their descriptions

Note: Refer the demo programs for reference

#### Running Publisher 

SYNOPSIS

	int publishPulseOximeter(string deviceid,string domainid,string loginfo,string logdata,string logconfpath);

DESCRIPTION

	The publish function used to publish the Pulse ox  data in the DDS. 

ARGUMENTS

	domain             Device Domain 

	device-id          Device ID - for device identification

	log-info           Log information category

	lod-data           Log data file 

	log4cpp-conf       Log configuration and format specification file


#### Echo Subscribers

SYNOPSIS

	int echoSubscribePulseOximeter(string deviceid,string domainid,string loginfo,string logdata,string logconfpath);

DESCRIPTION

This function is used to subscribe and join the PulseOximeter topic. Log4cpp config is used to maintain the logs and thier path.
 
ARGUMENTS

	domain             Device Domain 

	device-id          Device ID - for device identification

	log-info           Log information category

	lod-data           Log data file 

	log4cpp-conf       Log configuration and format specification file


#### Alarm Subscriber

SYNOPSIS

	int alarmSubscribePulseOximeter(string  domainid,string deviceid,int sysmin,int sysmax,int dismin,int dismax,int pulsemin,int pulsemax,string loginfo,string logdata,string logconfpath);


DESCRIPTION

This function is used to subscribe and join the PulseOximeter topic with alarm notification. Log4cpp config is used to maintain the logs and thier path.

 
ARGUMENTS


	domain               Device Domain

	device-id            Device ID for identification

	log-info             Log information category

	log-data             Log data category 

	log4cpp-conf         Log configuration and format specification file

	spo2-low	     SPO2 low level alarm specification - default <88

	spo2-high	     SPO2 high level alarm specification - default >92
	
	pulse-low 	     Temperature Low level Alarm Alarm Specification - default <90

    	pulse-high 	     Temperature High Level Alarm Specification - default >105

#### Persistance Subscriber

SYNOPSIS

	int persistSubscribePulseOximeter(string domainid,string deviceid,string loginfo,string logdata,string logconfpath,string host,string database);

DESCRIPTION

This function is used to subscribe and join the PulseOximeter topic and store the output in the MongoDB database notification. Log4cpp config is used to maintain the logs and thier path.
 
ARGUMENTS

	domain           Device Domain

	device-id        Device ID for identification

	host             Host Ip_Address

	database         Database Name

	log-info         Log information category

	log-data         Log data category

	log4cpp-conf     Log configuration and format specification file
