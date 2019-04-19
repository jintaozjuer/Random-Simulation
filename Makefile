proj5.exe: proj5.o EventClass.o operator.o random.o RideClass.o SimulationClass.o
	g++ proj5.o EventClass.o operator.o random.o RideClass.o SimulationClass.o -o proj5.exe


proj5.o: proj5.cpp LinkedNodeClass.h LinkedNodeClass.inl SortedListClass.h SortedListClass.inl FIFOQueueClass.h FIFOQueueClass.inl EventClass.h constants.h random.h SimulationClass.h operator.h
	g++ -c proj5.cpp -o proj5.o

EventClass.o: EventClass.cpp EventClass.h constants.h
	g++ -c EventClass.cpp -o EventClass.o

operator.o: operator.cpp operator.h constants.h EventClass.h
	g++ -c operator.cpp -o operator.o

random.o: random.cpp random.h
	g++ -c random.cpp -o random.o

RideClass.o: RideClass.cpp RideClass.h constants.h
	g++ -c RideClass.cpp -o RideClass.o

SimulationClass.o: SimulationClass.cpp SimulationClass.h random.h constants.h
	g++ -c SimulationClass.cpp -o SimulationClass.o

clean:
	rm -f proj5.exe proj5.o EventClass.o operator.o random.o RideClass.o SimulationClass.o
