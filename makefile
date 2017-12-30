CC= g++
CFLAGS= -Wall -Werror -pedantic -std=c++11
OBJS= Main.o EnigmaMachine.o Reflector.o

enigma: $(OBJS)
	$(CC) $(CFLAGS) -o enigma $(OBJS)

Main.o: EnigmaMachine.hpp
	$(CC) $(CFLAGS) -c Main.cpp

EnigmaMachine.o: EnigmaMachine.hpp Reflector.hpp
	$(CC) $(CFLAGS) -c EnigmaMachine.cpp

Reflector.o: Reflector.hpp
	$(CC) $(CFLAGS) -c Reflector.cpp

clean:
	rm -rf enigma *.o

.PHONY: clean
