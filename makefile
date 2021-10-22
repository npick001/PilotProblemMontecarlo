all: main.cpp PilotSim.o
	g++ main.cpp PilotSim. -o pilotSim
PilotSim.o: PilotSim.h PilotSim.cpp
clean:
	rm *.o
	