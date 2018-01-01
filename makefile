CC= g++
CFLAGS= -Wall -Werror -pedantic -std=c++11
OBJS= Main.o EnigmaMachine.o Reflector.o Rotor.o Plugboard.o Utils.o MappingTool.o

enigma: $(OBJS)
	$(CC) $(CFLAGS) -o enigma $(OBJS)

Main.o: Main.cpp EnigmaMachine.hpp Utils.hpp
	$(CC) $(CFLAGS) -c Main.cpp

EnigmaMachine.o: EnigmaMachine.cpp EnigmaMachine.hpp Reflector.hpp Rotor.hpp Plugboard.hpp
	$(CC) $(CFLAGS) -c EnigmaMachine.cpp

Reflector.o: Reflector.cpp Reflector.hpp MappingTool.hpp
	$(CC) $(CFLAGS) -c Reflector.cpp

MappingTool.o: MappingTool.cpp MappingTool.hpp
	$(CC) $(CFLAGS) -c MappingTool.cpp

Rotor.o: Rotor.cpp Rotor.hpp MappingTool.hpp
	$(CC) $(CFLAGS) -c Rotor.cpp

Plugboard.o: Plugboard.cpp Plugboard.hpp MappingTool.hpp
	$(CC) $(CFLAGS) -c Plugboard.cpp

Utils.o: Utils.cpp Utils.hpp
	$(CC) $(CFLAGS) -c Utils.cpp

clean:
	rm -rf enigma *.o

.PHONY: clean
