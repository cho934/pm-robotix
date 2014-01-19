COMMON = ../common
TARGET = ../../dist/DEV_TEST
BUILD = ../../build/$(shell basename $(CURDIR))
SOURCE = cpp
RESOURCE = res
CFILES = $(notdir $(wildcard $(SOURCE)/*.cpp))
OBJ = $(addprefix $(BUILD)/,$(CFILES:.cpp=.o))
ARMADEUS_ROOTFS_DIR=/armadeus/compilation2/buildroot/project_build_armv4t/apf9328/root
XENO=$(ARMADEUS_ROOTFS_DIR)/usr/xenomai

CC = arm-linux-uclibcgnueabi-g++
CFLAGS = -I$(COMMON)/$(SOURCE) -W -Wall -I$(XENO)/include -I$(XENO)/include/native  -I$(XENO)/include/rtdm
LDFLAGS = -lpthread -lnative -lrtdm -las_devices -L$(XENO)/lib -Xlinker -rpath $(XENO)/lib -Xlinker $(XENO)/lib/libnative.a $(XENO)/lib/librtdm.a

.PHONY: common resource clean all-clean

all : $(TARGET)

$(TARGET) : common resource $(OBJ)
	$(CC) -o $@ $(OBJ) ../../build/common/*.o $(LDFLAGS) 

common:
	@(cd $(COMMON) && $(MAKE))

resource:
	@(cp $(RESOURCE)/* ../../dist)
	
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
	@(cd $(COMMON) && $(MAKE) $@)
	@rm -f $(OBJ)

all-clean: clean
	@(cd $(COMMON) && $(MAKE) $@)
	@rm $(TARGET)

