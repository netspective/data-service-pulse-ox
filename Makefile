# Makefile 

# The top level directory
TOPDIR := $(shell pwd)

# The source directory locations
IDL_DIR=$(TOPDIR)/idl
CPP_DIR=$(TOPDIR)
CPP_LIB_DIR=$(TOPDIR)/lib

ifeq ($(strip $(PREFIX)),)

        TARGET_PATH=$(TOPDIR)
else
        TARGET_PATH=$(PREFIX)
endif


# The C/C++ compilers to use
#CPP=/usr/bin/g++ 
CPP=/usr/bin/g++
IDLPP= idlpp

# The C/C++ compiler flags
CPPFLAGS= -g -Wall -I/opt/mongo-cxx-driver-v1.8/mongo/client -I$(OSPL_HOME)/include/dcps/C++/SACPP -I$(OSPL_HOME)/include -I$(OSPL_HOME)/include/sys -I$(CPP_LIB_DIR)
LDFLAGS= -L/opt/mongo-cxx-driver-v1.8 -L/lib64 -L$(OSPL_HOME)/lib -L/usr/lib -Wl,-rpath,$(OSPL_HOME)/lib
LIBS= -ldcpsgapi -ldcpssacpp -lddsdatabase -lddsos  -lsimpledds

# Boost Libraries is used by the  publisher/generator examples
BOOST_LIBS= -lboost_thread -lboost_program_options -lboost_system

# The target programs to build
TARGETS= \
	$(CPP_DIR)/bin/pulseox-pub \
	$(CPP_DIR)/bin/pulseox-sub-echo \
	$(CPP_DIR)/bin/pulseox-sub-alarm \
	$(CPP_DIR)/bin/pulseox-sub-persist \
	$(CPP_DIR)/bin/lib

INSTALL_TARGETS= \
	pulseox_install



# Build all targets
all: check_idlpp $(TARGETS)

install: $(INSTALL_TARGETS)

# Clean all files, including C++ generated from IDL
clean:
	rm -f /lib//libpulseoximeter.so;  \
	rm -f /usr/include/pulseOximeter.h;  \
	rm -f /usr/include/Functions.h;  \
	rm -f $(CPP_DIR)/lib/gen/pulseox/*;  \
	rm -f $(CPP_DIR)/*.a;  \
	rm -f $(CPP_DIR)/src/*.o;  \
	rm -f $(CPP_DIR)/lib/*.o; \
	rm -f $(TOPDIR)/bin/*
	rm -f $(TARGETS)

# Check that the idlpp compiler is in the current path
check_idlpp:
	@$(IDLPP) | grep Usage > /dev/null;


# Generate the pulseox C++ source files from the IDL
$(CPP_DIR)/lib/gen/pulseox/pulseox.h:
	mkdir -p $(CPP_DIR)/lib/gen/pulseox; \
	cd ${IDL_DIR}; $(IDLPP) -S -l cpp -d $(CPP_DIR)/lib/gen/pulseox pulseox.idl; 

# Compile the pulseox IDL-generated C++ files into libpulseox.a
$(CPP_DIR)/lib/gen/pulseox/libpulseox.a: $(CPP_DIR)/lib/gen/pulseox/pulseox.h
	cd $(CPP_DIR)/lib/gen/pulseox; \
	$(CPP) $(CPPFLAGS) -c pulseox.cpp; \
        $(CPP) $(CPPFLAGS) -c pulseoxDcps.cpp; \
        $(CPP) $(CPPFLAGS) -c pulseoxDcps_impl.cpp; \
        $(CPP) $(CPPFLAGS) -c pulseoxSplDcps.cpp; \
        ar cr libpulseox.a pulseox.o pulseoxDcps.o pulseoxDcps_impl.o pulseoxSplDcps.o; \
        ranlib libpulseox.a

# Compile the Functions helper class
Functions.o: $(CPP_LIB_DIR)/Functions.cpp
	$(CPP) $(CPPFLAGS) -c $(CPP_LIB_DIR)/Functions.cpp


# Compile the pulseoxOximeterPublish binary
$(CPP_DIR)/bin/pulseox-pub: $(CPP_DIR)/lib/gen/pulseox/libpulseox.a $(CPP_LIB_DIR)/Functions.o
	cd $(CPP_DIR)/src; \
	$(CPP) $(CPPFLAGS) -I$(CPP_DIR)/lib/gen/pulseox -c $(CPP_DIR)/src/pulseOximeter-pub.cpp -o  $(CPP_DIR)/src/pulseOximeter-pub.o $(LDFLAGS) $(LIBS); 

# Compile the pulseoxOximeterSubscribe binary
$(CPP_DIR)/bin/pulseox-sub-echo: $(CPP_DIR)/lib/gen/pulseox/libpulseox.a $(CPP_LIB_DIR)/Functions.o
	cd $(CPP_DIR)/src; \
	$(CPP) $(CPPFLAGS) -I$(CPP_DIR)/lib/gen/pulseox -c $(CPP_DIR)/src/pulseOximeter-echo.cpp -o $(CPP_DIR)/src/pulseOximeter-echo.o $(LDFLAGS) $(LIBS);

# Compile the pulseoxOximeterSubscribe binary
$(CPP_DIR)/bin/pulseox-sub-alarm: $(CPP_DIR)/lib/gen/pulseox/libpulseox.a $(CPP_LIB_DIR)/Functions.o
	cd $(CPP_DIR)/src; \
        $(CPP) $(CPPFLAGS) -I$(CPP_DIR)/lib/gen/pulseox -c $(CPP_DIR)/src/pulseOximeter-alarm.cpp -o $(CPP_DIR)/src/pulseOximeter-alarm.o  $(LDFLAGS) $(LIBS); 

# Compile the pulseoxOximeterSubscribe binary
$(CPP_DIR)/bin/pulseox-sub-persist: $(CPP_DIR)/lib/gen/pulseox/libpulseox.a $(CPP_LIB_DIR)/Functions.o 
	cd $(CPP_DIR)/src; \
        $(CPP) $(CPPFLAGS) -I$(CPP_DIR)/lib/gen/pulseox -c $(CPP_DIR)/src/pulseOximeter-persist.cpp -o $(CPP_DIR)/src/pulseOximeter-persist.o $(LDFLAGS) $(LIBS);

# Creating Libraries
$(CPP_DIR)/bin/lib:
	cd $(CPP_DIR)/src; \
	ar cr $(CPP_DIR)/libpulseoximeter.a $(CPP_DIR)/src/pulseOximeter-pub.o $(CPP_LIB_DIR)/Functions.o $(CPP_DIR)/lib/gen/pulseox/libpulseox.a \
	$(CPP_DIR)/src/pulseOximeter-echo.o $(CPP_DIR)/src/pulseOximeter-alarm.o $(CPP_DIR)/src/pulseOximeter-persist.o; \
        ranlib $(CPP_DIR)/libpulseoximeter.a; \
	
pulseox_install:
	mkdir -p $(TARGET_PATH)/lib; \
        mkdir -p $(TARGET_PATH)/include; \
	cp $(CPP_DIR)/libpulseoximeter.a $(TARGET_PATH)/lib; \
	cp $(CPP_DIR)/libpulseoximeter.a /lib; \
        cp $(CPP_DIR)/lib/pulseOximeter.h $(TARGET_PATH)/include; \
        cp $(CPP_DIR)/lib/pulseOximeter.h /usr/include; \
        cp $(CPP_DIR)/lib/Functions.h /usr/include;

