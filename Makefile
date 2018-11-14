#### Start of system configuration section. ####

srcdir = ./source
incdir = ./include
CFLAGS = -I./ -I../ 
CXX = g++ -std=gnu++11 $(CFLAGS)
CDEBUG = -g
LDFLAGS = -Wall -g -pthread -lrt

#### End of system configuration section. ####
# identify the .c source files 
csrc =  ./src/CAN_utils.c
csrc += ./src/CO_message.c
csrc += ./src/RT_utils.c
csrc += ./src/motor.c

# idenfity the .cc source files
ccsrc =  ./src/caster.cc
ccsrc += ./src/vehicle.cc

# add target specific files
vehicle_src 				= ./src/main.cc
calibrate_src 			= ./src/calibrate.cc
canDump_motor_src		= ./src/canDump_motor.cc

# general object files
obj =  $(csrc:.c=.o) $(ccsrc:.cc=.o) 

#target specific object files
vehicle_obj   = 		$(obj) $(vehicle_src:.cc=.o) 
calibrate_obj = 		$(obj) $(calibrate_src:.cc=.o) 
canDump_motor_obj = $(obj) $(canDump_motor_src:.cc=.o) 

all_obj = $(obj) ./src/main.o ./src/calibrate.o ./src/canDump_motor.o ./src/joystick.o

# build targets
vehicle: $(vehicle_obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

calibrate: $(calibrate_obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

canDump_motor: $(canDump_motor_obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

test: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

joystick: ./src/joystick.o
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(all_obj)
	rm -f vehicle 
	rm -f calibrate
	rm -f canDump_motor
	rm -f joystick
	rm -f test