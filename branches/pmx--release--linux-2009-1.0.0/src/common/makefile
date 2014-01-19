CC = g++
CFLAGS = -W -Wall -g
LDFLAGS = -g

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
