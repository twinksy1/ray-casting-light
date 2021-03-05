MAIN=main.o
HEADERS=*.h
EXE=app
LIBS=-lSDL2
CC=g++

all: $(EXE)

%.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@

$(EXE): $(MAIN)
	$(CC) $^ -o $@ $(LIBS)

clean:
	rm $(EXE) *.o
