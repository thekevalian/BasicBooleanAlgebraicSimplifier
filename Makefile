PROJECT = BLS
CC = g++
FILES = $(wildcard *.cpp)
LIBS =

$(PROJECT): $(FILES)
	$(CC) -o $@ $^ $(LIBS) -static

clean:
	rm -rf $(PROJECT)