COMMON = ../common
TARGET = ../../dist/PMX_TEST
BUILD = ../../build/$(shell basename $(CURDIR))
SOURCE = cpp
RESOURCE = res
CFILES = $(notdir $(wildcard $(SOURCE)/*.cpp))
OBJ = $(addprefix $(BUILD)/,$(CFILES:.cpp=.o))

CC = g++
CFLAGS = -I$(COMMON)/$(SOURCE) -W -Wall
LDFLAGS = -lpthread

.PHONY: common clean all-clean

all : $(TARGET)

$(TARGET) : common res $(OBJ)
	$(CC) -o $@ $(OBJ) ../../build/common/*.o $(LDFLAGS)

common:
	@(cd $(COMMON) && $(MAKE))

res:
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

