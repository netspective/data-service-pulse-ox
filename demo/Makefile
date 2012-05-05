# Makefile 

# The top level directory
TOPDIR := $(shell pwd)

# The source directory locations
IDL_DIR=$(TOPDIR)/idl
CPP_DIR=$(TOPDIR)
CPP_LIB_DIR=$(TOPDIR)/lib
pulseox_LIB=$(TOPDIR)/../lib

# The C/C++ compilers to use
#CPP=/usr/bin/g++ 
CPP=/usr/bin/g++
IDLPP= idlpp

# The C/C++ compiler flags
CPPFLAGS= -g -Wall -I/opt/mongo-cxx-driver-v1.8/mongo/client -I$(OSPL_HOME)/include/dcps/C++/SACPP -I$(OSPL_HOME)/include -I$(OSPL_HOME)/include/sys -I$(CPP_LIB_DIR)
LDFLAGS= -L/opt/mongo-cxx-driver-v1.8 -L/lib64 -L$(OSPL_HOME)/lib -L/usr/lib -Wl,-rpath,$(OSPL_HOME)/lib
LIBS=  -lboost_thread -lboost_program_options -lboost_system -ldcpsgapi -ldcpssacpp -lddsdatabase -lddsos  /lib/libsimpledds.a -lpulseoximeter /lib/liblogger.a

# Boost Libraries is used by the  publisher/generator examples
#BOOST_LIBS= -lboost_thread -lboost_program_options -lboost_system

# The target programs to build
TARGETS= \
	$(CPP_DIR)/bin/pulseox-pub \
	$(CPP_DIR)/bin/pulseox-echo \
	$(CPP_DIR)/bin/pulseox-alarm \
	$(CPP_DIR)/bin/pulseox-persist



all: $(TARGETS)

clean: 
	rm -f $(TOPDIR)/bin/*; \
	rm -f $(TOPDIR)/src/*.o;


# Compile the pulseOximeterPublish binary
$(CPP_DIR)/bin/pulseox-pub:
	cd $(CPP_DIR)/src; \
	$(CPP) $(CPPFLAGS) -c $(CPP_DIR)/src/pulseOximeter-pub.cpp; \
        $(CPP) $(LDFLAGS) $(LIBS) $(BOOST_LIBS)  -llog4cpp -o $(TOPDIR)/bin/pulseox-pub $(CPP_DIR)/src/pulseOximeter-pub.o /lib/libpulseoximeter.a $(pulseox_LIB)/gen/pulseox/libpulseox.a $(LIBS);

# Compile the pulseOximeterPublish binary
$(CPP_DIR)/bin/pulseox-echo:
	cd $(CPP_DIR)/src; \
        $(CPP) $(CPPFLAGS) -c $(CPP_DIR)/src/pulseOximeter-echo.cpp; \
        $(CPP) $(LDFLAGS) $(LIBS) $(BOOST_LIBS)  -llog4cpp -o $(TOPDIR)/bin/pulseox-echo $(CPP_DIR)/src/pulseOximeter-echo.o /lib/libpulseoximeter.a $(pulseox_LIB)/gen/pulseox/libpulseox.a $(LIBS);

# Compile the pulseOximeterPublish binary
$(CPP_DIR)/bin/pulseox-alarm:
	cd $(CPP_DIR)/src; \
        $(CPP) $(CPPFLAGS) -c $(CPP_DIR)/src/pulseOximeter-alarm.cpp; \
        $(CPP) $(LDFLAGS) $(LIBS) $(BOOST_LIBS)  -llog4cpp -o $(TOPDIR)/bin/pulseox-alarm $(CPP_DIR)/src/pulseOximeter-alarm.o /lib/libpulseoximeter.a $(pulseox_LIB)/gen/pulseox/libpulseox.a $(LIBS);

# Compile the pulseOximeterPublish binary
$(CPP_DIR)/bin/pulseox-persist:
	cd $(CPP_DIR)/src; \
        $(CPP) $(CPPFLAGS) -c $(CPP_DIR)/src/pulseOximeter-persist.cpp; \
        $(CPP) $(LDFLAGS) $(LIBS) $(BOOST_LIBS)  -llog4cpp -lmongoclient -o $(TOPDIR)/bin/pulseox-persist $(CPP_DIR)/src/pulseOximeter-persist.o /lib/libpulseoximeter.a $(pulseox_LIB)/gen/pulseox/libpulseox.a $(LIBS);
 
