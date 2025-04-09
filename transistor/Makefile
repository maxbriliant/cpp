main.x: transistor.cpp Transistor.o AndGate.o OrGate.o
	g++ -o main.x transistor.cpp Transistor.o  AndGate.o OrGate.o
Transistor.o: Transistor.cpp
	g++ -c Transistor.cpp
AndGate.o: AndGate.cpp
	g++ -c AndGate.cpp
OrGate.o: OrGate.cpp
	g++ -c OrGate.cpp
clean:
	rm *.o *.x
