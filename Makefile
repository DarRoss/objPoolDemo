objPoolDemo: particle.o particlePool.o main.o
	g++ -g -o objPoolDemo main.o -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17 particle.o particlePool.o

main.o: main.cpp olcPixelGameEngine.h particlePool.o
	g++ -g -c main.cpp -std=c++17

particle.o: particle.h particle.cpp
	g++ -g -c particle.cpp -std=c++17

particlePool.o: particlePool.h particlePool.cpp particle.o
	g++ -g -c particlePool.cpp -std=c++17

clean:
	rm *.o objPoolDemo
