
backtester: main.o event.o datetime.o
	g++ main.o event.o datetime.o -o backtester

main.o: ./src/main.cpp
	g++ -c ./src/main.cpp

event.o: ./src/event.cpp ./src/event.h
	g++ -c ./src/event.cpp

datetime.o: ./src/datetime.cpp ./src/datetime.h
	g++ -c ./src/datetime.cpp

clean:
	del *.o
	del backtester.exe

