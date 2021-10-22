pilotSim: main.o PilotSim.o
	gcc -g -Wall -o pilotSim main.o PilotSim.o
main.o: main.cpp
PilotSim.o: PilotSim.h PilotSim.cpp
clean:
	rm main.o PilotSim.o