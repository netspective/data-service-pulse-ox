#include <stdio.h>
#include <string>
#include <iostream>
#include "Functions.h"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
namespace po = boost::program_options;



bool parse_args_pub(int argc, char* argv[],string &domainid,string &deviceid,string &loginfo,string &logdata,string &logconfpath)
{
  po::options_description desc("Available options for are");
  desc.add_options()
    ("help", "produce help message")
    ("domain", po::value<std::string>(), "Device Domain ")
    ("device-id",po::value<std::string>(), "Device ID - for device identification")
    ("log-info", po::value<std::string>(), "Log Info Specification")
    ("log-data", po::value<std::string>(), "Log Data Specification ")
    ("log4cpp-conf", po::value<std::string>(), "Log Configration and Format specification file")
    ;
 
  try {
    po::variables_map vm;        
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    
   
    if (vm.count("help") || argc == 1) {
      std::cout << desc << "\n";
      return false;
    }
    
    if (vm.count("domain")) 
      domainid = vm["domain"].as<std::string>();
    if (vm.count("device-id")) 
      deviceid = vm["device-id"].as<std::string>();
    if (vm.count("log-info")) 
      loginfo = vm["log-info"].as<std::string>();
    if (vm.count("log-data")) 
      logdata = vm["log-data"].as<std::string>();
    if (vm.count("log4cpp-conf")) 
      logconfpath = vm["log4cpp-conf"].as<std::string>();
    
  } 
  catch (...) {
    std::cout << desc << "\n";
    return false;
  }
  return true;
}

bool parse_args_sub(int argc, char* argv[],string &domainid,string &deviceid,string &loginfo,string &logdata,string &logconfpath)
{
  po::options_description desc("Available options for are");
  desc.add_options()
    ("help", "produce help message")
    ("domain", po::value<std::string>(), "Device Domain")
    ("device-id",po::value<std::string>(), "Device ID for identification")
    ("log-info", po::value<std::string>(), "Log Info Specification")
    ("log-data", po::value<std::string>(), "Log data Specification ")
    ("log4cpp-conf", po::value<std::string>(), "Log Configration and Format specification file")
    ;

  try {
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") || argc == 1) {
      std::cout << desc << "\n";
      return false;
    }

    if (vm.count("domain"))
      domainid = vm["domain"].as<std::string>();
    if (vm.count("device-id"))
      deviceid = vm["device-id"].as<std::string>();
    if (vm.count("log-info"))
      loginfo = vm["log-info"].as<std::string>();
    if (vm.count("log-data"))
      logdata = vm["log-data"].as<std::string>();
    if (vm.count("log4cpp-conf"))
      logconfpath = vm["log4cpp-conf"].as<std::string>();
	   

    }
  
  catch (...) {
    std::cout << desc << "\n";
    return false;
  }
  return true;
}

bool parse_args_sub_persist(int argc, char* argv[],string &domainid,string &deviceid,string &loginfo,string &logdata,string &logconfpath, string &host, string &database) {

  po::options_description desc("Available options for are");
  desc.add_options()
    ("help", "produce help message")
    ("domain", po::value<std::string>(), "Device Domain")
    ("device-id",po::value<std::string>(), "Device ID for identification")
    ("log-info", po::value<std::string>(), "Log Info Specification")
    ("log-data", po::value<std::string>(), "Log data Specification ")
    ("log4cpp-conf", po::value<std::string>(), "Log Configration and Format specification file")
    ("host", po::value<std::string>(), "Database Host")
    ("database", po::value<std::string>(), "Database Name")
    ;

  try {
        po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help") || argc == 1) {
		std::cout << desc << "\n";
		return false;
	}

	if (vm.count("domain"))
		domainid = vm["domain"].as<std::string>();
	if (vm.count("device-id"))
		deviceid = vm["device-id"].as<std::string>();
	if (vm.count("log-info"))
		loginfo = vm["log-info"].as<std::string>();
	if (vm.count("log-data"))
		logdata = vm["log-data"].as<std::string>();
	if (vm.count("log4cpp-conf"))
		logconfpath = vm["log4cpp-conf"].as<std::string>();
	if (vm.count("host"))
		host = vm["host"].as<std::string>();
	if (vm.count("database"))
		database = vm["database"].as<std::string>();


  }
  catch (...) {
    std::cout << desc << "\n";
    return false;
 }
  return true;

}


bool parse_args_pulse_alarm(int argc, char* argv[],string &domainid,string &deviceid,string &loginfo,string &logdata,string &logconfpath,int &splow,int &sphigh,int &pulselow,int &pulsehigh)
{
  po::options_description desc("Available options for <pulseoximeter-alarm> are");
  desc.add_options()
    ("help", "produce help message")
    ("domain", po::value<std::string>(), "Device Domain")
    ("device-id",po::value<std::string>(), "Device ID for identification")
    ("log-info", po::value<std::string>(), "Log Info Specification")
    ("log-data", po::value<std::string>(), "Log data Specification ")
    ("log4cpp-conf", po::value<std::string>(), "Log Configration and Format specification file")
    ("spo2-low", po::value<int>(), "SPO2 Low level Alarm Alarm Specification - default <88")
    ("spo2-high", po::value<int>(), "SPO2 High Level Alarm Specification - default >92")
    ("pulse-low", po::value<int>(), "Temperature Low level Alarm Alarm Specification - default <90")
    ("pulse-high", po::value<int>(), "Temperature High Level Alarm Specification - default >105")
    ;

  try {
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") || argc == 1) {
      std::cout << desc << "\n";
      return false;
    }
    
    if (vm.count("domain"))
      domainid = vm["domain"].as<std::string>();
    if (vm.count("device-id"))
      deviceid = vm["device-id"].as<std::string>();
    if (vm.count("log-info")) 
      loginfo = vm["log-info"].as<std::string>();
    if (vm.count("log-data")) 
      logdata = vm["log-data"].as<std::string>();
    if (vm.count("log4cpp-conf")) 
      logconfpath = vm["log4cpp-conf"].as<std::string>();
    if (vm.count("spo2-low"))
      splow = vm["spo2-low"].as<int>();
    if (vm.count("spo2-high"))
      sphigh = vm["spo2-high"].as<int>();
    if (vm.count("pulse-low"))
      pulselow = vm["pulse-low"].as<int>();
    if (vm.count("pulse-high"))
      pulsehigh = vm["pulse-high"].as<int>();
	
    
    }
  
  catch (...) {
    std::cout << desc << "\n";
    return false;
  }
  return true;
} 


string alarmString(int value,int min,int max)
{
	stringstream temp;
	temp<<value;
	if(value < min)
	temp<<" (LOW)";
	else if(value > max)
	temp<<" (HIGH)";
	else
	temp<<" (NORMAL)";
	return temp.str();
}





