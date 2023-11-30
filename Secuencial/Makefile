#Makefile de compilacion

CC := g++
CFLAGS := -std=c++11 -Wall

SOURCE := secuencial.cpp
EXECUTABLE := secuencialejecutable
OPENCV := $(shell pkg-config --cflags --libs opencv4)

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE) $(OPENCV)

clean:
	rm -f $(EXECUTABLE)
