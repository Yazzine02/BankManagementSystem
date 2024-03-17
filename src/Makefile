# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -Wall

# Libraries
LIBS = -lsqlite3

# Source files
SRCS = main.cpp Database.cpp Logger.cpp ATM.cpp Client.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = main

# Default rule
all: $(TARGET)

# Compile source files to object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to generate executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

