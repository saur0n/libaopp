################################################################################
#   libao++: C++ wrapper for audio output library
#   Build rules
#   
#   © 2019, Sauron
################################################################################

NAME=ao++
CC=g++
CXXFLAGS=-fPIC -std=gnu++11 -Os -Wall -Wextra -Wno-unused-parameter -g
SOURCES=*.cpp
HEADERS=*.hpp
OUTPUT=lib$(NAME).so

all: $(OUTPUT)

$(OUTPUT): $(SOURCES) $(HEADERS)
	$(CC) -shared -lao $(CXXFLAGS) -o $(OUTPUT) $(SOURCES)

clean:
	rm -f *.o *.so

release: all
	strip $(OUTPUT)

install:
	mv $(OUTPUT) /usr/lib64
	mkdir -p /usr/include/ao/
	cp $(HEADERS) /usr/include/ao/

.PHONY:
	all release install clean
