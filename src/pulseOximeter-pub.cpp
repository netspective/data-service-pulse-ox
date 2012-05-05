#include <pulseOximeter.h>
#include "ccpp_pulseox.h"
#define devid "deviceID"


using namespace DDS;
using namespace std;
namespace po = boost::program_options;
using namespace com::netspective::medigy;

char buf[BUFFERSIZE], c;
int sizebuf,port;
//string domainid,deviceid,loginfo,logdata,logconfpath,hostip;
stringstream prtemp;

char* pulseRandomData()
{
        char send_data[1024],temp[1024];
        int spo2, pulseox;

        strcpy(send_data,"");
        strcpy(temp,"");

        spo2 = rand()%30+70;
        pulseox = rand()%40+55;

        sprintf(temp, "%d", time(0));
        strcat(send_data,temp);

        sprintf(temp, "%d", spo2);
        strcat(send_data,":");
        strcat(send_data,temp);

        sprintf(temp, "%d", pulseox);
        strcat(send_data,":");
        strcat(send_data,temp);
	
        return send_data;

}

int publishPulseOximeter(string deviceid,string domainid,string loginfo,string logdata,string logconfpath)
{

	

       	
	/*Initializing SimpleDDS library*/
	DataService *simpledds;
	PulseOximeterTypeSupport_var typesupport;
	DataWriter_ptr writer;
	PulseOximeterDataWriter_var bpWriter;

	/*Setting QoS Properties for Topic*/
	DDS::TopicQos tQos;
	getQos(tQos);
	simpledds = new OpenSpliceDataService(tQos,loginfo,logconfpath);
	typesupport = new PulseOximeterTypeSupport();
	writer = simpledds->publish(typesupport);
	bpWriter = PulseOximeterDataWriter::_narrow(writer);
	simpledds->logger->info(" Pulse Oximeter Publisher Started %s",deviceid.c_str());

	/*Sending Command To Data Generator*/
	strcpy(buf,"PULSEOX");
	PulseOximeter data;

	/*Storing Domain and Device ID*/
	data.deviceID = DDS::string_dup(deviceid.c_str());
	data.deviceDomain = DDS::string_dup(domainid.c_str());
	simpledds->logger->info("Pulse Oximeter  Started Publishing Data In DDS");
        simpledds->logger->info("Format: TIMEOFMEASURED, OXYGEN_SATURATION, PULSERATE");

	while (1) 
	{

			strcpy(buf,pulseRandomData());
			char * pch;
			pch = strtok (buf,SEMI);
			data.timeOfMeasurement = atol(pch);
			prtemp<<data.timeOfMeasurement<<COMMA;
			pch = strtok (NULL,SEMI);
			data.SPO2 = (short)atoi(pch);		
			prtemp<<data.SPO2<<COMMA;
			pch = strtok (NULL,SEMI);
			data.pulseRatePerMinute = (short)atoi (pch);
			prtemp<<data.pulseRatePerMinute;
			bpWriter->write(data, NULL);
			simpledds->logger->info(prtemp.str().c_str());
			sleep(1);
			prtemp.str(CLEAN);
		
	}

	/*Deleting SimpleDDS Instance*/
	simpledds->logger->info("Pulse Oximeter Publisher Ends %s",deviceid.c_str());
	simpledds->deleteWriter(writer);
	delete simpledds;
	return 0;
}
