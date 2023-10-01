PROJECT = BLS
CC = g++
CPPFLAGS = -g
FILES = $(wildcard *.cpp)
LIBS =

$(PROJECT): $(FILES)
	$(CC) -o $@ $^ $(LIBS) $(CPPFLAGS) -static

clean:
	rm -rf $(PROJECT)


run: $(PROJECT)
	./$(PROJECT)