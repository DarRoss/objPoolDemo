tgtLeadingDemo: projectile.o genericPool.o main.o poolManager.o aimer.o slowTarget.o
	g++ -g -o tgtLeadingDemo main.o -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17 projectile.o genericPool.o poolManager.o aimer.o slowTarget.o

main.o: main.cpp olcPixelGameEngine.h poolManager.o aimer.o slowTarget.o
	g++ -g -c main.cpp -std=c++17

projectile.o: projectile.h projectile.cpp
	g++ -g -c projectile.cpp -std=c++17

genericPool.o: genericPool.h genericPool.cpp 
	g++ -g -c genericPool.cpp -std=c++17

poolManager.o: poolManager.h poolManager.cpp genericPool.o projectile.o
	g++ -g -c poolManager.cpp -std=c++17

aimer.o: aimer.h aimer.cpp poolManager.o
	g++ -g -c aimer.cpp -std=c++17

slowTarget.o: slowTarget.h slowTarget.cpp
	g++ -g -c slowTarget.cpp -std=c++17

clean:
	rm *.o tgtLeadingDemo
