CC            = g++
LDFLAGS       =
CFLAGS        = -c -g
DEBUG_FLAGS   = -D__DEBUG__
INCLUDE_DIRS  = $(shell pwd)
TEST_FILE     = $(shell pwd)/test/testAPI.cpp
CFLAGS       += -I $(INCLUDE_DIRS)
CFLAGS       += $(DEBUG_FLAGS)

HEADERS = SerialPort.h
SRCS    = SerialPort.cpp
OBJS 	= $(SRCS:.cpp=.o)

# Compile object files from the sources
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

all: serial-test

serial-test: $(TEST_FILE) $(HEADERS) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@
api:

clean:
	rm -rf *.o
	rm -rf serial-test
