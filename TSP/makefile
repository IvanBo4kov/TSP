output: main.o TSP.o
	g++ main.o TSP.o -o output

main.o: main.cpp
	g++ -c -std=c++17  main.cpp 

TSP.o: TSP.cpp TSP.hpp
	g++ -c -std=c++17  TSP.cpp

clean:
	rm *.o output

