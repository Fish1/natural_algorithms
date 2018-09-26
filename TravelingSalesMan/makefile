install:
	g++ -c *.cpp
	g++ *.o -o app -lsfml-graphics -lsfml-window -lsfml-system
	rm *.o
	
gen:
	cd ./generator
	g++ ./generator/CoordinateGenerator.cpp -o ./generator/Generator
