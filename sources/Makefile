TARGET = scan_cli
GXX = g++
CXXFLAGS = -Wall -g
SRCS = main.cpp \
		./getip/sniff.cpp \
		./cli/command_line.cpp \
		./cli/display.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean: 
	rm -rf $(TARGET)