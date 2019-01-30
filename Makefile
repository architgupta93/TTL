CC            = g++
LDFLAGS       =
CFLAGS        = -c -g
DEBUG_FLAGS   = -D__DEBUG__
INCLUDE_DIRS  = $(shell pwd)
CFLAGS       += -I$(INCLUDE_DIRS)
CFLAGS       += $(DEBUG_FLAGS)

# Test specific files and objects
TEST_FILE     = $(shell pwd)/test/testAPI.cpp
TEST_OBJ      = $(shell pwd)/test/testAPI.o

COMM_FILE     = $(shell pwd)/test/testComm.cpp
COMM_OBJ      = $(shell pwd)/test/testComm.o

HEADERS = SerialPort.h
SRCS    = SerialPort.cpp
OBJS 	= $(SRCS:.cpp=.o)

# Compile object files from the sources
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

all: api

comm: $(COMM_FILE)
	$(CC) $(COMM_FILE) -o $@.x

api: $(TEST_OBJ) $(HEADERS) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(TEST_OBJ) -o $@.x

clean:
	rm -rf *.o
	rm -rf *.x
	rm -rf test/*.o
