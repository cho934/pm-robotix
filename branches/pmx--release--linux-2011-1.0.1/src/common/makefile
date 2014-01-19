CC=arm-linux-uclibcgnueabi-g++
ARMADEUS_ROOTFS_DIR=/armadeus/compilation2/buildroot/project_build_armv4t/apf9328/root
XENO=$(ARMADEUS_ROOTFS_DIR)/usr/xenomai

CFLAGS=-W -Wall -g -I$(XENO)/include -I$(XENO)/include/native  -I$(XENO)/include/rtdm
#LDFLAGS= -lpthread -lnative -lrtdm -las_devices -L$(XENO)/lib -Xlinker -rpath $(XENO)/lib -Xlinker $(XENO)/lib/libnative.a $(XENO)/lib/librtdm.a

BUILD  = ../../build/$(shell basename $(CURDIR))
SOURCE = cpp
FILES  = $(notdir $(wildcard $(SOURCE)/*.cpp))
OBJ    = $(addprefix $(BUILD)/,$(FILES:.cpp=.o))

all : $(OBJ)

$(BUILD)/%.o : $(SOURCE)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)  

format:
	indent -sc -pmt $(SOURCE)/*.cpp $(SOURCE)/*.hpp
	rm -f $(SOURCE)/*.cpp~
	rm -f $(SOURCE)/*.hpp~
	astyle --options=../../astyle.cfg $(SOURCE)/*.cpp $(SOURCE)/*.hpp
	rm -f $(SOURCE)/*.cpp.orig
	rm -f $(SOURCE)/*.hpp.orig

clean:
	@rm -f $(OBJ)

all-clean: clean