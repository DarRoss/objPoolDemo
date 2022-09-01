objPoolDemo: particle.o genericPool.o main.o poolManager.o
	g++ -g -o objPoolDemo main.o -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17 particle.o genericPool.o poolManager.o

main.o: main.cpp olcPixelGameEngine.h poolManager.o
	g++ -g -c main.cpp -std=c++17

particle.o: particle.h particle.cpp
	g++ -g -c particle.cpp -std=c++17

genericPool.o: genericPool.h genericPool.cpp 
	g++ -g -c genericPool.cpp -std=c++17

poolManager.o: poolManager.h poolManager.cpp genericPool.o particle.o
	g++ -g -c poolManager.cpp -std=c++17

clean:
	rm *.o objPoolDemo
