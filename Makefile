PROJECT = BLS
CC = g++
CPPFLAGS = -g #-static <- better used when finished, debugging with -static is a bad idea
FILES = $(wildcard *.cpp)
LIBS =

$(PROJECT): $(FILES)
	$(CC) -o $@ $^ $(LIBS) $(CPPFLAGS)

clean:
	rm -rf $(PROJECT)


run: $(PROJECT)
	./$(PROJECT)