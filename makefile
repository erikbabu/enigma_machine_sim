CC= g++
CFLAGS= -Wall -Werror -pedantic -std=c++11
OBJS= Main.o EnigmaMachine.o Reflector.o Rotor.o Plugboard.o

enigma: $(OBJS)
	$(CC) $(CFLAGS) -o enigma $(OBJS)

Main.o: Main.cpp EnigmaMachine.hpp
	$(CC) $(CFLAGS) -c Main.cpp

EnigmaMachine.o: EnigmaMachine.cpp EnigmaMachine.hpp Reflector.hpp Rotor.hpp Plugboard.hpp
	$(CC) $(CFLAGS) -c EnigmaMachine.cpp

Reflector.o: Reflector.cpp Reflector.hpp
	$(CC) $(CFLAGS) -c Reflector.cpp

Rotor.o: Rotor.cpp Rotor.hpp
	$(CC) $(CFLAGS) -c Rotor.cpp

Plugboard.o: Plugboard.cpp Plugboard.hpp
	$(CC) $(CFLAGS) -c Plugboard.cpp

clean:
	rm -rf enigma *.o

.PHONY: clean
