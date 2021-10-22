all: main.cpp PilotSim.cpp
	g++ main.o PilotSim.o -o program

clean:
	rm *.o
	