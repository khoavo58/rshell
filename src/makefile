CC = g++
CC_FLAGS = -std=c++11 -Wall -ansi -pedantic
EXEC = main.out
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.cpp)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)