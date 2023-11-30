#Makefile de compilacion

CC := g++
CFLAGS := -std=c++11 -Wall -fopenmp

SOURCE := paraleloOpenMP.cpp
EXECUTABLE := openejecutable
OPENCV := $(shell pkg-config --cflags --libs opencv4)

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE) $(OPENCV)

clean:
	rm -f $(EXECUTABLE)
