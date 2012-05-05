#include <pulseOximeter.h>
#include "ccpp_pulseox.h"
#define devid "deviceID"

using namespace DDS;
using namespace std;
namespace po = boost::program_options;
using namespace com::netspective::medigy;
stringstream temp,prtemp;
//string domainid,deviceid,loginfo,logdata,logconfpath;
//int splow,sphigh,pulselow,pulsehigh;


int alarmSubscribePulseOximeter(string domainid,string deviceid,string loginfo,string logdata,string logconfpath,int splow,int sphigh,int pulselow,int pulsehigh)
{

	/*Initializing SimpleDDS library*/	
	DataService *simpledds;
	PulseOximeterTypeSupport_var typesupport;
    	DataReader_ptr content_reader;
    	PulseOximeterDataReader_var bpReader;
    	ReturnCode_t status;
	int i=0;
        simpledds->logger->info(" PulseOximeter Alarm Subscriber Started");

	/*Setting QoS Properties for Topic*/
	DDS::TopicQos tQos;
	getQos(tQos);

	simpledds = new OpenSpliceDataService(tQos,loginfo,logconfpath);
	typesupport = new PulseOximeterTypeSupport();
        simpledds->logger->info(" PulseOximeter Alarm Subscriber Started");
	/*Creating content Filtered Subscriber*/
	StringSeq sSeqExpr;
        sSeqExpr.length(0);
	content_reader = simpledds->filteredSubscribe(typesupport, deviceid ,devid , deviceid,sSeqExpr);
    	bpReader = PulseOximeterDataReader::_narrow(content_reader);
   	PulseOximeterSeq  bpList;
     	SampleInfoSeq     infoSeq;
	simpledds->logger->info("pulse Oximeter Alarm Subscriber for %s",deviceid.c_str());
	simpledds->logger->info("Format: DOMAIN_ID, DEVICE_ID, MEASURED_TIME, SPO2 (LEVEL), PUSLERATE (LEVEL)");
	
	/*Receiving Data from DDS */	
	while (1) 
	{
         	status = bpReader->take(
            	bpList,
            	infoSeq,
            	LENGTH_UNLIMITED,
            	ANY_SAMPLE_STATE,
           	ANY_VIEW_STATE,
            	ANY_INSTANCE_STATE);
         	checkStatus(status, "take");
          	if (status == RETCODE_NO_DATA) 
		{
          		continue;
          	}
          	for (i = 0; i < bpList.length(); i++) 
	  	{

			if(infoSeq[i].valid_data)
			{
		if (bpList[i].SPO2 <  splow || bpList[i].SPO2 > sphigh || bpList[i].pulseRatePerMinute < pulselow || bpList[i].pulseRatePerMinute > pulsehigh)
				{
					prtemp <<bpList[i].deviceDomain<<COMMA<<bpList[i].deviceID<<COMMA<<bpList[i].timeOfMeasurement<<COMMA;
			 		prtemp <<alarmString(bpList[i].SPO2,splow,sphigh)<<COMMA<<alarmString(bpList[i].pulseRatePerMinute,pulselow,pulsehigh);
					simpledds->logger->info(prtemp.str().c_str());
					prtemp.str(CLEAN);
				}
				
			}

		}
		status = bpReader->return_loan(bpList, infoSeq);
        	checkStatus(status, "return_loan");
		
    	}

	simpledds->logger->info("PulseOximeter Alarm Subscriber Ends %s",deviceid.c_str());	
        /* We're done.  Delete everything */
        simpledds->deleteReader(content_reader);
        delete simpledds;
        return 0;


}

