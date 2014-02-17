# Base make files for all the project builds
# This file should not used directly
# ------------------------------------
# Expected variables
#  - TARGET [optional] Indicates the target of the compilation - if any
# ------------------------------------

# Base path for armadeus compiler and headers
XENO=/media/Armadeus/armadeus-3.4/buildroot/project_build_armv4t/apf9328/root/usr/xenomai

# Define the compiler and headers to be used
ifeq ($(wildcard $(XENO)), )
    CXX = g++
    INCLUDE = /usr
    CXXFLAGS_EXTRA = -DSIMU -I$(DEVSIMU)/$(SOURCE)
    LDFLAGS_EXTRA = -lrt ../../build/dev-simu/*.o
else
    CXX = arm-linux-uclibcgnueabi-g++
    INCLUDE = $(XENO)
    CXXFLAGS_EXTRA = -ggdb -I$(INCLUDE)/include/native -I$(INCLUDE)/include/rtdm
    LDFLAGS_EXTRA = -ggdb -lnative -lrtdm -las_devices -Xlinker $(INCLUDE)/lib/libnative.a $(INCLUDE)/lib/librtdm.a
endif

# Folder for intermediate files
BUILD = ../../build/$(shell basename $(CURDIR))

# Folder containing source files
SOURCE = cpp

# Folder containing resource files - to be copied with output
RESOURCE = res

# Path to the common project
COMMON = ../common

# Path to the dev-simu project
DEVSIMU = ../dev-simu

# All the source files
FILES = $(notdir $(wildcard $(SOURCE)/*.cpp))

# All the intermediate files
OBJ = $(addprefix $(BUILD)/,$(FILES:.cpp=.o))

# Default compiler variables
CXXFLAGS = -W -Wall -g -ggdb -I$(COMMON)/$(SOURCE) -I$(INCLUDE)/include $(CXXFLAGS_EXTRA)

LDFLAGS = -lpthread -L$(INCLUDE)/lib -Xlinker -rpath $(INCLUDE)/lib $(LDFLAGS_EXTRA)

# Define the default target - compile the intermediate files and the output of the project - if any
all : $(TARGET) $(OBJ)

.PHONY: all-clean clean format

# Targets for end projects
ifdef TARGET
$(TARGET): common dev-simu resource $(OBJ)
	@$(CXX) -o $@ $(OBJ) ../../build/common/*.o $(LDFLAGS)

common: dev-simu
	@(cd $(COMMON) && $(MAKE))

resource:
	@(cp $(RESOURCE)/* ../../PMXArmadeusBinaries)
endif

# Targets for simu - if required
ifeq ($(wildcard $(XENO)), )
dev-simu:
	@(cd $(DEVSIMU) && $(MAKE))
else
dev-simu:
endif

# Target to build .o files - precompiled file
$(BUILD)/%.o: $(SOURCE)/%.cpp
	@mkdir -p $(BUILD)
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

# Target to build .d files - dependency file
$(BUILD)/%.d: $(SOURCE)/%.cpp
	@mkdir -p $(BUILD)
	@$(CXX) -MM -MT '$(@:.d=.o) $@' -o $@ $< -I$(COMMON)/$(SOURCE)

# Target to format the source code
format:
	indent -sc -pmt $(SOURCE)/*.cpp $(SOURCE)/*.hpp
	rm -f $(SOURCE)/*.cpp~
	rm -f $(SOURCE)/*.hpp~
	astyle --options=../../astyle.cfg $(SOURCE)/*.cpp $(SOURCE)/*.hpp
	rm -f $(SOURCE)/*.cpp.orig
	rm -f $(SOURCE)/*.hpp.orig

ifdef TARGET
# Target to clean intermediate files
clean:
	@(cd $(COMMON) && $(MAKE) $@)
	@(cd $(DEVSIMU) && $(MAKE) $@)
	@rm -f $(BUILD)/*.o
	@rm -f $(BUILD)/*.d

# Target to clean intermediate and distribution files
all-clean: clean
	@(cd $(COMMON) && $(MAKE) $@)
	@(cd $(DEVSIMU) && $(MAKE) $@)
	@rm -f $(TARGET)

else
# Target to clean intermediate files
clean:
	@rm -f $(BUILD)/*.o
	@rm -f $(BUILD)/*.d

# Target to clean intermediate and distribution files
all-clean: clean
endif

# Include dependency files - if required
ifeq '$(MAKECMDGOALS)' 'all-clean'
NOINCLUDE=true
endif

ifeq '$(MAKECMDGOALS)' 'clean'
NOINCLUDE=true
endif

ifndef NOINCLUDE
-include $(OBJ:.o=.d)
endif
